#include "CMap.h"
#include "glc2d.h"

int CMap::Init()
{
	m_TxMap = g2_TextureLoad("Texture/map.png");


	return 0;
}

int CMap::Update()
{



	return 0;
}

int CMap::Render()
{
	g2_Draw2D(m_TxMap, {});


	return 0;
}

int CMap::Destroy()
{
	g2_TextureRelease(m_TxMap);


	return 0;
}