#include "SoundManager.h"
#include <cstdio>
#include <Windows.h>
#include <mmsystem.h>
#include <cstring>

#pragma comment(lib, "winmm.lib")

// PCM WAV 데이터를 읽고 waveOut으로 반복 재생한다.
// 게임 갱신 중 동기식 MCI 명령을 실행하지 않는다.
bool SoundManager::LoadBgm()
{
    if (!m_bgmData.empty()) return true;
    FILE* file = nullptr;
    fopen_s(&file, "resource/sound/bgm.wav", "rb");
    if (!file) return false;

    char riff[12];
    bool formatFound = false;
    bool dataFound = false;
    bool valid = fread(riff, 1, 12, file) == 12 &&
        std::memcmp(riff, "RIFF", 4) == 0 && std::memcmp(riff + 8, "WAVE", 4) == 0;
    while (valid && !(formatFound && dataFound))
    {
        char id[4];
        DWORD size = 0;
        if (fread(id, 1, 4, file) != 4 || fread(&size, 4, 1, file) != 1) break;
        const long next = ftell(file) + static_cast<long>(size) + (size & 1);
        if (size > 32 * 1024 * 1024) { valid = false; break; }
        if (std::memcmp(id, "fmt ", 4) == 0)
        {
            m_bgmFormat = {};
            valid = size >= 16 && fread(&m_bgmFormat, 1, 16, file) == 16;
            formatFound = valid;
        }
        else if (std::memcmp(id, "data", 4) == 0)
        {
            m_bgmData.resize(size);
            valid = size > 0 && fread(m_bgmData.data(), 1, size, file) == size;
            dataFound = valid;
        }
        if (fseek(file, next, SEEK_SET) != 0) { valid = false; break; }
    }
    fclose(file);
    valid = valid && formatFound && dataFound &&
        m_bgmFormat.wFormatTag == WAVE_FORMAT_PCM &&
        m_bgmFormat.nChannels > 0 && m_bgmFormat.nSamplesPerSec > 0 &&
        m_bgmFormat.nBlockAlign > 0;
    if (!valid) m_bgmData.clear();
    return valid;
}

void SoundManager::PlayBgm()
{
    StopBgm();
    if (!LoadBgm()) return;
    MMRESULT result = waveOutOpen(&m_bgmDevice, WAVE_MAPPER,
        &m_bgmFormat, 0, 0, CALLBACK_NULL);
    if (result != MMSYSERR_NOERROR) { m_bgmDevice = nullptr; return; }

    m_bgmHeader = {};
    m_bgmHeader.lpData = m_bgmData.data();
    m_bgmHeader.dwBufferLength = static_cast<DWORD>(m_bgmData.size());
    result = waveOutPrepareHeader(m_bgmDevice, &m_bgmHeader, sizeof(m_bgmHeader));
    if (result != MMSYSERR_NOERROR) { StopBgm(); return; }
    m_bgmPrepared = true;
    m_bgmHeader.dwFlags |= WHDR_BEGINLOOP | WHDR_ENDLOOP;
    m_bgmHeader.dwLoops = 0xFFFFFFFF;
    result = waveOutWrite(m_bgmDevice, &m_bgmHeader, sizeof(m_bgmHeader));
    if (result != MMSYSERR_NOERROR) StopBgm();
}

void SoundManager::Update()
{
    // 반복 재생은 오디오 장치에서 처리한다.
}

void SoundManager::StopBgm()
{
    if (!m_bgmDevice) return;
    waveOutReset(m_bgmDevice);
    if (m_bgmPrepared)
    {
        waveOutUnprepareHeader(m_bgmDevice, &m_bgmHeader, sizeof(m_bgmHeader));
        m_bgmPrepared = false;
    }
    waveOutClose(m_bgmDevice);
    m_bgmDevice = nullptr;
    m_bgmHeader = {};
}

void SoundManager::Stop()
{
    StopBgm();
    PlaySoundA(NULL, NULL, 0);
}

void SoundManager::PlayEffect(const char* fileName)
{
    PlaySoundA(fileName, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}

void SoundManager::PlayStart()
{
    PlayEffect("resource/sound/start.wav");
}

void SoundManager::PlayCollect()
{
    PlayEffect("resource/sound/collect.wav");
}

void SoundManager::PlayHit()
{
    PlayEffect("resource/sound/hit.wav");
}

void SoundManager::PlayClear()
{
    PlayEffect("resource/sound/clear.wav");
}

void SoundManager::PlayFail()
{
    PlayEffect("resource/sound/fail.wav");
}
