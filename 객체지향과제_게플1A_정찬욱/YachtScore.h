#pragma once
#include <array>

// 화면이나 입력에 의존하지 않는 야추 점수 계산입니다.
class YachtScore
{
public:
    static constexpr int Categories = 12;
    // 0~5: 숫자 항목, 6: 초이스, 7: 포카드, 8: 풀하우스,
    // 9: 작은 스트레이트, 10: 큰 스트레이트, 11: 야추입니다.
    static constexpr int Calculate(int category, const int (&dice)[5])
    {
        if (category < 0 || category >= Categories) return 0;
        int counts[7] = {};
        int sum = 0;
        for (int i = 0; i < 5; ++i)
        {
            if (dice[i] < 1 || dice[i] > 6) return 0;
            ++counts[dice[i]];
            sum += dice[i];
        }
        if (category < 6) return counts[category + 1] * (category + 1);
        if (category == 6) return sum;
        int largest = 0;
        bool pair = false, triple = false;
        for (int face = 1; face <= 6; ++face)
        {
            if (counts[face] > largest) largest = counts[face];
            if (counts[face] == 2) pair = true;
            if (counts[face] == 3) triple = true;
        }
        if (category == 7) return largest >= 4 ? sum : 0;
        // 풀하우스는 서로 다른 숫자의 3개와 2개 조합입니다.
        if (category == 8) return pair && triple ? sum : 0;
        if (category == 11) return largest == 5 ? 50 : 0;
        int run = 0, longest = 0;
        for (int face = 1; face <= 6; ++face)
        {
            run = counts[face] ? run + 1 : 0;
            if (run > longest) longest = run;
        }
        if (category == 9) return longest >= 4 ? 15 : 0;
        return longest >= 5 ? 30 : 0;
    }
    void Reset() { m_scores.fill(-1); m_used = 0; }
    bool Record(int category, const int (&dice)[5])
    {
        if (category < 0 || category >= Categories || m_scores[category] >= 0) return false;
        m_scores[category] = Calculate(category, dice);
        ++m_used;
        return true;
    }
    int Get(int category) const { return m_scores[category]; }
    int Used() const { return m_used; }
    bool Finished() const { return m_used == Categories; }
    int Subtotal() const
    {
        int sum = 0;
        for (int i = 0; i < 6; ++i) if (m_scores[i] >= 0) sum += m_scores[i];
        return sum;
    }
    int Bonus() const { return Subtotal() >= 63 ? 35 : 0; }
    int Total() const
    {
        int sum = Bonus();
        for (int value : m_scores) if (value >= 0) sum += value;
        return sum;
    }
private:
    std::array<int, Categories> m_scores = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
    int m_used = 0;
};
