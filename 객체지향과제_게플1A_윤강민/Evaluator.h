#pragma once

#include "Cards.h"

#include <vector>

using HandScore = unsigned int;

HandScore evaluateFive(const Card* cards);
HandScore evaluateBest(const std::vector<Card>& cards);

inline int handCategory(HandScore score) {
    return static_cast<int>(score >> 20);
}

inline int scoreField(HandScore score, int index) {
    return static_cast<int>((score >> (16 - 4 * index)) & 0xF);
}

const char* categoryName(int category);
