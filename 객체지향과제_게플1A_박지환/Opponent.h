#pragma once
#include "glc2d.h"
#include "Track.h"	
#include <cmath>
#include <random>

class Opponent
{
public:
	int Init();
	int Destroy();
	int Render();
	int Update(float deltaTime);

public:
	void Reset();
	VEC2 GetPosition() const;
	float GetRotationAngle() const;
	void IncreaseSpeed(float amount);

private:
	int m_txOpponent			{ -1 };

	void CheckOpponentTrackSection();

	VEC2 m_position				{ 695.5f, Track::OUTER_BOTTOM_Y };
	float m_speed				{ 500.f };
	float m_curveAngle			{ 0.f };
	float m_rotationAngle		{ 0.f };

	float m_currentRadius		{ Track::OUTER_LANE_RADIUS };
	float m_lineChangeSpeed		{ 60.f };
	std::mt19937 m_randomEngine	{ std::random_device{}() };
	std::uniform_int_distribution<int> m_laneDistribution{ 1, 2 };	// 1: Inner, 2: Outer
	float m_laneDecisionAngle	{ 0.0f };							// 현재 곡선에서 목표 차선을 결정할 각도
	bool m_laneDecisionDone{ true };								// 목표 차선 결정 여부

	std::uniform_real_distribution<float> m_decisionOffset
	{
		Track::PI / 6.0f, 
		Track::PI / 2.0f
	};

	TrackSection m_trackSection
	{
		TrackSection::BottomStraight
	};

	TrackLane m_lane
	{
		TrackLane::Outer
	};
};

