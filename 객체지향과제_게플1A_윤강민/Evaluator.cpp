#include "Evaluator.h"

#include <algorithm>
#include <array>

namespace {

struct RankGroup {
    int count = 0;
    int rank = 0;
};

}

HandScore evaluateFive(const Card* cards) {
    int counts[15] = {};
    bool flush = true;
    for (int i = 0; i < 5; ++i) {
        ++counts[cards[i].rank];
        if (cards[i].suit != cards[0].suit) {
            flush = false;
        }
    }

    std::array<RankGroup, 5> groups{};
    int groupCount = 0;
    for (int rank = 14; rank >= 2; --rank) {
        if (counts[rank] > 0) {
            groups[groupCount++] = {counts[rank], rank};
        }
    }
    std::stable_sort(groups.begin(), groups.begin() + groupCount,
                     [](const RankGroup& a, const RankGroup& b) { return a.count > b.count; });

    bool straight = false;
    int straightHigh = 0;
    if (groupCount == 5) {
        if (groups[0].rank - groups[4].rank == 4) {
            straight = true;
            straightHigh = groups[0].rank;
        } else if (groups[0].rank == 14 && groups[1].rank == 5) {
            straight = true;
            straightHigh = 5;
        }
    }

    int category = 0;
    if (straight && flush) {
        category = 8;
    } else if (groups[0].count == 4) {
        category = 7;
    } else if (groups[0].count == 3 && groups[1].count == 2) {
        category = 6;
    } else if (flush) {
        category = 5;
    } else if (straight) {
        category = 4;
    } else if (groups[0].count == 3) {
        category = 3;
    } else if (groups[0].count == 2 && groups[1].count == 2) {
        category = 2;
    } else if (groups[0].count == 2) {
        category = 1;
    }

    HandScore score = static_cast<HandScore>(category) << 20;
    if (straight) {
        score |= static_cast<HandScore>(straightHigh) << 16;
    } else {
        int shift = 16;
        for (int i = 0; i < groupCount; ++i) {
            score |= static_cast<HandScore>(groups[i].rank) << shift;
            shift -= 4;
        }
    }
    return score;
}

HandScore evaluateBest(const std::vector<Card>& cards) {
    const int total = static_cast<int>(cards.size());
    if (total < 5) {
        return 0;
    }

    HandScore best = 0;
    for (int mask = 0; mask < (1 << total); ++mask) {
        int bits = 0;
        for (int i = 0; i < total; ++i) {
            if (mask & (1 << i)) {
                ++bits;
            }
        }
        if (bits != 5) {
            continue;
        }

        Card five[5];
        int next = 0;
        for (int i = 0; i < total; ++i) {
            if (mask & (1 << i)) {
                five[next++] = cards[i];
            }
        }
        best = std::max(best, evaluateFive(five));
    }
    return best;
}

const char* categoryName(int category) {
    static const char* names[] = {
        "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight",
        "Flush", "Full House", "Four of a Kind", "Straight Flush"};
    return names[category];
}
