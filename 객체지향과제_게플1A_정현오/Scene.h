#pragma once
#include "glc2d.h"

enum SceneRequest
{
    SCENE_KEEP = 0,
    SCENE_BEGIN,
    SCENE_PLAY,
    SCENE_RESULT,
    SCENE_QUIT,
};

class Scene
{
public:
    virtual ~Scene() = default;

    virtual int Init() = 0;
    virtual int Update(float deltaTime) = 0;
    virtual int Render() = 0;
    virtual int Destroy() = 0;
};

