#pragma once
#include "GameObject.h"

enum class E_StateType
{
	IDLE,
	WRONG,
	CORRECT
};

class Cat : public GameObject
{
private:
	E_StateType _state = E_StateType::IDLE;

public:
	Cat(VEC2 pos);

	void Update(float delta) override;

	void SetState(E_StateType st);
	E_StateType GetState();
};

