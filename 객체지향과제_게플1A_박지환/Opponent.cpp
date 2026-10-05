#include "Opponent.h"

int Opponent::Init()
{
	// texture loading
	m_txOpponent = g2_TextureLoad("Resource/Texture/sport_red.png");
	return 0;
}

int Opponent::Destroy()
{
	g2_TextureRelease(m_txOpponent);
	return 0;
}

int Opponent::Update(float deltaTime)
{
	float targetRadius = (TrackLane::Outer == m_lane)
		? Track::OUTER_LANE_RADIUS
		: Track::INNER_LANE_RADIUS;

	float changeAmount = m_lineChangeSpeed * deltaTime;

	if (m_currentRadius < targetRadius)
	{
		m_currentRadius += changeAmount;

		if (m_currentRadius > targetRadius)
		{
			m_currentRadius = targetRadius;
		}
	}
	else if (m_currentRadius > targetRadius)
	{
		m_currentRadius -= changeAmount;
		if (m_currentRadius < targetRadius)
		{
			m_currentRadius = targetRadius;
		}
	}

	switch (m_trackSection)
	{
	case TrackSection::BottomStraight:
	{
		m_position.x += m_speed * deltaTime;
		m_position.y = Track::CURVE_POS_Y + m_currentRadius;
		m_rotationAngle = 0.f;
	}break;

	case TrackSection::RightCurve:
	{
		m_curveAngle -= (m_speed / m_currentRadius) * deltaTime;

		m_position.x = Track::RIGHT_CURVE_POS_X
			+ m_currentRadius * std::cos(m_curveAngle);

		m_position.y = Track::CURVE_POS_Y
			+ m_currentRadius * std::sin(m_curveAngle);

		m_rotationAngle = m_curveAngle - Track::PI / 2.0f;
	}break;

	case TrackSection::TopStraight:
	{
		m_position.x -= m_speed * deltaTime;
		m_position.y = Track::CURVE_POS_Y - m_currentRadius;
		m_rotationAngle = -Track::PI;
	}break;

	case TrackSection::LeftCurve:
	{
		m_curveAngle -= (m_speed / m_currentRadius) * deltaTime;

		m_position.x = Track::LEFT_CURVE_POS_X
			+ m_currentRadius * std::cos(m_curveAngle);

		m_position.y = Track::CURVE_POS_Y
			+ m_currentRadius * std::sin(m_curveAngle);

		m_rotationAngle = m_curveAngle - Track::PI / 2.0f;
	}break;

	default:
		break;
	}

	bool isCurve =
		m_trackSection == TrackSection::RightCurve ||
		m_trackSection == TrackSection::LeftCurve;

	if (isCurve &&
		!m_laneDecisionDone &&
		m_curveAngle <= m_laneDecisionAngle)
	{
		int result = m_laneDistribution(m_randomEngine);

		m_lane = (result == 1)
			? TrackLane::Inner
			: TrackLane::Outer;

		m_laneDecisionDone = true;
	}

	CheckOpponentTrackSection();
	return 0;
}

int Opponent::Render()
{
	VEC2 opponentDrawPos
	{
		m_position.x - g2_TextureWidth(m_txOpponent) * 0.5f,
		m_position.y - g2_TextureHeight(m_txOpponent) * 0.5f
	};

	g2_Draw2D(
		m_txOpponent, nullptr, &opponentDrawPos,
		nullptr, &m_position, -m_rotationAngle
	);

	return 0;
}

VEC2 Opponent::GetPosition() const
{
	return m_position;
}

float Opponent::GetRotationAngle() const
{
	return m_rotationAngle;
}

void Opponent::IncreaseSpeed(float amount)
{
	m_speed += amount;
}

void Opponent::Reset()
{
	m_position = VEC2(695.5f, Track::OUTER_BOTTOM_Y);
	m_speed = 500.f;
	m_trackSection = TrackSection::BottomStraight;
	m_curveAngle = 0.f;
	m_rotationAngle = 0.f;
	m_lane = TrackLane::Outer;
	m_currentRadius = Track::OUTER_LANE_RADIUS;
	m_laneDecisionDone = true;
	m_laneDecisionAngle = 0.f;
}

void Opponent::CheckOpponentTrackSection()
{
	switch (m_trackSection)
	{
	case TrackSection::BottomStraight:
	{
		if (m_position.x >= Track::RIGHT_CURVE_POS_X)
		{
			m_position.x = Track::RIGHT_CURVE_POS_X;
			m_trackSection = TrackSection::RightCurve;
			m_curveAngle = Track::PI / 2.f;
			m_laneDecisionAngle =
				m_curveAngle - m_decisionOffset(m_randomEngine);
			m_laneDecisionDone = false;
		}
	}break;

	case TrackSection::RightCurve:
	{
		if (m_curveAngle <= -Track::PI / 2.f)
		{
			m_position.x = Track::RIGHT_CURVE_POS_X;
			m_position.y = Track::CURVE_POS_Y - m_currentRadius;
			m_curveAngle = -Track::PI / 2.f;
			m_trackSection = TrackSection::TopStraight;
			m_rotationAngle = -Track::PI;
		}
	}break;

	case TrackSection::TopStraight:
	{
		if (m_position.x <= Track::LEFT_CURVE_POS_X)
		{
			m_position.x = Track::LEFT_CURVE_POS_X;
			m_trackSection = TrackSection::LeftCurve;
			m_curveAngle = -Track::PI / 2.f;
			m_laneDecisionAngle =
				m_curveAngle - m_decisionOffset(m_randomEngine);
			m_laneDecisionDone = false;
		}
	}break;

	case TrackSection::LeftCurve:
	{
		if (m_curveAngle <= -3.f * Track::PI / 2.f)
		{
			m_position.x = Track::LEFT_CURVE_POS_X;
			m_position.y = Track::CURVE_POS_Y + m_currentRadius;
			m_curveAngle = -3.f * Track::PI / 2.f;
			m_trackSection = TrackSection::BottomStraight;
			m_rotationAngle = 0.0f;
		}
	}break;

	default:
		break;
	}
}