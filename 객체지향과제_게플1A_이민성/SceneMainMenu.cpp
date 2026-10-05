#include "SceneMainMenu.h"

#include "CApplication.h"

void SceneMainMenu::Update(CApplication& application, const KEYCODE* keys)
{
    if (CApplication::IsKeyPressed(keys, VK_UP) ||
        CApplication::IsKeyPressed(keys, 'W'))
    {
        MoveSelection(-1);
        application.PlaySound(application.GetResources().uiSelectSound);
    }

    if (CApplication::IsKeyPressed(keys, VK_DOWN) ||
        CApplication::IsKeyPressed(keys, 'S'))
    {
        MoveSelection(1);
        application.PlaySound(application.GetResources().uiSelectSound);
    }

    if (CApplication::IsKeyPressed(keys, VK_RETURN))
    {
        application.PlaySound(application.GetResources().uiSelectSound);
        SelectCurrentItem(application);
    }

    if (CApplication::IsKeyPressed(keys, VK_ESCAPE))
    {
        application.RequestExit();
    }
}

void SceneMainMenu::Render(const CApplication& application) const
{
    const GameResources& resources = application.GetResources();
    application.DrawFullScreenTexture(resources.mainBackground);

    const char* menuItems[MenuCount] =
    {
        "GAME START",
        "HOW TO PLAY",
        "EXIT"
    };

    for (int index = 0; index < MenuCount; ++index)
    {
        const int top = 345 + index * 58;
        const DWORD color = index == selectedMenu_
            ? 0xFFFFD166
            : 0xFFE6EDF3;

        g2_FontDrawText(
            resources.menuFont,
            { 410, top, 740, top + 44 },
            color,
            "%s",
            menuItems[index]);
    }

    g2_FontDrawText(
        resources.bodyFont,
        { 345, 555, 875, 590 },
        0xFFB8C5D6,
        "W, S or Arrow Keys: Move");
    g2_FontDrawText(
        resources.bodyFont,
        { 390, 592, 830, 625 },
        0xFFB8C5D6,
        "Enter: Select   Esc: Exit");
}

void SceneMainMenu::MoveSelection(int direction)
{
    selectedMenu_ = (selectedMenu_ + direction + MenuCount) % MenuCount;
}

void SceneMainMenu::SelectCurrentItem(CApplication& application) const
{
    switch (selectedMenu_)
    {
    case 0:
        application.ChangeScene(SceneId::BattlePreview);
        break;

    case 1:
        application.ChangeScene(SceneId::HowToPlay);
        break;

    case 2:
        application.RequestExit();
        break;

    default:
        break;
    }
}
