#include "Player.h"

int Player::Init()
{
	// texture 
	this->m_txPlayer = g2_TextureLoad("Resource/Texture/sport_yellow.png");

	// sound
	this->m_laneChangeSound = g2_SoundLoad("Resource/Sound/lane_change.mp3");

	return 0;
}

int Player::Destroy()
{
	g2_TextureRelease(m_txPlayer);
	g2_SoundRelease(m_laneChangeSound);
	return 0;
}

void Player::Reset()
{
	m_position = VEC2(585.5f, Track::OUTER_BOTTOM_Y);
	m_speed = 500.f;
	m_trackSection = TrackSection::BottomStraight;
	m_curveAngle = 0.f;
	m_rotationAngle = 0.f;
	m_lane = TrackLane::Outer;
	m_currentRadius = Track::OUTER_LANE_RADIUS;
	m_wasMouseDown = (g2_GetMouseEvent(0) == 3);
	m_didChangeLane = false;
}

int Player::Update(float deltaTime)
{
	m_didChangeLane = false;

	bool isMouseDown = (g2_GetMouseEvent(0) == 3);

	if (isMouseDown && !m_wasMouseDown)
	{
		if (TrackLane::Outer == m_lane)
		{
			m_lane = TrackLane::Inner;
		}
		else
		{
			m_lane = TrackLane::Outer;
		}
		
		m_didChangeLane = true;

		g2_SoundReset(m_laneChangeSound);
		g2_SoundPlay(m_laneChangeSound);
	}
	m_wasMouseDown = isMouseDown;

	m_currentRadius = (TrackLane::Outer == m_lane)
		? Track::OUTER_LANE_RADIUS
		: Track::INNER_LANE_RADIUS;

	switch (m_trackSection)
	{
	case TrackSection::BottomStraight:
	{
		m_position.x -= m_speed * deltaTime;
		m_position.y = Track::CURVE_POS_Y + m_currentRadius;
		m_rotationAngle = 0.f;
	}break;

	case TrackSection::LeftCurve:
	{
		m_curveAngle -= (m_speed / m_currentRadius) * deltaTime;

		m_position.x = Track::LEFT_CURVE_POS_X
			+ m_currentRadius * -std::cos(m_curveAngle);

		m_position.y = Track::CURVE_POS_Y
			+ m_currentRadius * std::sin(m_curveAngle);

		m_rotationAngle = m_curveAngle - Track::PI / 2.0f;
	}break;

	case TrackSection::TopStraight:
	{
		m_position.x += m_speed * deltaTime;
		m_position.y = Track::CURVE_POS_Y - m_currentRadius;
		m_rotationAngle = -Track::PI;
	}break;

	case TrackSection::RightCurve:
	{
		m_curveAngle -= (m_speed / m_currentRadius) * deltaTime;

		m_position.x = Track::RIGHT_CURVE_POS_X
			+ m_currentRadius * -std::cos(m_curveAngle);

		m_position.y = Track::CURVE_POS_Y
			+ m_currentRadius * std::sin(m_curveAngle);

		m_rotationAngle = m_curveAngle - Track::PI / 2.0f;
	}break;

	default:
		break;
	}

	CheckPlayerTrackSection();
	return 0;
}

int Player::Render()
{
	VEC2 playerDrawPos
	{
		m_position.x - g2_TextureWidth(m_txPlayer) * 0.5f,
		m_position.y - g2_TextureHeight(m_txPlayer) * 0.5f
	};

	g2_Draw2D(
		m_txPlayer, nullptr, &playerDrawPos,
		nullptr, &m_position, m_rotationAngle
	);
	return 0;
}

VEC2 Player::GetPosition() const
{
	return m_position;
}

TrackSection Player::GetTrackSection() const
{
	return m_trackSection;
}

void Player::IncreaseSpeed(float amount)
{
	m_speed += amount;
}

float Player::GetRotationAngle() const
{
	return m_rotationAngle;
}

bool Player::DidChangeLane() const
{
	return m_didChangeLane;
}

void Player::CheckPlayerTrackSection()
{
	switch (m_trackSection)
	{
	case TrackSection::BottomStraight:
	{
		if (m_position.x <= Track::LEFT_CURVE_POS_X)
		{
			m_position.x = Track::LEFT_CURVE_POS_X;
			m_trackSection = TrackSection::LeftCurve;
			m_curveAngle = Track::PI / 2.f;
		}
	}break;

	case TrackSection::LeftCurve:
	{
		if (m_curveAngle <= -Track::PI / 2.0f)
		{
			m_position.x = Track::LEFT_CURVE_POS_X;
			m_position.y = Track::CURVE_POS_Y - m_currentRadius;
			m_curveAngle = -Track::PI / 2.0f;
			m_trackSection = TrackSection::TopStraight;
			m_rotationAngle = -Track::PI;
		}
	}break;

	case TrackSection::TopStraight:
	{
		if (m_position.x >= Track::RIGHT_CURVE_POS_X)
		{
			m_position.x = Track::RIGHT_CURVE_POS_X;
			m_trackSection = TrackSection::RightCurve;
			m_curveAngle = -Track::PI / 2.0f;
		}
	}break;

	case TrackSection::RightCurve:
	{
		if (m_curveAngle <= -3.0f * Track::PI / 2.0f)
		{
			m_position.x = Track::RIGHT_CURVE_POS_X;
			m_position.y = Track::CURVE_POS_Y + m_currentRadius;
			m_curveAngle = -3.0f * Track::PI / 2.0f;
			m_trackSection = TrackSection::BottomStraight;
			m_rotationAngle = 0.0f;
		}
	}break;

	default:
		break;
	}
}