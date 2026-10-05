#pragma once

#include "Player.h"

#include <random>

enum class BattlePhase
{
    AwaitAttack,
    EnemyWindup,
    EnemyFeedback,
    EnemyDefeated,
    Healing,
    Won,
    Lost
};

class CombatState
{
public:
    static constexpr int TotalEnemies = 3;
    static constexpr int AttackDamage = 8;
    static constexpr int EnemyDamage = 7;
    static constexpr int BossMaxHp = 56;
    static constexpr int BossDamage = 10;
    static constexpr int HealMin = 10;
    static constexpr int HealMax = 20;
    static constexpr int PotionDropMin = 1;
    static constexpr int PotionDropMax = 2;
    static constexpr double GuardChance = 0.6;

    CombatState();
    explicit CombatState(unsigned int seed);

    void Reset();
    bool Attack();
    bool Guard();
    bool UsePotion();
    void Update(double seconds);

    BattlePhase GetPhase() const;
    const Player& GetPlayer() const;
    int GetEnemyHp() const;
    int GetEnemyMaxHp() const;
    int GetEnemyNumber() const;
    int GetDefeatedCount() const;
    bool IsBoss() const;
    int GetEnemyDamage() const;
    int GetPotionCount() const;
    int GetLastPotionDrop() const;
    int GetLastHealAmount() const;
    bool IsGuardQueued() const;
    bool WasGuardAttempted() const;
    bool LastGuardSucceeded() const;
    double GetPhaseSecondsRemaining() const;
    bool IsEnemyHitVisible() const;

private:
    static constexpr int EnemyMaxHp = 32;
    static constexpr double WindupSeconds = 1.1;
    static constexpr double FeedbackSeconds = 0.65;
    static constexpr double DefeatedSeconds = 0.75;
    static constexpr double HitSeconds = 0.32;
    static constexpr double HealingSeconds = 0.65;

    void BeginEnemyTurn(bool enemyWasHit);
    void FinishPhase();

    Player player_;
    std::mt19937 random_;
    BattlePhase phase_ = BattlePhase::AwaitAttack;
    int enemyHp_ = EnemyMaxHp;
    int enemyNumber_ = 1;
    int defeatedCount_ = 0;
    int potionCount_ = 0;
    int lastPotionDrop_ = 0;
    int lastHealAmount_ = 0;
    double phaseSeconds_ = 0.0;
    bool guardQueued_ = false;
    bool guardAttempted_ = false;
    bool guardSucceeded_ = false;
    bool enemyWasHit_ = false;
};
