# Target Catch 클래스 구성

## 관계

```text
main.cpp
  └─ Game
      ├─ Player
      ├─ Target
      ├─ Obstacle
      └─ SoundManager
```

## Game
- 역할: 게임 전체 상태, 점수, 시간, 그래픽 리소스와 게임 객체 관리
- 주요 데이터: `m_state`, `m_score`, `m_remainingTime`, texture id, 각 객체
- 주요 함수: `Init()`, `Update()`, `Render()`, `StartGame()`, `FinishGame()`, `Release()`

## Player
- 역할: 플레이어 위치, 이동 속도, Life 관리
- 주요 데이터: `m_x`, `m_y`, `m_speed`, `m_life`
- 주요 함수: `Init()`, `Update()`, `Damage()`

## Target
- 역할: 획득 대상의 위치와 다음 위치 관리
- 주요 데이터: `m_x`, `m_y`, `m_index`
- 주요 함수: `Init()`, `MoveNext()`

## Obstacle
- 역할: 장애물 이동과 재배치 관리
- 주요 데이터: `m_x`, `m_y`, `m_speed`, `m_index`
- 주요 함수: `Init()`, `Update()`, `Reset()`

## SoundManager
- 역할: 플레이 BGM과 시작/획득/충돌/성공/실패 효과음 재생
- 주요 데이터: `m_bgmOpened`
- 주요 함수: `PlayBgm()`, `Update()`, `StopBgm()`, `PlayStart()`, `PlayCollect()`, `PlayHit()`, `PlayClear()`, `PlayFail()`

## 게임 상태 흐름
`Start -> Play -> Result -> Play`

`Game` 객체가 모든 게임 객체를 멤버로 보유하고 상태에 따라 Update/Render를 제어한다.
