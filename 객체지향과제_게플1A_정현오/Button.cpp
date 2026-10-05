#include "Button.h"

int Button::Init(string imagePath)
{
	m_texture = g2_TextureLoad(imagePath.c_str());
	m_width = g2_TextureWidth(m_texture);
	m_height = g2_TextureHeight(m_texture);
	g2_SoundRelease(m_pressSound);
	m_pressSound = g2_SoundLoad("resource/audio/buttonPress.mp3");

	return 0;
}

int Button::Render()
{
	VEC2 scale = GetDrawScale();
	VEC2 position = transform.position;

	position.x -= m_width * (scale.x - transform.scale.x) * 0.5f;
	position.y -= m_height * (scale.y - transform.scale.y) * 0.5f;

	if (m_pressed && g2_TimeGetTime() < m_pressEndTime)
	{
		position.y += 2.0f;
	}

	VEC2 center{
		position.x + transform.center.x * scale.x,
		position.y + transform.center.y * scale.y
	};

	float rotation = GetRotation();

	g2_Draw2D(m_texture, nullptr, &position, &scale, &center, rotation);

	return 0;
}

int Button::Destroy()
{
	g2_TextureRelease(m_texture);
	return 0;
}

VEC2 Button::GetDrawScale()
{
	VEC2 scale = transform.scale;

	if (m_selected)
	{
		scale.x *= 1.1f;
		scale.y *= 1.1f;
	}

	return scale;
}

void Button::SetSelected(bool selected)
{
	m_selected = selected;

	if (!m_selected)
	{
		m_pressed = false;
	}
}

void Button::SetPressed(bool pressed)
{
	if (m_selected && !m_pressed && pressed)
	{
		m_pressed = true;
		m_pressEndTime = g2_TimeGetTime() + 80;

		g2_SoundPlay(m_pressSound, false);
	}
}

void Button::SetAction(int (*action)(void))
{
	m_action = action;
}

bool Button::CanAction() const
{
	return m_pressed && g2_TimeGetTime() >= m_pressEndTime + 10;
}

int Button::Press()
{
	m_selected = false;
	m_pressed = false;

	if (nullptr != m_action)
	{
		return m_action();
	}

	return 0;
}