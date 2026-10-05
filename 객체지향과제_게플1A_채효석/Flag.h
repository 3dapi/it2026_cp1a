#pragma once
#include "GameObject.h"
#include <memory>
enum class E_FlagColorType
{
	WHITE,
	BLUE
};

class Flag : public GameObject
{
private:
	E_FlagColorType _colorType;
	bool _isUp = false;

public :
	Flag(VEC2 pos, E_FlagColorType col);

	void ChangeFlag();
	void SetFlag(bool b);

	void ChangeAnim();

	E_FlagColorType GetColor() const;
	bool IsUp() const;
};

