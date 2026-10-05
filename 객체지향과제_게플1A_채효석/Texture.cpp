#include "Texture.h"

int Texture::Load()
{
	_texture = g2_TextureLoad(_filePath.c_str());

	printf("Texture Load : %s / handle = %d\n",
		_filePath.c_str(),
		_texture);

	return 0;
}

//Life-Cycle 에서 호출
int Texture::Print()
{
	VEC2 pos(_texturePos);
	g2_DrawAlphaOption(2);
	g2_Draw2D(_texture, nullptr, &pos);
	g2_DrawAlphaOption(0);

	return 0;
}

int Texture::Release()
{
	if (_texture == -1) return 0;

	g2_TextureRelease(_texture);
	_texture = -1;

	return 0;
}

int Texture::SetPos(VEC2 pos)
{
	_texturePos = pos;
	return 0;
}

VEC2 Texture::GetPos()
{
	return _texturePos;
}

std::string Texture::GetFilePath()
{
	return _filePath;
}