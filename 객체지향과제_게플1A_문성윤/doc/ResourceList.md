# 리소스 목록

실제 게임에서 사용하는 이미지·사운드·폰트의 파일, 규격, 용도와 출처를 정리한다. 아래 파일 경로는 `26311027-MoonSeongyoon-VN` 기준이다. 화면 배치는 [화면구성.md](화면구성.md)에 정리한다.

## 이미지

원본 해상도를 유지하고 코드에서 1920×1440 기준 좌표에 맞춰 비율을 유지해 축소/확대한다.
출처와 사용 조건은 2026-09-13에 각 제작자·제공 사이트의 안내 페이지를 확인해 기록했다.

| 리소스 | 파일 | 원본 규격 | 출처 및 사용 조건 | 게임 내 사용 |
| --- | --- | --- | --- | --- |
| 폐교 복도 | resource/background/bg_corridor.png | 1448×1086 RGB | 문성윤이 AI를 활용해 자체 제작. 프로젝트·과제 사용 제한 없음 | 시작·프롤로그·복도 조사·결과 화면 |
| 폐교 교실 | resource/background/bg_classroom.png | 1448×1086 RGB | 문성윤이 AI를 활용해 자체 제작. 프로젝트·과제 사용 제한 없음 | 교실 조사·전투·승리 후 대화·결말 대사 |
| 서연 | resource/character/ghost_seoyeon.png | 1400×2160 RGBA | 문성윤이 AI를 활용해 자체 제작. 프로젝트·과제 사용 제한 없음 | 프롤로그 P-D07부터 대화·전투·후속·결말에 표시. 결과 전환 때 숨김 |
| 그림자 | resource/character/ghost_shadow.png | 1400×2160 RGBA | 문성윤이 AI를 활용해 자체 제작. 프로젝트·과제 사용 제한 없음 | 복도 위협·교실 대치·전투·승리 퇴장 대사. 마지막 승리 안내에서 숨김 |
| UI 사각형 | resource/ui/white.png | 2×2 RGBA | 이번 구현에서 코드로 생성한 단색 픽셀. 별도 외부 에셋 없음 | 색상·알파·크기를 지정해 대화창·버튼·상태창 출력 |

주인공은 1인칭 시점의 이름·대사로 표현하므로 별도 초상화가 없다. 아이템·HP·점수는 계획대로 텍스트와 도형으로 표현한다. 고정 이미지 방식이므로 애니메이션 프레임은 필요하지 않다.

## 사운드 출처·사용 조건 (2026-09-13 확인)

아래 원본 파일은 빌드할 때 실행 폴더의 영문 별칭으로 복사한다. 게임에 결합된 형태로 사용하며 음원 파일만 별도 상품·소재로 재배포하지 않는다.

| 원본 파일 (resource/sound/) | 실행 파일명 | 제작자·출처 | 사용 조건 및 게임 내 사용 |
| --- | --- | --- | --- |
| `Sayuri Loop1_01.mp3` | `bgm_story.mp3` | Crow Shade, [Loops - Lonely Nightmare](https://crowshade.itch.io/melancholic-indie-horror-game-soundtrack-pack) | CC BY 4.0. 상업·비상업 사용과 편집이 가능하며 `Music by Crow Shade` 크레딧을 유지한다. 시작·대화·승패 이후·결말·결과 화면에서 반복 재생한다. |
| `Iwan Gabovitch - Dark Ambience Loop.mp3` | `bgm_battle.mp3` | Iwan Gabovitch, [OpenGameArt - Dark Ambience Loop](https://opengameart.org/content/dark-ambience-loop) | CC BY 3.0. `Dark Ambience Loop by Iwan Gabovitch qubodup.net` 또는 원본 링크를 크레딧에 남긴다. 마지막 전투의 시작·진행 중 재생하며 승패 확정 후 이야기 BGM으로 전환한다. |
| `qubodupPunch01.mp3` | `se_attack.mp3` | Iwan Gabovitch(qubodup), [OpenGameArt - Punch](https://opengameart.org/content/punch) | CC0. 별도 표시 의무는 없지만 제작자·원본 링크를 함께 기록한다. 공격·단서 활용·적 피해가 실제 적용될 때 재생한다. |
| `Replenish.mp3` | `se_heal.mp3` | Iwan Gabovitch(qubodup), [OpenGameArt - Replenish Life Force Sound](https://opengameart.org/content/replenish-life-force-sound) | CC BY 3.0. `Replenish Life Force Copyright 2013 Iwan Gabovitch http://freesound.org/people/qubodup/ , CC-BY3 license.` 문구를 크레딧에 남긴다. 회복 아이템 사용 효과음으로 재생한다. |
| `click4.mp3` | `se_select.mp3` | Kenney, [Kenney UI Audio](https://kenney.nl/assets/ui-audio) | CC0. 별도 표시 의무는 없지만 제작자·원본 링크를 함께 기록한다. 시작·대사 진행·선택·패널·결과 버튼에서 재생한다. |

glc2d 0.1.0.7의 MP3 지원을 사용하므로 WAV 변환은 하지 않는다. 효과음은 이전 재생을 멈춘 뒤 다시 재생해 연속 입력에 대응하고, 배경음은 타이틀과 대화 사이에서 끊지 않는다.

## 폰트

- 파일: `resource/font/에이투지체-6SemiBold.ttf`
- 내부 글꼴 이름: `A2Z 6 SemiBold`
- 출처: [에이투지체 소개·다운로드](https://freesentation.blog/a2z)
- 라이선스: SIL Open Font License(OFL) 1.1. 게임·앱에 번들하거나 상업·비상업 콘텐츠에 사용하는 것은 허용되며, 글꼴을 사용한 결과물에 별도 출처 표기는 필수가 아니다.
- 배포 조건: TTF 자체를 별도로 배포할 때는 원저작권·OFL 정보를 함께 제공하고, 글꼴 파일 자체만 판매하지 않는다. 수정본을 배포할 경우 OFL을 유지하고 Reserved Font Name을 침해하지 않는다. 현재 파일은 수정하지 않은 원본을 게임에 포함한다.
- 제목, 버튼, 화자, 대사, 상태 표시 전체에 적용.
- 실행 중 `FR_PRIVATE`로만 등록하며 게임 종료 때 해제. Windows에 영구 설치하지 않는다.
- 저장소에는 이 문서의 출처·조건 기록을 함께 포함하며, 별도 폰트 파일 배포가 필요할 때는 OFL 원문과 저작권 정보를 동봉한다.
