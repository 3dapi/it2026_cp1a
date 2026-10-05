#pragma once
#include "GameObject.h"

class Image : public GameObject
{
public:
	Image();
	~Image() override;

	int Update(float deltaTime) override;
	int Render() override;
};