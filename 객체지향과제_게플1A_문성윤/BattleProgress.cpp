#include "BattleProgress.h"
#include <algorithm>
#include <cstdio>
#include <cstring>

void BattleProgress::Reset() { *this = BattleProgress{}; }

void BattleProgress::BeginLines(Phase phase)
{
    m_phase = phase;
    m_lines.clear();
    m_page = 0;
}

void BattleProgress::Append(BattleDialogue dialogue, const char* replaceId, const char* replacement)
{
    for (const auto& line : GetBattleDialogue(dialogue))
        m_lines.push_back({line.speaker,
            replaceId && std::strcmp(line.id, replaceId) == 0 ? replacement : line.text, line.visual});
}

void BattleProgress::ResetAttempt()
{
    m_enemyHP = 100;
    m_potions = 1;
    m_turn = 1;
    m_strong = m_defending = m_clueUsed = false;
    m_lowHPShown = m_clueShown = m_weakEnemyShown = false;
    m_sound = Sound::None;
    BeginLines(Phase::Opening);
    Append(BattleDialogue::Opening);
}

void BattleProgress::Start(bool photo, bool record)
{
    if (IsActive()) return;
    m_photo = photo;
    m_record = record;
    ResetAttempt();
}

const char* BattleProgress::Speaker() const
{
    return m_phase == Phase::Choosing || m_lines.empty() ? "시스템" : m_lines[m_page].speaker.c_str();
}

const char* BattleProgress::Message() const
{
    return m_phase == Phase::Choosing || m_lines.empty() ?
        "그림자의 행동 예고를 보고 명령을 선택하세요." : m_lines[m_page].text.c_str();
}

StoryVisual BattleProgress::Visual() const
{
    return m_phase == Phase::Choosing || m_lines.empty() ? StoryVisual::Both : m_lines[m_page].visual;
}

bool BattleProgress::CanUse(Command command, const Player& player) const
{
    if (m_phase != Phase::Choosing || player.GetHP() == 0 || player.GetLife() == 0) return false;
    switch (command)
    {
    case Command::Attack:
    case Command::Defend: return true;
    case Command::Heal: return m_potions > 0 && player.GetHP() < 100;
    case Command::Clue: return (m_photo || m_record) && !m_clueUsed;
    default: return false;
    }
}

bool BattleProgress::Choose(Command command, Player& player)
{
    m_sound = Sound::None;
    if (!CanUse(command, player)) return false;
    BeginLines(Phase::PlayerResult);
    char message[256];
    switch (command)
    {
    case Command::Attack:
    {
        const int damage = (std::min)(m_enemyHP, 20);
        m_enemyHP -= damage;
        sprintf_s(message, "공격이 적중했다. 적 HP -%d.", damage);
        Append(BattleDialogue::Attack, "B05:1", message);
        m_sound = Sound::Attack;
        break;
    }
    case Command::Defend:
        m_defending = true;
        Append(BattleDialogue::Defend);
        break;
    case Command::Heal:
    {
        const int before = player.GetHP();
        player.Heal(30);
        --m_potions;
        sprintf_s(message, "회복 아이템을 사용했다. HP +%d. 남은 회복약 %d개.", player.GetHP() - before, m_potions);
        Append(BattleDialogue::Heal, "B09:1", message);
        m_sound = Sound::Heal;
        break;
    }
    case Command::Clue:
    {
        const int damage = (std::min)(m_enemyHP, 40);
        m_enemyHP -= damage;
        m_clueUsed = true;
        const bool both = m_photo && m_record;
        sprintf_s(message, "%s 적 HP -%d.", both ? "두 단서가 같은 사건을 증명한다." :
            m_photo ? "사진 속 행동이 그림자의 주장과 충돌한다." : "사고 기록이 그림자의 주장과 충돌한다.", damage);
        Append(both ? BattleDialogue::BothClues : m_photo ? BattleDialogue::Photo : BattleDialogue::Record,
            both ? "B14C:1" : m_photo ? "B14A:1" : "B14B:1", message);
        m_sound = Sound::Attack;
        break;
    }
    }
    if (m_enemyHP == 0)
    {
        // Commit the win once, before any further input or enemy retaliation.
        player.AddScore(20);
        m_phase = Phase::Victory;
        Append(BattleDialogue::Victory);
    }
    return true;
}

void BattleProgress::NextTurn()
{
    m_strong = !m_strong;
    ++m_turn;
    BeginLines(Phase::Forecast);
    Append(m_strong ? BattleDialogue::StrongForecast : BattleDialogue::NormalForecast);
}

void BattleProgress::Relations(const Player& player)
{
    BeginLines(Phase::Interlude);
    if (player.GetHP() <= 50 && !m_lowHPShown)
    {
        m_lowHPShown = true;
        Append(BattleDialogue::LowHP);
    }
    if (m_clueUsed && !m_clueShown)
    {
        m_clueShown = true;
        Append(BattleDialogue::ClueRelation);
    }
    if (m_enemyHP <= 40 && !m_weakEnemyShown)
    {
        m_weakEnemyShown = true;
        Append(BattleDialogue::WeakEnemy);
    }
    if (m_lines.empty()) NextTurn();
}

bool BattleProgress::Advance(Player& player)
{
    m_sound = Sound::None;
    if (m_phase == Phase::Inactive || m_phase == Phase::Choosing || IsFinished()) return false;
    if (m_page + 1 < m_lines.size())
    {
        ++m_page;
        return true;
    }
    switch (m_phase)
    {
    case Phase::Opening:
    case Phase::Forecast: m_phase = Phase::Choosing; break;
    case Phase::PlayerResult:
    {
        const bool defending = m_defending;
        const int damage = (std::min)(player.GetHP(), defending ? 10 : ExpectedDamage());
        player.TakeDamage(damage);
        m_defending = false;
        BeginLines(Phase::EnemyResult);
        char message[256];
        sprintf_s(message, "%s HP -%d.", defending ? "방어로 충격을 줄였다." :
            m_strong ? "강한 충격을 받았다." : "그림자의 공격을 받았다.", damage);
        Append(defending ? BattleDialogue::BlockedHit : m_strong ? BattleDialogue::StrongHit : BattleDialogue::NormalHit,
            defending ? "B21:1" : m_strong ? "B20:1" : "B19:1", message);
        m_sound = Sound::Attack;
        break;
    }
    case Phase::EnemyResult:
        // Resolve death before optional relationship dialogue or the next turn.
        if (player.GetHP() == 0)
        {
            if (player.GetLife() == 0) m_phase = Phase::Lost;
            else
            {
                BeginLines(Phase::Retry);
                Append(BattleDialogue::Retry);
            }
        }
        else Relations(player);
        break;
    case Phase::Interlude: NextTurn(); break;
    case Phase::Retry: player.Retry(); ResetAttempt(); break;
    case Phase::Victory: m_phase = Phase::Won; break;
    default: return false;
    }
    return true;
}
