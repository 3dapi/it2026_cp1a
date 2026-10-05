#pragma once
#include "GameObject.h"
#include <string>

using std::string;

class Button : public GameObject
{
public:
	int Init(string imagePath);
	int Render() override;
	int Destroy() override;

	void SetSelected(bool selected);
	void SetPressed(bool pressed);
	void SetAction(int (*action)(void));
	bool CanAction() const;
	int Press();

private:
	VEC2 GetDrawScale();

private:
	int m_texture			{ -1 };
	int m_pressSound		{ -1 };
	int m_width				{};
	int m_height			{};

	bool m_selected			{};
	bool m_pressed			{};

	long long m_pressEndTime{};

	int (*m_action)(void)	{};
};

