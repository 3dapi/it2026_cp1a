#include "GameObject.h"
void GameObject::Update(float delta)
{
	if (_anim)
	{
		_anim->Play(delta);
	}
}
void GameObject::Render()
{
	if (!_anim) return;
	
	Texture* curTex = _anim->GetCurrentTexture();
	/*printf("GameObject = %p / Animator = %p / Texture = %p\n",
		this,
		_anim,
		curTex);*/

	if (curTex == nullptr) return;
	
	curTex->SetPos(_pos);
	curTex->Print();
}

void GameObject::SetPos(VEC2 pos) { _pos = pos; }
VEC2 GameObject::GetPos() const { return _pos; }
Animator* GameObject::GetAnimator() const { return _anim; }