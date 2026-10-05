#pragma once

#include <glc2d.h>

#include <string>

#include "SceneBattlePreview.h"
#include "SceneHowToPlay.h"
#include "SceneMainMenu.h"

enum class SceneId
{
    MainMenu,
    HowToPlay,
    BattlePreview
};

struct GameResources
{
    int mainBackground = -1;
    int battleBackground = -1;
    int playerTexture = -1;
    int playerHit = -1;
    int playerGuard = -1;
    int playerHeal = -1;
    int goblin = -1;
    int goblinHit = -1;
    int goblinShaman = -1;
    int goblinShamanHit = -1;
    int potion = -1;
    int attackKey = -1;
    int guardKey = -1;
    int mainMenuMusic = -1;
    int stageMusic = -1;
    int playerAttackSound = -1;
    int uiSelectSound = -1;
    int guardSuccessSound = -1;
    int guardFailSound = -1;
    int playerHealSound = -1;
    int headingFont = -1;
    int menuFont = -1;
    int bodyFont = -1;
};

class CApplication
{
public:
    static constexpr int ScreenWidth = 1024;
    static constexpr int ScreenHeight = 640;

    int Init();
    int Update();
    int Render() const;
    int Destroy();

    void ChangeScene(SceneId nextScene);
    void RequestExit() const;

    const GameResources& GetResources() const;

    void DrawFullScreenTexture(int textureKey) const;
    void DrawTexture(int textureKey, const RECT& destination,
        const RECT* source = nullptr, DWORD color = 0xFFFFFFFF) const;

    void PlaySound(int soundKey) const;

    static bool IsKeyPressed(const KEYCODE* keys, int key);

private:
    bool CreateGameWindow();
    bool CreateFonts();
    bool LoadTextures();
    bool LoadSounds();
    void ReleaseTexture(int& textureKey);
    void ReleaseSound(int& soundKey);
    std::string BuildTexturePath(const char* fileName) const;
    std::string BuildSoundPath(const char* fileName) const;
    void StartMusicForScene(SceneId scene);
    void StopMusic();

    GameScene& ActiveScene();
    const GameScene& ActiveScene() const;

    bool initialized_ = false;
    bool windowCreated_ = false;
    SceneId currentScene_ = SceneId::MainMenu;
    GameResources resources_;
    SceneMainMenu mainMenuScene_;
    SceneHowToPlay howToPlayScene_;
    SceneBattlePreview battlePreviewScene_;
};
