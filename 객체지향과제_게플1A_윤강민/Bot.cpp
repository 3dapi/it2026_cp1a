#include "Bot.h"

#include "Evaluator.h"

#include <algorithm>
#include <cmath>
#include <functional>

namespace {

double preflopScore(const Card& a, const Card& b) {
    const int high = std::max(a.rank, b.rank);
    const int low = std::min(a.rank, b.rank);
    const bool pair = a.rank == b.rank;
    const bool suited = a.suit == b.suit;

    double score = high * 2.0 + low * 1.3;
    if (pair) {
        score += 22.0 + high * 1.3;
    }
    if (suited) {
        score += 8.0;
    }
    if (!pair) {
        score -= std::max(0, high - low - 1) * 2.2;
    }
    if (high == 14) {
        score += 6.0;
    }
    return score;
}

const std::vector<double>& allStartingHandScores() {
    static const std::vector<double> scores = [] {
        std::vector<double> result;
        for (int i = 0; i < 52; ++i) {
            for (int j = i + 1; j < 52; ++j) {
                Card a{2 + i / 4, static_cast<Suit>(i % 4)};
                Card b{2 + j / 4, static_cast<Suit>(j % 4)};
                result.push_back(preflopScore(a, b));
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }();
    return scores;
}

double topPercent(const Card& a, const Card& b) {
    const std::vector<double>& scores = allStartingHandScores();
    const auto above = std::upper_bound(scores.begin(), scores.end(), preflopScore(a, b));
    return static_cast<double>(scores.end() - above) / static_cast<double>(scores.size());
}

struct PostflopRead {
    double strength = 0.0;
    bool draw = false;
};

PostflopRead readPostflop(const Card hole[2], const std::vector<Card>& board) {
    std::vector<Card> all(board);
    all.push_back(hole[0]);
    all.push_back(hole[1]);

    const HandScore score = evaluateBest(all);
    const int category = handCategory(score);
    const int primary = scoreField(score, 0);
    const int secondary = scoreField(score, 1);

    std::vector<int> boardRanks;
    for (const Card& card : board) {
        boardRanks.push_back(card.rank);
    }
    std::sort(boardRanks.begin(), boardRanks.end(), std::greater<int>());

    auto holds = [&](int rank) { return hole[0].rank == rank || hole[1].rank == rank; };
    const bool pocketPair = hole[0].rank == hole[1].rank;

    double strength = 0.97;
    switch (category) {
    case 0:
        strength = 0.10 + (std::max(hole[0].rank, hole[1].rank) == 14 ? 0.05 : 0.0);
        break;
    case 1:
        if (!holds(primary)) {
            strength = 0.16;
        } else if (pocketPair && primary > boardRanks[0]) {
            strength = 0.66;
        } else if (primary >= boardRanks[0]) {
            strength = 0.56;
        } else if (primary >= boardRanks[1]) {
            strength = 0.38;
        } else {
            strength = 0.28;
        }
        break;
    case 2: {
        const int involved = (holds(primary) ? 1 : 0) + (holds(secondary) ? 1 : 0);
        strength = involved == 2 ? 0.74 : (involved == 1 ? 0.45 : 0.18);
        break;
    }
    case 3:
        strength = holds(primary) ? 0.82 : 0.30;
        break;
    case 4:
        strength = 0.88;
        break;
    case 5:
        strength = 0.92;
        break;
    default:
        strength = 0.97;
        break;
    }

    bool draw = false;
    if (board.size() < 5) {
        for (int suit = 0; suit < 4; ++suit) {
            int total = 0;
            bool mine = false;
            for (const Card& card : all) {
                if (static_cast<int>(card.suit) == suit) {
                    ++total;
                }
            }
            for (int i = 0; i < 2; ++i) {
                if (static_cast<int>(hole[i].suit) == suit) {
                    mine = true;
                }
            }
            if (total == 4 && mine) {
                draw = true;
            }
        }

        bool present[16] = {};
        for (const Card& card : all) {
            present[card.rank] = true;
        }
        present[1] = present[14];
        for (int start = 1; start <= 11; ++start) {
            if (!(present[start] && present[start + 1] && present[start + 2] && present[start + 3])) {
                continue;
            }
            for (int rank = start; rank <= start + 3; ++rank) {
                if (holds(rank) || (rank == 1 && holds(14))) {
                    draw = true;
                }
            }
        }

        if (draw && strength < 0.5) {
            strength = std::max(strength, 0.38);
        }
    }

    strength += (rand01() - 0.5) * 0.08;
    return {strength, draw};
}

bool chance(double probability) {
    return rand01() < probability;
}

double between(double base, double spread) {
    return base + spread * rand01();
}

enum class Plan { Fold, Check, Call, Raise };

}

Action decideBot(Style style, const Card hole[2], const BotContext& context) {
    const bool tag = style == Style::TightAggressive;
    const bool tightLoose = style == Style::TightLoose;
    const bool preflop = context.street == Street::Preflop;

    const int rawCall = std::max(0, context.curBet - context.streetContrib);
    const int callAmount = std::min(rawCall, context.stack);
    const double potOdds = callAmount / static_cast<double>(std::max(1, context.pot + callAmount));
    const double commit = callAmount / static_cast<double>(std::max(1, context.stack));
    const bool bigBet = commit > 0.5;
    const int stackNow = context.stack + context.streetContrib;
    const int bigBlind = context.bigBlind;

    Plan plan = Plan::Check;
    double multiplier = 0.0;
    int level = 0;

    if (preflop) {
        const double top = topPercent(hole[0], hole[1]);
        level = context.curBet <= bigBlind ? 0 : (context.curBet <= bigBlind * 4.5 ? 1 : 2);

        if (rawCall <= 0) {
            const double openRate = tag ? 0.12 : (tightLoose ? 0.04 : 0.06);
            plan = (top < openRate && chance(0.8)) ? Plan::Raise : Plan::Check;
        } else if (level == 0) {
            if (tag) {
                plan = top < 0.17 ? Plan::Raise : Plan::Fold;
            } else if (tightLoose) {
                plan = top < 0.04 ? Plan::Raise : (top < 0.20 ? Plan::Call : Plan::Fold);
            } else {
                plan = (top < 0.05 && chance(0.6)) ? Plan::Raise : (top < 0.60 ? Plan::Call : Plan::Fold);
            }
        } else if (level == 1) {
            if (tag) {
                plan = top < 0.04 ? Plan::Raise : (top < 0.10 ? Plan::Call : Plan::Fold);
                if (plan == Plan::Fold && top < 0.30 && chance(0.04)) {
                    plan = Plan::Raise;
                }
            } else if (tightLoose) {
                plan = top < 0.025 ? Plan::Raise : ((top < 0.12 && !bigBet) ? Plan::Call : Plan::Fold);
            } else if (top < 0.03 && chance(0.5)) {
                plan = Plan::Raise;
            } else if ((top < 0.38 && commit < 0.35) || top < 0.12) {
                plan = Plan::Call;
            } else {
                plan = Plan::Fold;
            }
        } else {
            if (tag) {
                plan = top < 0.015 ? Plan::Raise : (top < 0.035 ? Plan::Call : Plan::Fold);
            } else if (tightLoose) {
                plan = top < 0.04 ? Plan::Call : Plan::Fold;
            } else {
                plan = top < 0.15 ? Plan::Call : Plan::Fold;
            }
        }

        if (plan == Plan::Raise) {
            if (level == 0) {
                multiplier = style == Style::Fish ? between(2.0, 2.0) : between(2.3, 1.0);
            } else if (level == 1) {
                multiplier = between(2.7, 0.6);
            } else {
                multiplier = between(2.2, 0.5);
            }
        }
    } else {
        const PostflopRead read = readPostflop(hole, *context.board);
        const double strength = read.strength;
        const bool draw = read.draw;

        if (rawCall <= 0) {
            if (tag) {
                if (strength >= 0.55 && chance(0.75)) {
                    plan = Plan::Raise;
                    multiplier = between(0.5, 0.3);
                } else if (draw && chance(0.5)) {
                    plan = Plan::Raise;
                    multiplier = between(0.45, 0.2);
                } else if (chance(0.07)) {
                    plan = Plan::Raise;
                    multiplier = between(0.4, 0.2);
                }
            } else if (tightLoose) {
                if (strength >= 0.7 && chance(0.35)) {
                    plan = Plan::Raise;
                    multiplier = between(0.6, 0.4);
                }
            } else {
                if (strength >= 0.56 && chance(0.4)) {
                    plan = Plan::Raise;
                    multiplier = between(0.3, 0.4);
                } else if (chance(0.06)) {
                    plan = Plan::Raise;
                    multiplier = between(0.25, 0.3);
                }
            }
        } else {
            if (tag) {
                if (strength >= 0.82 && chance(0.6)) {
                    plan = Plan::Raise;
                    multiplier = between(0.7, 0.4);
                } else if (strength >= std::max(0.42, potOdds + 0.22)) {
                    plan = Plan::Call;
                } else if (draw && potOdds < 0.28) {
                    plan = Plan::Call;
                } else if (chance(0.04)) {
                    plan = Plan::Raise;
                    multiplier = 0.8;
                } else {
                    plan = Plan::Fold;
                }
            } else if (tightLoose) {
                if (strength >= 0.9 && chance(0.3)) {
                    plan = Plan::Raise;
                    multiplier = between(0.7, 0.4);
                } else if (bigBet) {
                    plan = strength >= 0.5 ? Plan::Call : Plan::Fold;
                } else {
                    plan = (strength >= 0.22 || draw) ? Plan::Call : Plan::Fold;
                }
            } else {
                if (strength >= 0.8 && chance(0.35)) {
                    plan = Plan::Raise;
                    multiplier = between(0.5, 0.4);
                } else if (bigBet && strength < 0.3) {
                    plan = Plan::Fold;
                } else if (strength >= 0.14 || draw || potOdds < 0.25) {
                    plan = Plan::Call;
                } else {
                    plan = chance(0.35) ? Plan::Call : Plan::Fold;
                }
            }
        }
    }

    if (plan == Plan::Fold && rawCall <= 0) {
        plan = Plan::Check;
    }

    if (plan == Plan::Raise) {
        double amount;
        if (preflop) {
            if (level == 0) {
                amount = bigBlind * multiplier + std::max(0, context.limpersAndCallers - 1) * bigBlind;
            } else {
                amount = context.curBet * multiplier;
            }
        } else {
            amount = context.curBet +
                     std::max(context.minRaise, static_cast<int>(std::lround(context.pot * multiplier)));
        }

        int target = static_cast<int>(std::lround(amount / 50.0)) * 50;
        target = std::max(target, context.curBet + context.minRaise);
        target = std::min(target, stackNow);
        if (stackNow - target < bigBlind * 2) {
            target = stackNow;
        }

        if (context.stack <= rawCall || target <= context.curBet) {
            plan = rawCall > 0 ? Plan::Call : Plan::Check;
        } else {
            return {ActionType::Raise, target};
        }
    }

    switch (plan) {
    case Plan::Fold: return {ActionType::Fold, 0};
    case Plan::Call: return {ActionType::Call, 0};
    default: return {ActionType::Check, 0};
    }
}

const char* styleName(Style style) {
    switch (style) {
    case Style::TightAggressive: return "TAG";
    case Style::TightLoose: return "TL";
    default: return "FISH";
    }
}
