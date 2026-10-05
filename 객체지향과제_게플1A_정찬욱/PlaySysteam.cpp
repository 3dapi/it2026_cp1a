#include "PlaySysteam.h"
#include "glc2d.h"
#include <stdio.h>


namespace
{
    constexpr float TrayX = 560.0f;
    constexpr float TrayY = 250.0f;
    constexpr float TraySize = 100.0f;
    constexpr float TrayStep = 120.0f;
    constexpr float HeldX = 480.0f;
    constexpr float HeldY = 635.0f;
    constexpr float HeldSize = 70.0f;
    constexpr float HeldStep = 86.0f;
}

bool PlaySysteam::Init()
{
    for (int i = 0; i < Dice::Count; ++i)
    {
        m_slots[i] = -1;
        m_traySlots[i] = i;
    }
    m_selectedCount = 0;
    m_mousePressed = m_spacePressed = false;
    m_yacht.Init();
    m_restartPressed = false;
    m_sound.Init();
    return m_dice.Init();
}

void PlaySysteam::SelectDice(int index)
{
    if (!m_yacht.HasRolled() || m_yacht.Finished() || index < 0 || index >= Dice::Count) return;


    // 주사위를 옮길 때는 현재 숫자를 변경하지 않음
    if (IsSelected(index))
    {
        // 왼쪽 위부터 순서대로 가장 앞의 빈
        // 자리를 찾는다
        int emptySlot = -1;
        for (int slot = 0; slot < Dice::Count; ++slot)
        {
            bool occupied = false;
            for (int i = 0; i < Dice::Count; ++i)
                if (!IsSelected(i) && m_traySlots[i] == slot) occupied = true;
            if (!occupied) { emptySlot = slot; break; }
        }
        if (emptySlot < 0) return;
        m_traySlots[index] = emptySlot;
        const int removedSlot = m_slots[index];
        m_slots[index] = -1;
        for (int i = 0; i < Dice::Count; ++i)
            if (m_slots[i] > removedSlot) --m_slots[i];
        --m_selectedCount;
        m_sound.Play(Sound::Effect::Select);
    }
    else
    {
        m_slots[index] = m_selectedCount++;
        m_traySlots[index] = -1;
        m_sound.Play(Sound::Effect::Select);
    }
}

void PlaySysteam::RollUnselected()
{
    if (!m_yacht.CanRoll()) return;
    bool rolled = false;
    for (int i = 0; i < Dice::Count; ++i)
    {
        if (!IsSelected(i))
        {
            m_dice.RollOne(i);
            rolled = true;
        }
    }
    // 모두 고정된 경우에는 던지는 소리를 내지 않습니다.
    if (rolled)
    {
        m_yacht.OnRolled();
        m_sound.Play(Sound::Effect::Roll);
    }
}

void PlaySysteam::Update()
{
    const bool mouseDown = g2_GetMouseEvent(0) != 0;
    if (mouseDown && !m_mousePressed)
    {
        const float mx = static_cast<float>(g2_GetMouseX());
        const float my = static_cast<float>(g2_GetMouseY());
        if (!ClickScore(mx, my))
        for (int i = 0; i < Dice::Count; ++i)
        {
            const bool held = IsSelected(i);
            const float x = held ? HeldX + m_slots[i] * HeldStep
                                 : TrayX + (m_traySlots[i] % 3) * TrayStep;
            const float y = held ? HeldY : TrayY + (m_traySlots[i] / 3) * TrayStep;
            const float size = held ? HeldSize : TraySize;
            if (mx >= x && mx < x + size && my >= y && my < y + size)
            {
                SelectDice(i);
                break;
            }
        }
    }
    m_mousePressed = mouseDown;
    const KEYCODE* keys = g2_GetKeyboard();
    const bool spaceDown = keys && keys[VK_SPACE] != 0;

    // 같은 순간에 클릭과 굴리기가 입력되면 선택부터 처리합니다.
    if (spaceDown && !m_spacePressed)
    {
        m_sound.Play(Sound::Effect::Button);
        RollUnselected();
    }
    m_spacePressed = spaceDown;
    const bool restartDown = keys && keys['R'] != 0;
    if (m_yacht.Finished() && restartDown && !m_restartPressed)
    {
        m_yacht.Restart();
        ResetTurn();
    }
    m_restartPressed = restartDown;
}

void PlaySysteam::Render()
{
    if (!m_yacht.HasRolled() || m_yacht.Finished()) return;
    for (int i = 0; i < Dice::Count; ++i)
    {
        if (IsSelected(i))
            m_dice.RenderOne(i, HeldX + m_slots[i] * HeldStep, HeldY, HeldSize);
        else
            m_dice.RenderOne(i, TrayX + (m_traySlots[i] % 3) * TrayStep,
                            TrayY + (m_traySlots[i] / 3) * TrayStep, TraySize);
    }
}

void PlaySysteam::Destroy()
{
    m_sound.Destroy();
    m_dice.Destroy();
    for (int i = 0; i < Dice::Count; ++i)
    {
        m_slots[i] = -1;
        m_traySlots[i] = i;
    }
    m_selectedCount = 0;
    m_mousePressed = m_spacePressed = false;
}


void PlaySysteam::CurrentDice(int (&values)[5]) const
{
    for (int i = 0; i < Dice::Count; ++i) values[i] = m_dice.GetNumber(i);
}

void PlaySysteam::ResetTurn()
{
    // 다음 턴에는 고정을 풀고 첫 굴리기를 기다립니다.
    for (int i = 0; i < Dice::Count; ++i)
    {
        m_slots[i] = -1;
        m_traySlots[i] = i;
    }
    m_selectedCount = 0;
}

bool PlaySysteam::ClickScore(float x, float y)
{
    int values[5];
    CurrentDice(values);
    const auto result = m_yacht.ClickScore(x, y, values);
    if (result == YachtSystem::ClickResult::Recorded)
    {
        m_sound.Play(Sound::Effect::Button);
        ResetTurn();
    }
    return result != YachtSystem::ClickResult::Outside;
}

void PlaySysteam::RenderScoreboard()
{
    int values[5];
    CurrentDice(values);
    m_yacht.Render(values);
}
