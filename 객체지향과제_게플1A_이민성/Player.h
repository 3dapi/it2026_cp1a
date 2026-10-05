#pragma once

class Player
{
public:
    static constexpr int MaxHp = 50;

    void Reset();
    void TakeDamage(int damage);
    int Heal(int amount);

    int GetHp() const;
    int GetMaxHp() const;

private:
    int hp_ = MaxHp;
};
