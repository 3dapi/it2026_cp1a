#include "Cat.h"

Cat::Cat(VEC2 pos)
	: GameObject(pos)
{
	string prefix = "rsc/imgs/Cats/Player/";

	//Idle
	auto idleTex = std::make_unique<Texture>(prefix + "Idle.png", pos);
	idleTex->Load();

	auto idleClip = std::make_unique<AnimationClip>("Idle", 0.1f, false);
	idleClip->AddTexture(std::move(idleTex));


	//Wrong
	auto wrongTex = std::make_unique<Texture>(prefix + "Wrong.png", pos);
	wrongTex->Load();

	auto wrongClip = std::make_unique<AnimationClip>("Wrong", 0.1f, false);
	wrongClip->AddTexture(std::move(wrongTex));


	//Correct
	auto correctTex = std::make_unique<Texture>(prefix + "Correct.png", pos);
	correctTex->Load();

	auto correctClip = std::make_unique<AnimationClip>("Correct", 0.1f, false);
	correctClip->AddTexture(std::move(correctTex));

	_anim->AddClip("Idle", std::move(idleClip));
	_anim->AddClip("Wrong", std::move(wrongClip));
	_anim->AddClip("Correct", std::move(correctClip));

	_anim->ChangeClip("Idle");
}

void Cat::Update(float delta)
{
	GameObject::Update(delta);

	switch (_state)
	{
	case E_StateType::IDLE:
		_anim->ChangeClip("Idle");
		break;
	case E_StateType::WRONG:
		_anim->ChangeClip("Wrong");
		break;
	case E_StateType::CORRECT:
		_anim->ChangeClip("Correct");
		break;
	}
}

void Cat::SetState(E_StateType st)
{
	_state = st;
}
E_StateType Cat::GetState()
{
	return _state;
}