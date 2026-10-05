#include "CApplication.h"

#include <cstdio>

extern CApplication g_app;

namespace
{
int AppUpdate()
{
    return g_app.Update();
}

int AppRender()
{
    return g_app.Render();
}
}

int CApplication::Init()
{
    if (initialized_)
    {
        return 0;
    }

    const int initResult = g2_InitSdk();
    if (initResult != 0)
    {
        std::fprintf(stderr, "glc2d SDK initialization failed: %d\n", initResult);
        return 1;
    }

    g2_SetFrameMove(AppUpdate);
    g2_SetRender(AppRender);
    g2_SetClearColor(0xFF101827);
    g2_SetStateShow(0);
    g2_SetCursorShow(0);

    if (!CreateGameWindow() || !CreateFonts() || !LoadTextures() || !LoadSounds())
    {
        Destroy();
        return 1;
    }

    currentScene_ = SceneId::MainMenu;
    initialized_ = true;
    StartMusicForScene(currentScene_);
    std::printf("DUNGEON DECK initialized.\n");
    return 0;
}

int CApplication::Update()
{
    ActiveScene().Update(*this, g2_GetKeyboard());
    return 0;
}

int CApplication::Render() const
{
    ActiveScene().Render(*this);
    return 0;
}

int CApplication::Destroy()
{
    StopMusic();
    ReleaseSound(resources_.playerHealSound);
    ReleaseSound(resources_.guardFailSound);
    ReleaseSound(resources_.guardSuccessSound);
    ReleaseSound(resources_.uiSelectSound);
    ReleaseSound(resources_.playerAttackSound);
    ReleaseSound(resources_.stageMusic);
    ReleaseSound(resources_.mainMenuMusic);
    ReleaseTexture(resources_.guardKey);
    ReleaseTexture(resources_.potion);
    ReleaseTexture(resources_.goblinShamanHit);
    ReleaseTexture(resources_.goblinShaman);
    ReleaseTexture(resources_.playerHeal);
    ReleaseTexture(resources_.attackKey);
    ReleaseTexture(resources_.goblinHit);
    ReleaseTexture(resources_.goblin);
    ReleaseTexture(resources_.playerGuard);
    ReleaseTexture(resources_.playerHit);
    ReleaseTexture(resources_.playerTexture);
    ReleaseTexture(resources_.battleBackground);
    ReleaseTexture(resources_.mainBackground);

    if (windowCreated_)
    {
        g2_DestroyWin();
        windowCreated_ = false;
    }

    initialized_ = false;
    return 0;
}

void CApplication::ChangeScene(SceneId nextScene)
{
    if (nextScene == SceneId::BattlePreview)
    {
        battlePreviewScene_.Reset();
    }
    if (currentScene_ != nextScene)
    {
        StopMusic();
        currentScene_ = nextScene;
        StartMusicForScene(currentScene_);
    }
}

void CApplication::RequestExit() const
{
    PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
}

const GameResources& CApplication::GetResources() const
{
    return resources_;
}

void CApplication::PlaySound(int soundKey) const
{
    if (soundKey < 0)
    {
        return;
    }

    g2_SoundReset(soundKey);
    g2_SoundPlay(soundKey);
}

void CApplication::DrawFullScreenTexture(int textureKey) const
{
    if (textureKey < 0)
    {
        return;
    }

    const int textureWidth = g2_TextureWidth(textureKey);
    const int textureHeight = g2_TextureHeight(textureKey);

    if (textureWidth <= 0 || textureHeight <= 0)
    {
        return;
    }

    VEC2 position(0.0f, 0.0f);
    VEC2 scale(
        static_cast<float>(ScreenWidth) / static_cast<float>(textureWidth),
        static_cast<float>(ScreenHeight) / static_cast<float>(textureHeight));

    g2_Draw2D(textureKey, nullptr, &position, &scale);
}

bool CApplication::IsKeyPressed(const KEYCODE* keys, int key)
{
    return keys != nullptr && keys[key] == EINPUT_DOWN;
}

void CApplication::DrawTexture(int textureKey, const RECT& destination,
    const RECT* source, DWORD color) const
{
    if (textureKey < 0)
    {
        return;
    }
    const int width = source != nullptr
        ? source->right - source->left : g2_TextureWidth(textureKey);
    const int height = source != nullptr
        ? source->bottom - source->top : g2_TextureHeight(textureKey);
    if (width <= 0 || height <= 0)
    {
        return;
    }
    VEC2 position(static_cast<float>(destination.left), static_cast<float>(destination.top));
    VEC2 scale(static_cast<float>(destination.right - destination.left) / width,
        static_cast<float>(destination.bottom - destination.top) / height);
    g2_DrawAlphaOption(0);
    g2_Draw2D(textureKey, source, &position, &scale, nullptr, 0.0f, color);
}

bool CApplication::CreateGameWindow()
{
    const int createResult = g2_CreateWin(
        100,
        70,
        ScreenWidth,
        ScreenHeight,
        "DUNGEON DECK - glc2d Card RPG",
        true);

    if (createResult != 0)
    {
        std::fprintf(stderr, "glc2d window creation failed: %d\n", createResult);
        return false;
    }

    windowCreated_ = true;
    return true;
}

bool CApplication::CreateFonts()
{
    resources_.headingFont = g2_FontCreate("Arial", 30, 0);
    resources_.menuFont = g2_FontCreate("Arial", 27, 0);
    resources_.bodyFont = g2_FontCreate("Consolas", 20, 0);

    if (resources_.headingFont < 0 ||
        resources_.menuFont < 0 ||
        resources_.bodyFont < 0)
    {
        std::fprintf(stderr, "glc2d font creation failed.\n");
        return false;
    }

    return true;
}

bool CApplication::LoadTextures()
{
    const struct TextureEntry
    {
        const char* file;
        int* key;
    } entries[] =
    {
        { "Main.png", &resources_.mainBackground },
        { "InGame.png", &resources_.battleBackground },
        { "Player.png", &resources_.playerTexture },
        { "Player_Hit.png", &resources_.playerHit },
        { "Player_Guard.png", &resources_.playerGuard },
        { "Player_Heal.png", &resources_.playerHeal },
        { "Goblin.png", &resources_.goblin },
        { "Goblin_Hit.png", &resources_.goblinHit },
        { "GoblinShaman.png", &resources_.goblinShaman },
        { "GoblinShaman_Hit.png", &resources_.goblinShamanHit },
        { "Potion.png", &resources_.potion },
        { "J.png", &resources_.attackKey },
        { "K.png", &resources_.guardKey }
    };
    for (const TextureEntry& entry : entries)
    {
        const std::string path = BuildTexturePath(entry.file);
        *entry.key = g2_TextureLoad(path.c_str());
        if (*entry.key < 0)
        {
            std::fprintf(stderr, "Cannot load texture: %s\n", path.c_str());
            return false;
        }
    }
    return true;
}

bool CApplication::LoadSounds()
{
    const struct SoundEntry
    {
        const char* file;
        int* key;
    } entries[] =
    {
        { "MainMenu_InDarkness.wav", &resources_.mainMenuMusic },
        { "Boss_Alternative_Welcome.mp3", &resources_.stageMusic },
        { "Player_ProjectileCast01.wav", &resources_.playerAttackSound },
        { "UI_Select.wav", &resources_.uiSelectSound },
        { "Monster_KnightSwing.wav", &resources_.guardSuccessSound },
        { "Monster_KnightReady.wav", &resources_.guardFailSound },
        { "Player_Heal.wav", &resources_.playerHealSound }
    };

    for (const SoundEntry& entry : entries)
    {
        const std::string path = BuildSoundPath(entry.file);
        *entry.key = g2_SoundLoad(path.c_str());
        if (*entry.key < 0)
        {
            std::fprintf(stderr, "Cannot load sound: %s\n", path.c_str());
            return false;
        }
    }
    return true;
}

void CApplication::ReleaseTexture(int& textureKey)
{
    if (textureKey >= 0)
    {
        g2_TextureRelease(textureKey);
        textureKey = -1;
    }
}

void CApplication::ReleaseSound(int& soundKey)
{
    if (soundKey >= 0)
    {
        g2_SoundRelease(soundKey);
        soundKey = -1;
    }
}

std::string CApplication::BuildTexturePath(const char* fileName) const
{
    char executablePath[MAX_PATH] = {};
    const DWORD pathLength = GetModuleFileNameA(nullptr, executablePath, MAX_PATH);

    if (pathLength == 0 || pathLength >= MAX_PATH)
    {
        return std::string("texture\\") + fileName;
    }

    std::string directory(executablePath, pathLength);
    const std::string::size_type slashPosition = directory.find_last_of("\\/");

    if (slashPosition != std::string::npos)
    {
        directory.erase(slashPosition + 1);
    }
    else
    {
        directory.clear();
    }

    return directory + "texture\\" + fileName;
}

std::string CApplication::BuildSoundPath(const char* fileName) const
{
    char executablePath[MAX_PATH] = {};
    const DWORD pathLength = GetModuleFileNameA(nullptr, executablePath, MAX_PATH);

    if (pathLength == 0 || pathLength >= MAX_PATH)
    {
        return std::string("sound\\") + fileName;
    }

    std::string directory(executablePath, pathLength);
    const std::string::size_type slashPosition = directory.find_last_of("\\/");

    if (slashPosition != std::string::npos)
    {
        directory.erase(slashPosition + 1);
    }
    else
    {
        directory.clear();
    }

    return directory + "sound\\" + fileName;
}

void CApplication::StartMusicForScene(SceneId scene)
{
    const int musicKey = scene == SceneId::MainMenu
        ? resources_.mainMenuMusic :
        scene == SceneId::BattlePreview ? resources_.stageMusic : -1;
    if (musicKey >= 0)
    {
        g2_SoundReset(musicKey);
        g2_SoundPlay(musicKey, true);
    }
}

void CApplication::StopMusic()
{
    if (resources_.mainMenuMusic >= 0)
    {
        g2_SoundStop(resources_.mainMenuMusic);
    }
    if (resources_.stageMusic >= 0)
    {
        g2_SoundStop(resources_.stageMusic);
    }
}

GameScene& CApplication::ActiveScene()
{
    switch (currentScene_)
    {
    case SceneId::HowToPlay:
        return howToPlayScene_;

    case SceneId::BattlePreview:
        return battlePreviewScene_;

    case SceneId::MainMenu:
    default:
        return mainMenuScene_;
    }
}

const GameScene& CApplication::ActiveScene() const
{
    switch (currentScene_)
    {
    case SceneId::HowToPlay:
        return howToPlayScene_;

    case SceneId::BattlePreview:
        return battlePreviewScene_;

    case SceneId::MainMenu:
    default:
        return mainMenuScene_;
    }
}
