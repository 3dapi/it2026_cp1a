# Crash Out 리소스 목록

- 작성자: 박지환
- 개발 환경: C++, Visual Studio 2022, glc2d

게임에 사용하거나 적용을 위해 준비한 그래픽, 폰트 및 사운드의 출처와 사용 조건을 정리한 문서이다. 사용 목적은 적용 예정인 기능을 포함한다.

## 1. 이미지

이미지 파일 위치: `Resource/Texture/`

| 리소스 이름 | 파일명 | 사용 목적 | 출처 | 라이선스 또는 사용 조건 |
| --- | --- | --- | --- | --- |
| 해변 트랙 배경 | `background.png` | 시작·플레이·결과 화면의 공통 배경과 2차선 트랙 표시 | AI 이미지 생성 기능으로 제작·편집 | AI 생성 이미지. OpenAI 이용약관 적용. 아래 AI 생성 이미지 항목 참고 |
| 게임 타이틀 | `Title.png` | 시작 화면에 게임 제목 Crash Out 표시 | AI 이미지 생성 기능으로 제작 | AI 생성 이미지. OpenAI 이용약관 적용. 아래 AI 생성 이미지 항목 참고 |
| 플레이어 자동차 | `sport_yellow.png` | 플레이어 차량을 노란색으로 표시 | marcusvh — [2D Top Down Pixel Art Car Pack](https://marcusvh.itch.io/2d-cars) | 제작자 안내에 따라 상업·비상업 프로젝트에서 무료 사용 가능. 제작자 크레딧 표기 요청에 따라 이름과 출처를 기재 |
| 상대 자동차 | `sport_red.png` | 상대 차량을 빨간색으로 표시 | marcusvh — [2D Top Down Pixel Art Car Pack](https://marcusvh.itch.io/2d-cars) | 제작자 안내에 따라 상업·비상업 프로젝트에서 무료 사용 가능. 제작자 크레딧 표기 요청에 따라 이름과 출처를 기재 |
| 충돌 이펙트 | `crash_effect.png` | 차량 충돌 위치에 불꽃 효과 표시용으로 준비 | AI 이미지 생성 기능으로 제작 | AI 생성 이미지. OpenAI 이용약관 적용. 아래 AI 생성 이미지 항목 참고 |


## 2. 사운드

사운드 파일 위치: `Resource/Sound/`

| 리소스 이름 | 파일명 | 사용 목적 | 출처 | 라이선스 또는 사용 조건 |
| --- | --- | --- | --- | --- |
| 차선 변경 효과음 | `lane_change.mp3` | 플레이어 차선 변경 알림 | 53439420 / Pixabay — [Retro Jump Sound 04](https://pixabay.com/sound-effects/retro-jump-sound-04-474783/) | Pixabay Content License. 무료 사용·수정 가능, 출처 표기 의무 없음. 원본 콘텐츠의 단독 판매·배포 금지 등 약관 준수 |
| 충돌 효과음 | `car_crash.mp3` | 충돌 및 게임오버 알림 | DRAGON-STUDIO / Pixabay — [Car Crash Sound](https://pixabay.com/sound-effects/film-special-effects-car-crash-sound-376882/) | Pixabay Content License. 무료 사용·수정 가능, 출처 표기 의무 없음. 원본 콘텐츠의 단독 판매·배포 금지 등 약관 준수 |
| 점수 획득 효과음 | `score.mp3` | 한 바퀴 완주에 따른 점수 획득 알림 | floraphonic / Pixabay — [Arcade UI 6](https://pixabay.com/sound-effects/film-special-effects-arcade-ui-6-229503/) | Pixabay Content License. 무료 사용·수정 가능, 출처 표기 의무 없음. 원본 콘텐츠의 단독 판매·배포 금지 등 약관 준수 |
| 게임 시작 효과음 | `game_start.mp3`  | 새 게임 시작 알림 | freesound_community / Pixabay — [Short Beep Tone](https://pixabay.com/sound-effects/film-special-effects-short-beep-tone-47916/) | Pixabay Content License. 무료 사용·수정 가능, 출처 표기 의무 없음. 원본 콘텐츠의 단독 판매·배포 금지 등 약관 준수 |


## 3. 폰트

| 리소스 이름 | 파일명 | 사용 목적 | 출처 | 라이선스 또는 사용 조건 |
| --- | --- | --- | --- | --- |
| Neo둥근모 | `neodgm.ttf`  | 시작 안내 등 게임 내 텍스트 출력 | Dalgona / neodgm 프로젝트 — [공식 사이트](https://neodgm.dalgona.dev/), [공식 저장소](https://github.com/neodgm/neodgm) | SIL Open Font License 1.1. 사용 및 소프트웨어와 함께 배포 가능. 폰트 파일 배포 시 저작권 고지와 라이선스 원문 포함. 폰트 자체의 단독 판매 금지 |

## 4. 사용 조건 및 크레딧

### 자동차

자동차 그래픽 제작자: **marcusvh**  
사용 에셋: **2D Top Down Pixel Art Car Pack**  
출처: [제작자 에셋 페이지](https://marcusvh.itch.io/2d-cars)

제작자는 상업·비상업 프로젝트의 무료 사용을 허용하며 크레딧 표기를 요청하고 있다. 본 문서에 제작자와 원본 에셋 출처를 표시한다.

### 사운드

사운드는 Pixabay에서 제공하는 효과음을 사용한다. 출처 표기가 필수는 아니지만, 리소스 관리를 위해 제작자와 개별 다운로드 페이지를 기록하였다. 콘텐츠를 거의 원본 그대로 단독 판매·배포하는 행위는 허용되지 않는다. 위 표는 주요 조건의 요약이며 전체 약관이 우선한다.

- [Pixabay Content License 요약](https://pixabay.com/service/license-summary/)
- [Pixabay 전체 이용약관](https://pixabay.com/service/terms/)

### 폰트

Neo둥근모는 SIL Open Font License 1.1을 따른다. 폰트 파일을 프로젝트에 동봉할 경우, 제공된 저작권 고지 및 라이선스 원문도 함께 보관한다. 이 문서의 요약은 라이선스 원문을 대신하지 않는다.

- [Neo둥근모 라이선스 원문](https://github.com/neodgm/neodgm/blob/main/LICENSE.txt)

### AI 생성 이미지

배경, 타이틀 및 충돌 이펙트는 ChatGPT 이미지 생성 기능을 이용해 제작·편집하였다. OpenAI 이용약관에 따라 사용자와 OpenAI 사이에서는 법이 허용하는 범위에서 출력물의 권리가 사용자에게 귀속된다. 이는 CC0 등의 별도 공개 라이선스를 부여한다는 의미는 아니며, 제3자의 권리를 침해하지 않도록 사용해야 한다.

- [OpenAI 이용약관](https://openai.com/policies/row-terms-of-use/)
