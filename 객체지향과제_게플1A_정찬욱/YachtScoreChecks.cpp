#include "YachtScore.h"
// 대표 조합과 경계 조건을 컴파일 단계에서 검사
namespace {
constexpr int house[5] = {2,2,5,5,5};
constexpr int yacht[5] = {6,6,6,6,6};
constexpr int small[5] = {1,2,2,3,4};
constexpr int large[5] = {2,3,4,5,6};
constexpr int gap[5] = {1,2,3,5,6};
constexpr int four[5] = {3,3,3,3,6};
constexpr int bad[5] = {0,1,2,3,4};
static_assert(YachtScore::Calculate(1, house) == 4, "upper score");
static_assert(YachtScore::Calculate(6, house) == 19, "choice");
static_assert(YachtScore::Calculate(7, four) == 18, "four of a kind");
static_assert(YachtScore::Calculate(7, house) == 0, "not four");
static_assert(YachtScore::Calculate(8, house) == 19, "full house");
static_assert(YachtScore::Calculate(8, yacht) == 0, "distinct full house");
static_assert(YachtScore::Calculate(9, small) == 15, "duplicate small straight");
static_assert(YachtScore::Calculate(10, small) == 0, "not large");
static_assert(YachtScore::Calculate(10, large) == 30, "large straight");
static_assert(YachtScore::Calculate(9, gap) == 0, "gap");
static_assert(YachtScore::Calculate(11, yacht) == 50, "yacht");
static_assert(YachtScore::Calculate(11, four) == 0, "not yacht");
static_assert(YachtScore::Calculate(0, bad) == 0, "invalid die");
}
