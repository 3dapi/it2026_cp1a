#include "WindowImage.h"
#include "Window.h"
#include "glc2d.h"

#include <iostream>
#include <string.h>

extern Window window;
// 이후에 활용할 수 있도록 이미지의 주소,인덱스,너비,폭을 설정함.
void WindowImage::Initialize(int sprite, const float x , const float y )
{
	SetImage(sprite);

	if (x != INPUT_NULL)
	{
		SetPosX(x);
	}
	if (y != INPUT_NULL)
	{
		SetPosY(y);
	}

	window.AddImage(this);
}
// 좌표를 입력하면 해당 위치에 이미지 표시.
// 렌더를 안하면 바로 다음render()에서 아라야시키 당하는 듯.
// m_pos는 생략 가능한 듯.
void WindowImage::Draw()
{
	g2_Draw2D(m_sprite, nullptr, &m_pos);
}

// 이걸 호출하면 이후에 Render해도 이미지가 나타나지 않음.
// 다만 Setup을 다시 해주면 부활함.
//	- 정확히는 유사한 객체를 다시 만드는 것이라 할 수 있을 듯.
void WindowImage::Release()
{
	g2_TextureRelease(m_sprite);
}



void WindowImage::SetImage(int sprite)
{
	//m_imageP= fileName;
	//m_sprite = g2_TextureLoad(m_imageP);
	m_sprite = sprite;
	m_width = g2_TextureWidth(m_sprite);
	m_height = g2_TextureHeight(m_sprite);
}

void WindowImage::SetAlpha(int alpha)
{
	g2_DrawAlphaOption(alpha);
}

void WindowImage::SetPos(const float x, const float y)
{
	SetPosX(x);
	SetPosY(y);
}

void WindowImage::SetPosX(const float x)
{
	m_pos.x = x;
}

void WindowImage::SetPosY(const float y)
{
	m_pos.y = y;
}

int WindowImage::GetIndex()
{
	return m_sprite;
}

int WindowImage::GetWidth()
{
	return m_width;
}

int WindowImage::GetHeight()
{
	return m_height;
}

float WindowImage::GetPosX()
{
	return m_pos.x;
}

float WindowImage::GetPosY()
{
	return m_pos.y;
}

