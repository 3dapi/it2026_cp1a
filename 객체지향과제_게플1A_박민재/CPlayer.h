#pragma once
#include "glc2d.h"

#define InvincibleTime 1000

// 공격 방향 
enum {
	ATTACK_LEFT,
	ATTACK_RIGHT
};

class CPlayer
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

	VEC2 GetPosition();									// 플레이어 좌표 전달 함수
	RECT GetCollisionRect();							// 플레이어 Rect 전달 함수 (충돌 처리)
	
	void TakeDamage(int damage);						// 플레이어가 데미지를 입었을 때 처리
	int GetCurHp();									// 현재 체력 전달 함수
	bool IsDead();										// 플레이어가 사망했을 때 처리	
	void MovePlayer(); 									// 플레이어 이동 처리

	bool IsInvincible();								// 플레이어 무적 여부 확인
	void StartInvincible();								// 무적 활성화

	bool IsAttack();									// 공격 여부 확인
	RECT GetAttackRect();								// 공격 범위 Rect 전달 함수
	int GetAttackPoint();								// 공격력 전달 함수
	
private:

	float m_PosX = 500.0f;								// 중심 좌표X
	float m_PosY = 300.0f;								// 중심 좌표Y

	float m_Width{};
	float m_Height{};

	VEC2 m_Draw_Pos{};									// 좌상단 좌표
	VEC2 m_Scale = { 0.5f, 0.5f };						// 스케일

	VEC2 m_Attack_Effect_Pos{};
	int m_AttackEffectTime = 100;						// 이펙트 출력 시간

	int m_MaxHp = 100;									// 총 체력
	int m_CurHp{}; 										// 현재 체력

	float m_Speed = 0.05f;								// 이동 속도

	int m_Attack = 80;									// 공격력

	int m_Direction{};									// 공격 방향
	bool m_IsAttacking = false;
	long long m_AttackTimer = 0;
	int m_AttackSpeed = 750;							// 공격 속도 (0.75간격)
	float m_attackWidth{};								// 공격 범위 넓이
	float m_attackHeight{};								// 공격 범위 높이
	RECT m_AttackRect{};								// 공격 범위 Rect

	long long m_InvincibleTimer{};

	int m_Char_turn_right_tx = -1;						// 캐릭터 텍스처
	int m_Char_turn_left_tx = -1;

	int m_Attack_Effect_right_tx = -1;
	int m_Attack_Effect_left_tx = -1;
};

