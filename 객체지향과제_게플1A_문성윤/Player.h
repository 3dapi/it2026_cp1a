#pragma once

class Player
{
  public:
    void Init();
    void TakeDamage(int damage);
    void Heal(int amount);
    void AddScore(int amount);
    void Retry();

    int GetHP() const
    {
        return m_hp;
    }

    int GetLife() const
    {
        return m_life;
    }

    int GetScore() const
    {
        return m_score;
    }

  private:
    int m_hp = 100;
    int m_life = 3;
    int m_score = 0;
};
