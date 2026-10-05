#pragma once

class Piece
{
private:
    int m_position;

public:
    Piece();

    void Init(int startPosition);
    void Move(int direction);
    void Reset(int startPosition);

    int GetPosition() const;
};
