#pragma once

#include "GameScene.h"

class SceneMainMenu final : public GameScene
{
public:
    void Update(CApplication& application, const KEYCODE* keys) override;
    void Render(const CApplication& application) const override;

private:
    static constexpr int MenuCount = 3;

    void MoveSelection(int direction);
    void SelectCurrentItem(CApplication& application) const;

    int selectedMenu_ = 0;
};
