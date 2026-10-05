#pragma once
#include "glc2d.h"


enum class TrackSection
{
	BottomStraight,
	LeftCurve,
	TopStraight,
	RightCurve
};

enum class TrackLane
{
	Inner,
	Outer
};

class Track
{
public:
	// curve position
	static constexpr float LEFT_CURVE_POS_X		{ 334.0f };
	static constexpr float RIGHT_CURVE_POS_X	{ 946.0f };
	static constexpr float CURVE_POS_Y			{ 358.0f };

	// lane radii
	static constexpr float INNER_LANE_RADIUS	{ 204.0f };
	static constexpr float OUTER_LANE_RADIUS	{ 252.0f };

	// straight lane positions
	static constexpr float INNER_TOP_Y
	{
		CURVE_POS_Y - INNER_LANE_RADIUS
	};
	static constexpr float INNER_BOTTOM_Y
	{
		CURVE_POS_Y + INNER_LANE_RADIUS
	};

	static constexpr float OUTER_TOP_Y
	{
		CURVE_POS_Y - OUTER_LANE_RADIUS
	};
	static constexpr float OUTER_BOTTOM_Y
	{
		CURVE_POS_Y + OUTER_LANE_RADIUS
	};

	
	static constexpr float PI{ 3.14159265358979323846f };
};

