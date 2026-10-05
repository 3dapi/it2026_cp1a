#include "CEnemy.h"



int CEnemy::Init(int texture_right, int texture_left)
{
	m_Boar_right_tx = texture_right;
	m_Boar_left_tx = texture_left;

	m_Width = g2_TextureWidth(m_Boar_right_tx) * m_Scale.x;
	m_Height = g2_TextureHeight(m_Boar_right_tx) * m_Scale.y;

	m_CurHp = m_MaxHp;

	m_Active = false;

	return 0;
}

int CEnemy::Update(float playerX, float playerY)
{
	if (!m_Active) // 활성화된 적만 데이터 업데이트
		return 0;

	auto moveX = playerX - m_PosX;
	auto moveY = playerY - m_PosY;

	if (moveX < 0.0f)
		m_IsLeft = true;
	else if (moveX > 0.0f)
		m_IsLeft = false;

	auto length = sqrt(moveX * moveX + moveY * moveY);

	if (length != 0.0f)
	{
		moveX /= length;
		moveY /= length;

		m_PosX += moveX * m_Speed;
		m_PosY += moveY * m_Speed;
	}

	m_Draw_Pos = { m_PosX - m_Width / 2.0f,
			m_PosY - m_Height / 2.0f };


	return 0;
}

int CEnemy::Render()
{
	if (!m_Active) // 활성화된 적만 렌더링
		return 0;

	if (m_IsLeft)
		g2_Draw2D(m_Boar_left_tx, {}, &m_Draw_Pos, &m_Scale, {});
	else
		g2_Draw2D(m_Boar_right_tx, {}, &m_Draw_Pos, &m_Scale, {});

	return 0;
}

int CEnemy::Destroy()
{
	return 0;
}

void CEnemy::TakeDamage(int damage)
{
	m_CurHp -= damage;
	if (m_CurHp < 0)
	{
		m_CurHp = 0;
	}
}

bool CEnemy::IsDead()
{
	return m_CurHp <= 0;
}

VEC2 CEnemy::GetPosition()
{
	return { m_PosX, m_PosY };
}

void CEnemy::SetPosition(float x, float y)
{
	m_PosX = x;
	m_PosY = y;

	m_Draw_Pos = { m_PosX - m_Width / 2.0f,
					m_PosY - m_Height / 2.0f };
}

void CEnemy::Activate(float x, float y)
{
	m_PosX = x;
	m_PosY = y;

	m_CurHp = m_MaxHp; // 체력 초기화

	m_Draw_Pos = { m_PosX - m_Width / 2.0f,
					m_PosY - m_Height / 2.0f };

	m_Active = true;
}

void CEnemy::Deactivate()
{
	m_Active = false;
}

bool CEnemy::IsActive()
{
	return m_Active;
}

RECT CEnemy::GetCollisionRect()
{
	RECT rc{};

	// 실제 이미지보다 작게
	float width = m_Width * 0.9f;
	float height = m_Height * 0.9f;

	rc.left = m_PosX - width / 2;
	rc.right = m_PosX + width / 2;
	rc.top = m_PosY - height / 2;
	rc.bottom = m_PosY + height / 2;

	return rc;
}
