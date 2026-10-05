#include "SceneGameBegin.h"
#include "glc2d.h"
#include "CApplication.h"
int SceneGameBegin::Init()
{
	{
		this->m_txbg = g2_TextureLoad("resource/texture/tex_Ui/Map_Ui.png");
	}
	{
		this->m_tx1 = g2_TextureLoad("resource/texture/tex_Ui/1.png");
		this->m_tx2 = g2_TextureLoad("resource/texture/tex_Ui/2.png");
		this->m_tx3 = g2_TextureLoad("resource/texture/tex_Ui/3.png");
		this->m_tx4 = g2_TextureLoad("resource/texture/tex_Ui/4.png");
		this->m_tx5 = g2_TextureLoad("resource/texture/tex_Ui/5.png");
		this->m_tx6 = g2_TextureLoad("resource/texture/tex_Ui/6.png");
	}
	this->Ysound = g2_SoundLoad("resource/texture/Ysound.mp3");
	

	return 0;


}

int SceneGameBegin::Destroy()
{
	return 0;
}

int SceneGameBegin::Update()
{
	const KEYCODE* pKey = g2_GetKeyboard();

	if (pKey[VK_SPACE])
	{
		printf("Space");
		if (!g2_SoundIsPlaying(Ysound))
		{
			g2_SoundPlay(Ysound);
		}
	}
	
	return 0;
}

int SceneGameBegin::Render()
{
	{
		VEC2 posTitle{ 1100.F,800.0F };
		g2_Draw2D(m_tx1, nullptr, &posTitle);
	}
	{
		VEC2 posTitle{ 100.0F, 0.0 };
		g2_Draw2D(m_txbg,nullptr, &posTitle);
	}
	{
		VEC2 posTitle{ 1100.F,800.0F };
		g2_Draw2D(m_tx2, nullptr, &posTitle);
	}
	{
		VEC2 posTitle{ 1100.F,800.0F };
		g2_Draw2D(m_tx3, nullptr, &posTitle);
	}
	{
		VEC2 posTitle{ 1100.F,800.0F };
		g2_Draw2D(m_tx4, nullptr, &posTitle);
	}
	{
		VEC2 posTitle{ 1100.F,800.0F };
		g2_Draw2D(m_tx5, nullptr, &posTitle);
	}
	{
		VEC2 posTitle{ 1100.F,800.0F };
		g2_Draw2D(m_tx6, nullptr, &posTitle);
	}

	return 0;
}

