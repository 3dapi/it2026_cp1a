#include "Flag.h"

Flag::Flag(VEC2 pos, E_FlagColorType col)
	: GameObject(pos),_colorType(col)
{
	string prefix = (_colorType == E_FlagColorType::BLUE)?
		"rsc/imgs/Flag/Blue/" 
		: "rsc/imgs/Flag/White/";


	auto upTex = std::make_unique<Texture>(prefix + "Up.png", pos);
	upTex->Load();
	
	auto upClip = std::make_unique<AnimationClip>("Up", 0.1f, false);
	upClip->AddTexture(std::move(upTex));


	auto downTex = std::make_unique<Texture>(prefix + "Down.png", pos);
	downTex->Load();

	auto downClip = std::make_unique<AnimationClip>("Down", 0.1f, false);
	downClip->AddTexture(std::move(downTex));

	_anim->AddClip("Up", std::move(upClip));
	_anim->AddClip("Down", std::move(downClip));

	_anim->ChangeClip("Down");
	_isUp = false;
}

void Flag::SetFlag(bool b)
{
	_isUp = b;
	
	ChangeAnim();
}

void Flag::ChangeFlag()
{
	_isUp = !_isUp;

	ChangeAnim();
}

void Flag::ChangeAnim()
{
	if (_isUp)
		_anim->ChangeClip("Up");
	else
		_anim->ChangeClip("Down");
}

E_FlagColorType Flag::GetColor() const { return _colorType; }
bool Flag::IsUp() const { return _isUp; }