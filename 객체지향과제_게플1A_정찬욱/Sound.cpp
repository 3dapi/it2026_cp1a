#include "Sound.h"
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")

void Sound::Init()
{

    Destroy();
    const wchar_t* files[3] = {
        L"버튼 눌렀을때.mp3", L"주사위 선택했을때.mp3",
        L"던질때.mp3"
    };

    wchar_t executable[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, executable, MAX_PATH);
    std::wstring folder(executable);
    folder = folder.substr(0, folder.find_last_of(L"\\/") + 1);

    for (int i = 0; i < 3; ++i)
    {
        // 실행 파일 옆의 소리를 먼저 찾고 프로젝트 폴더도 확인
        std::wstring path = folder + L"sound/" + files[i];
        if (GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES)
            path = std::wstring(L"sound/") + files[i];

        MCI_OPEN_PARMSW open = {};
        open.lpstrDeviceType = L"mpegvideo";
        open.lpstrElementName = path.c_str();

        const MCIERROR error = mciSendCommandW(0, MCI_OPEN,
            MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, reinterpret_cast<DWORD_PTR>(&open));
        if (error == 0) m_sounds[i] = open.wDeviceID;
        else printf("Sound %d load failed: %lu\n", i, static_cast<unsigned long>(error));
    }
    StartBgm();
}

void Sound::Play(Effect effect)
{
    const int index = static_cast<int>(effect);
    if (index < 0 || index >= 3 || m_sounds[index] == 0) return;


    // 빠르게 다시 누르면 해당 효과음을 처음부터 재생
    mciSendCommandW(m_sounds[index], MCI_STOP, 0, 0);
    MCI_PLAY_PARMS play = {};
    play.dwFrom = 0;

    const MCIERROR error = mciSendCommandW(m_sounds[index], MCI_PLAY,
        MCI_FROM, reinterpret_cast<DWORD_PTR>(&play));
    if (error) printf("Sound %d play failed: %lu\n", index, static_cast<unsigned long>(error));
}

void Sound::Destroy()
{
    if (m_bgm) mciSendCommandW(m_bgm, MCI_CLOSE, 0, 0);
    m_bgm = 0;

    for (int i = 0; i < 3; ++i)
    {
        if (m_sounds[i]) mciSendCommandW(m_sounds[i], MCI_CLOSE, 0, 0);
        m_sounds[i] = 0;
    }
}

void Sound::StartBgm()
{
    if (m_bgm) mciSendCommandW(m_bgm, MCI_CLOSE, 0, 0);
    m_bgm = 0;

    wchar_t executable[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, executable, MAX_PATH);
    std::wstring folder(executable);

    folder = folder.substr(0, folder.find_last_of(L"\\/") + 1);
    std::wstring path = folder + L"sound/bgm.mp3";

    if (GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES)
        path = L"sound/bgm.mp3";


    // 한글 경로를 지원하며 배경음악은 효과음과 독립적으로 재생함
    MCI_OPEN_PARMSW open = {};
    open.lpstrDeviceType = L"mpegvideo";
    open.lpstrElementName = path.c_str();
    open.lpstrAlias = L"yacht_background_music";

    MCIERROR error = mciSendCommandW(0, MCI_OPEN,
        MCI_OPEN_TYPE | MCI_OPEN_ELEMENT | MCI_OPEN_ALIAS,
        reinterpret_cast<DWORD_PTR>(&open));
    if (error)
    {
        printf("BGM load failed: %lu\n", static_cast<unsigned long>(error));
        return;
    }

    m_bgm = open.wDeviceID;

    // 효과음을 가리지 않도록 음량을 25퍼센트로 설정
    error = mciSendStringW(L"setaudio yacht_background_music volume to 100", nullptr, 0, nullptr);
    if (error) printf("BGM volume failed: %lu\n", static_cast<unsigned long>(error));


    // 음악이 끝나면 자동으로 처음부터 반복
    error = mciSendStringW(L"play yacht_background_music repeat", nullptr, 0, nullptr);
    if (error) printf("BGM play failed: %lu\n", static_cast<unsigned long>(error));
}
