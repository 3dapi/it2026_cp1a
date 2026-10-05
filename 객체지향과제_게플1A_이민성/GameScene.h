#pragma once

#include <glc2d.h>

class CApplication;

class GameScene
{
public:
    virtual ~GameScene() = default;

    virtual void Update(CApplication& application, const KEYCODE* keys) = 0;
    virtual void Render(const CApplication& application) const = 0;
};
