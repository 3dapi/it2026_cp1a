#include "Piece.h"

// 생성자: 말 위치 0으로 초기화
Piece::Piece()
    : m_position(0)
{
}

// Init(): 시작 위치 지정
void Piece::Init(int startPosition)
{
    m_position = startPosition;
}

// Reset(): 말 위치 재설정
void Piece::Reset(int startPosition)
{
    m_position = startPosition;
}

// Move(): 방향 / 한 칸 이동
void Piece::Move(int direction)
{
    m_position += direction;
}

int Piece::GetPosition() const
{
    return m_position;
}
