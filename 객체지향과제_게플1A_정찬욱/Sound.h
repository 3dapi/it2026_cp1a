#pragma once

// 효과음 파일을 불러오고 재생하며 종료 시 장치를 정리
class Sound
{
public:
    enum class Effect { Button, Select, Roll };
    Sound() = default;
    ~Sound() { Destroy(); }

    // 같은 소리 장치를 여러 객체가 중복 해제하지 않도록 복사를 금지
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;
    void Init();
    void Play(Effect effect);
    void Destroy();
    void StartBgm();

private:
    // 버튼, 주사위 선택, 주사위 굴리기 순서
    // 효과음과 별도로 배경음악 장치를 관리
    unsigned int m_bgm = 0;
    unsigned int m_sounds[3] = { 0, 0, 0 };
};
