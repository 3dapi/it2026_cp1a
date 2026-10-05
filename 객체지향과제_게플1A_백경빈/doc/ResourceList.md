# 게임 리소스 목록

출처는 사용자가 2026-09-14에 밝힌 내용을 기록했다. 아래의 "사용 조건 미확인"은 출처 정보와 별개로, 제출·배포에 적용할 조건을 아직 확인하지 않았다는 뜻이다.

| 리소스 이름 | 파일명 | 사용 목적 | 출처 | 라이선스 또는 사용 조건 |
| --- | --- | --- | --- | --- |
| 타이틀 표지 | `Title.png` | 시작 화면 | ChatGPT 생성 이미지(사용자 제공) | 사용 조건 미확인 |
| 숲 배경 | `Forest.png` | 첫 일반 전투 | ChatGPT 생성 이미지(사용자 제공) | 사용 조건 미확인 |
| 폐허 배경 | `Ruins.png` | 폐허 일반 전투 | ChatGPT 생성 이미지(사용자 제공) | 사용 조건 미확인 |
| 동굴 배경 | `Cave.png` | 동굴 일반 전투 | ChatGPT 생성 이미지(사용자 제공) | 사용 조건 미확인 |
| 성채 내부 배경 | `Citadel.png` | 보스전 | ChatGPT 생성 이미지(사용자 제공) | 사용 조건 미확인 |
| 플레이어 | `Player.png` | 전투 화면 플레이어 | Codex ImageGen, 2026-09-14 | 사용 조건 미확인 |
| 숲의 야수 | `ForestEnemy.png` | 숲 일반 적 | Codex ImageGen, 2026-09-14 | 사용 조건 미확인 |
| 폐허의 수호자 | `RuinsEnemy.png` | 폐허 일반 적 | Codex ImageGen, 2026-09-14 | 사용 조건 미확인 |
| 동굴의 박쥐 | `CaveEnemy.png` | 동굴 일반 적 | Codex ImageGen, 2026-09-14 | 사용 조건 미확인 |
| 성채 보스 | `Boss.png` | 최종 보스 | Codex ImageGen, 2026-09-14 | 사용 조건 미확인 |
| 회복약 | `Potion.png` | HP 30 회복 도구 | Codex ImageGen, 2026-09-14 | 사용 조건 미확인 |
| 고급 회복약 | `SuperPotion.png` | HP 60 회복 도구 | Codex ImageGen, 2026-09-14 | 사용 조건 미확인 |
| 보상 아이콘 시트 | `RewardIcons.png` | 공격·체력·도구 보상 선택 화면 | Codex ImageGen, 2026-09-21 | OpenAI 서비스 이용 조건에 따름 |
| 타이틀 음악: New Future | `Main bgm.mp3` | 시작 화면 음악 | [Ian Aisling - New Future](https://uppbeat.io/music/tracks/ian-aisling/new-future), Uppbeat (사용자 제공) | 다운로드 당시 적용된 사용 조건·크레딧 문구 미확인 |

지역 선택은 별도 지도 대신 실제 폐허·동굴 배경 미리보기로 구현했다. 배경 음악은 타이틀용과 전투용으로 전환하여 반복 재생하며 선택·결과 효과음은 Windows 시스템 효과음을 사용한다. 타이틀 음악을 내려받을 때 받은 크레딧 문구나 라이선스 기록이 확인되면 사용 조건을 추가한다.

## UI 보완 및 선택 음악

- `Pixel.png`: 직접 구성한 흰색 1픽셀 이미지. HP 막대와 안내·보상 패널에 사용하며 외부 원본은 없다.
- `Battle bgm.mp3`: **Battle Theme A**, 작곡가 **cynicmusic**. START 이후 게임 방법·전투·결과 화면에서 반복 재생하며 타이틀 복귀 시 타이틀 음악으로 전환한다.
- 출처: https://opengameart.org/content/battle-theme-a
- 원본 파일: https://opengameart.org/sites/default/files/battleThemeA.mp3
- 사용 조건: 원본 게시물에 표시된 [CC0 1.0 Universal](https://creativecommons.org/publicdomain/zero/1.0/). 복제·수정·배포·상업적 이용 가능. 별도 허락이나 의무적인 저작자 표시가 필요하지 않지만 과제의 출처 기록을 위해 저작자를 기재한다.
- 크레딧: Battle Theme A — cynicmusic (cynicmusic.com, pixelsphere.org).
- 확인 및 다운로드: 2026-10-04. 원본 음원을 편집하지 않고 파일명만 Battle bgm.mp3로 변경했다.
- SHA-256: 6042399782e581d753d616bc703e66483d5eccb5fb687a20c9a552d68c49e620
