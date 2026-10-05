#include "CPlayer.h"

bool g_IsTurn = false;

int CPlayer::Init()
{
	// 플레이어 좌/우 이미지 로드
	m_Char_turn_right_tx = g2_TextureLoad("Texture/player_right.png");
	m_Char_turn_left_tx = g2_TextureLoad("Texture/player_left.png");
	m_Attack_Effect_right_tx = g2_TextureLoad("Texture/attack_right.png");
	m_Attack_Effect_left_tx = g2_TextureLoad("Texture/attack_left.png");

	// 이미지 크기 확인
	m_Width = g2_TextureWidth(m_Char_turn_right_tx) * m_Scale.x;
	m_Height = g2_TextureHeight(m_Char_turn_right_tx) * m_Scale.y;

	// 플레이어 초기 세팅
	m_CurHp = m_MaxHp; 

	m_InvincibleTimer = 0;
	m_Direction = ATTACK_RIGHT;
	
	m_AttackTimer = g2_TimeGetTime();

	return 0;
}

int CPlayer::Update()
{
	
	MovePlayer();

	m_Draw_Pos = {
		m_PosX - m_Width / 2.0f,
		m_PosY - m_Height / 2.0f
	};

	m_Attack_Effect_Pos = {
		(float)m_AttackRect.left,
		(float)m_AttackRect.top
	};

	if (m_IsAttacking)
	{
		long long current = g2_TimeGetTime();

		if (current - m_AttackTimer >= m_AttackEffectTime)
			m_IsAttacking = false;
	}

	return 0;
}

int CPlayer::Render()
{
	
	if (!g_IsTurn)
		g2_Draw2D(m_Char_turn_right_tx, {}, &m_Draw_Pos, &m_Scale, {});
	else
		g2_Draw2D(m_Char_turn_left_tx, {}, &m_Draw_Pos, &m_Scale, {});
	
	if (m_IsAttacking)
	{
		if (m_Direction == ATTACK_RIGHT) {
			g2_Draw2D(m_Attack_Effect_right_tx, {}, &m_Attack_Effect_Pos, {});
		}
		else
			g2_Draw2D(m_Attack_Effect_left_tx, {}, &m_Attack_Effect_Pos, {});
	}

	return 0;
}

int CPlayer::Destroy()
{
	g2_TextureRelease(m_Char_turn_right_tx);
	g2_TextureRelease(m_Char_turn_left_tx);
	g2_TextureRelease(m_Attack_Effect_right_tx);
	g2_TextureRelease(m_Attack_Effect_left_tx);

	return 0;
}

VEC2 CPlayer::GetPosition()
{
	return { m_PosX, m_PosY };
}

void CPlayer::TakeDamage(int damage)
{
	m_CurHp -= damage;
	if (m_CurHp < 0)
	{
		m_CurHp = 0;
	}
}

int CPlayer::GetCurHp()
{
	return m_CurHp;
}

bool CPlayer::IsDead()
{
	return m_CurHp <= 0;
}

void CPlayer::MovePlayer()
{
	const KEYCODE* keyboard = g2_GetKeyboard();

	auto moveX = 0.0f;
	auto moveY = 0.0f;

	if (keyboard['A'] != EINPUT_NONE)
	{
		g_IsTurn = true;
		moveX -= 1.0f;
		m_Direction = ATTACK_LEFT;
	}

	if (keyboard['D'] != EINPUT_NONE)
	{
		g_IsTurn = false;
		moveX += 1.0f;
		m_Direction = ATTACK_RIGHT;
	}

	if (keyboard['W'] != EINPUT_NONE)
	{
		moveY -= 1.0f;
	}

	if (keyboard['S'] != EINPUT_NONE)
	{
		moveY += 1.0f;
	}

	auto length = sqrt(moveX * moveX + moveY * moveY); // 이동 방향 벡터 생성

	if (length != 0.0f) // 벡터 졍규화
	{
		moveX /= length;
		moveY /= length;
	}

	m_PosX += moveX * m_Speed;
	m_PosY += moveY * m_Speed;

	// 플레이어 이동 범위 제한 - 화면 테두리 바깥으로 나가지 못하도록
	// 왼쪽
	if (m_PosX < m_Width / 2.0f)
	{
		m_PosX = m_Width / 2.0f;
	}
	// 오른쪽
	if (m_PosX > g2_GetScnW() - m_Width / 2.0f)
	{
		m_PosX = g2_GetScnW() - m_Width / 2.0f;
	}
	// 위
	if (m_PosY < m_Height / 2.0f)
	{
		m_PosY = m_Height / 2.0f;
	}
	// 아래
	if (m_PosY > g2_GetScnH() - m_Height / 2.0f)
	{
		m_PosY = g2_GetScnH() - m_Height / 2.0f;
	}
}


RECT CPlayer::GetCollisionRect()
{
	RECT rc{};

	// 실제 이미지보다 작게
	float width = m_Width * 0.7f; 
	float height = m_Height * 0.7f;

	rc.left = m_PosX - width / 2;
	rc.right = m_PosX + width / 2;
	rc.top = m_PosY - height / 2;
	rc.bottom = m_PosY + height / 2;

	return rc;
}

bool CPlayer::IsInvincible()
{
	long long current = g2_TimeGetTime();

	return  current - m_InvincibleTimer < InvincibleTime;
}

void CPlayer::StartInvincible()
{
	m_InvincibleTimer = g2_TimeGetTime();
}

bool CPlayer::IsAttack()
{
	long long current = g2_TimeGetTime();

	if (current - m_AttackTimer >= m_AttackSpeed)
	{
		m_AttackTimer = current;

		m_attackWidth = m_Width + 50.0f;
		m_attackHeight = m_Height + 50.0f;

		if (m_Direction == ATTACK_RIGHT)
		{
			m_AttackRect.left = m_PosX + m_Width / 2;
			m_AttackRect.right = m_AttackRect.left + m_attackWidth;
		}
		else if (m_Direction == ATTACK_LEFT)
		{
			m_AttackRect.right = m_PosX - m_Width / 2;
			m_AttackRect.left = m_AttackRect.right - m_attackWidth;
		}

		m_AttackRect.top = m_PosY - m_attackHeight / 2;
		m_AttackRect.bottom = m_PosY + m_attackHeight / 2;

		m_IsAttacking = true;
		return true;
	}
	return false;
}

RECT CPlayer::GetAttackRect()
{
	return m_AttackRect;
}

int CPlayer::GetAttackPoint()
{
	return m_Attack;
}
