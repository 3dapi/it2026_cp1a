#include "Player.h"

#include <algorithm>

void Player::Reset()
{
    hp_ = MaxHp;
}

void Player::TakeDamage(int damage)
{
    if (damage > 0)
    {
        hp_ = std::max(0, hp_ - damage);
    }
}

int Player::Heal(int amount)
{
    if (amount <= 0 || hp_ == 0)
    {
        return 0;
    }

    const int restored = std::min(amount, MaxHp - hp_);
    hp_ += restored;
    return restored;
}

int Player::GetHp() const
{
    return hp_;
}

int Player::GetMaxHp() const
{
    return MaxHp;
}
