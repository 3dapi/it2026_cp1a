#pragma once
#include <string>
#include <glc2d.h>
class Texture
{
protected :
	std::string _filePath;

	int _texture = -1;
	VEC2 _texturePos{0,0};

public :
	Texture(std::string path, VEC2 pos) : _filePath(path), _texturePos(pos) 
	{
		printf("Texture CREATE : %p / %s\n",
			this,
			_filePath.c_str());
	}
	~Texture()
	{
		printf("Texture DELETE : %p\n", this);
		Release();
	}
	int Load();
	int Release();
	int Print();

	int SetPos(VEC2 pos);
	VEC2 GetPos();

	std::string GetFilePath();
};

