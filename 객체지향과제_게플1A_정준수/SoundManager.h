#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <vector>

class SoundManager
{
public:
    void PlayBgm();
    void Update();
    void StopBgm();
    void Stop();
    void PlayStart();
    void PlayCollect();
    void PlayHit();
    void PlayClear();
    void PlayFail();

private:
    void PlayEffect(const char* fileName);
    bool LoadBgm();
    HWAVEOUT m_bgmDevice = nullptr;
    WAVEHDR m_bgmHeader = {};
    WAVEFORMATEX m_bgmFormat = {};
    std::vector<char> m_bgmData;
    bool m_bgmPrepared = false;
};
