#pragma once
#include <glc2d.h>

#include "Animator.h"

class GameObject
{
protected:
	VEC2 _pos;
	Animator* _anim;
public:
	GameObject(VEC2 pos = { 0,0 })
		: _pos(pos)
	{
		_anim = new Animator;
	}

	virtual ~GameObject()
	{
		printf(
			"GameObject Delete : %p / Animator = %p\n",
			this,
			_anim
		);
		if (_anim)
		{
			delete _anim;
			_anim = nullptr;
		}
	}

	virtual void Update(float delta);
	virtual void Render();
	
	void SetPos(VEC2 pos);
	VEC2 GetPos() const;
	Animator* GetAnimator() const;
};

