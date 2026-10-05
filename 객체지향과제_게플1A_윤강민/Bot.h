#pragma once
//3타이트 300핸드 or 1등
//2루즈  마지막 or 300핸드?
//3피쉬 200핸드
#include "Cards.h"

#include <vector>

enum class Style { TightAggressive, TightLoose, Fish };

enum class ActionType { Fold, Check, Call, Raise };

struct Action {
    ActionType type = ActionType::Check;
    int amount = 0;
};

struct BotContext {
    Street street = Street::Preflop;
    const std::vector<Card>* board = nullptr;
    int pot = 0;
    int curBet = 0;
    int minRaise = 0;
    int bigBlind = 0;
    int stack = 0;
    int streetContrib = 0;
    int limpersAndCallers = 0;
};

Action decideBot(Style style, const Card hole[2], const BotContext& context);

const char* styleName(Style style);
