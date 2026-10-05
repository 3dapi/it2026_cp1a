#pragma once
#include "Dice.h"
#include "Sound.h"
#include "YachtSystem.h"

class PlaySysteam
{

public:
    bool Init();
    void Update();
    void Render();
    void RenderScoreboard();
    void Destroy();
    void SelectDice(int index);
    void RollUnselected();


    // 유효한 번호이고 아래에 내려놓은 주사위인지 확인
    bool IsSelected(int index) const
    {
        return index >= 0
            && index < Dice::Count
            && m_slots[index] >= 0;
    }


    // 해당 주사위의 현재 숫자를 반환
    int GetNumber(int index) const
    {
        return m_dice.GetNumber(index);
    }


private:
    YachtSystem m_yacht;
    bool m_restartPressed = false;
    void ResetTurn();
    void CurrentDice(int (&values)[5]) const;
    bool ClickScore(float x, float y);
    Dice m_dice;
    Sound m_sound;


    // -1이면 바구니 안, 0 이상이면 아래쪽 고정 위치
    int m_slots[Dice::Count] = { -1, -1, -1, -1, -1 };


    // 각 주사위가 차지하는 바구니 안의 자리
    int m_traySlots[Dice::Count] = { 0, 1, 2, 3, 4 };


    // 아래에 고정한 주사위 개수
    int m_selectedCount = 0;


    // 직전 업데이트의 버튼 입력 상태
    bool m_mousePressed = false;
    bool m_spacePressed = false;
};