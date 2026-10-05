#include "SceneHowToPlay.h"

#include "CApplication.h"

void SceneHowToPlay::Update(CApplication& application, const KEYCODE* keys)
{
    if (CApplication::IsKeyPressed(keys, VK_RETURN) ||
        CApplication::IsKeyPressed(keys, VK_ESCAPE))
    {
        application.ChangeScene(SceneId::MainMenu);
    }
}

void SceneHowToPlay::Render(const CApplication& application) const
{
    const GameResources& resources = application.GetResources();
    application.DrawFullScreenTexture(resources.battleBackground);

    g2_FontDrawText(
        resources.headingFont,
        { 380, 38, 760, 88 },
        0xFFFFD166,
        "HOW TO PLAY");

    g2_FontDrawText(
        resources.bodyFont,
        { 115, 120, 920, 155 },
        0xFFE6EDF3,
        "Defeat two goblins, then the final goblin shaman boss.");
    g2_FontDrawText(
        resources.bodyFont,
        { 115, 168, 920, 203 },
        0xFFE6EDF3,
        "J: Attack for 8 damage. Boss HP: 56.");
    g2_FontDrawText(
        resources.bodyFont,
        { 115, 216, 920, 251 },
        0xFFE6EDF3,
        "K: Guard the counterattack. 60% chance to take no damage.");
    g2_FontDrawText(
        resources.bodyFont,
        { 115, 264, 920, 299 },
        0xFFE6EDF3,
        "Enemy damage: Goblin 7 / Boss 10. Press K before it lands.");
    g2_FontDrawText(
        resources.bodyFont,
        { 115, 312, 920, 347 },
        0xFFE6EDF3,
        "Each normal goblin drops 1-2 potions. Start with 0.");
    g2_FontDrawText(
        resources.bodyFont,
        { 115, 360, 920, 395 },
        0xFF70E000,
        "L: Use 1 potion on your turn. Random heal: 10-20 HP.");
    g2_FontDrawText(resources.bodyFont, { 115, 408, 940, 443 },
        0xFFE6EDF3, "HP cannot exceed 50. At full HP, potions are not used.");
    g2_FontDrawText(resources.bodyFont, { 115, 456, 940, 491 },
        0xFFE6EDF3, "Healing does not trigger a counterattack.");
    g2_FontDrawText(
        resources.bodyFont,
        { 310, 550, 820, 590 },
        0xFFB8C5D6,
        "Enter or Esc: Return to Main Menu");
}
