#include "SceneBegin.h"
#include "glc2d.h"

int SceneBegin::Init()
{
	this->m_txt = g2_TextureLoad("resouce/tetris.png");
	
	m_font = g2_FontCreate(
		"Arial",
		24
	);

	
	return 0;
}

int SceneBegin::Update()
{
	const KEYCODE* key = g2_GetKeyboard();

	if (key[VK_RETURN] == EINPUT_DOWN ||
		key[VK_SPACE] == EINPUT_DOWN)
	{
		return 1;
	}

	return 0;
}

int SceneBegin::Render()
{

	g2_Draw2D(
		m_txt,
		nullptr,
		&pos,
		&scale
	);

	RECT rc =
	{
		220,    
		500,    
		650,    
		550     
	};

	g2_FontDrawText(
		m_font,
		rc,
		0xFFFFFFFF,
		"PRESS ENTER OR SPACE TO START"
	);


	return 0;
}

int SceneBegin::Destroy()
{
	
	return 0;
}
