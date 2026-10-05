# 26311046_JeongJunsu_GameProject

- 학번: 26311046
- 이름: 정준수
- 과목명: 객체지향프로그래밍Ⅰ
- 제출 제목: 게프1A 26311046 정준수 게임제작과제
- 게임 제목: Target Catch
- 개발 환경: Visual Studio C++ / glc2d

## 게임 설명
45초 안에 좌우로 움직이며 Target 10개를 모으는 간단한 2D 수집/회피 게임입니다.
떨어지는 장애물에 닿으면 Life가 1 감소하고, Life가 0이 되거나 시간이 끝나면 실패합니다.

## 조작
- Enter: 게임 시작 / 결과 화면에서 재시작
- A / D 또는 ← / →: 좌우 이동

## 최종 구현
- Game / Player / Target / Obstacle / SoundManager 클래스 구성
- 시작 → 플레이 → 성공/실패 → 재시작 흐름
- Target 획득 +10점, 목표 점수 100점
- Life 3, 제한 시간 45초
- 충돌 판정 및 결과 처리
- 배경, 플레이어, Target, 장애물, HUD, 결과 패널 그래픽 적용
- Target/장애물 2프레임 간단 애니메이션
- BGM 및 시작/획득/피격/성공/실패 효과음 적용

## 실행 전 확인
1. NuGet 패키지 복원
2. Visual Studio에서 솔루션 빌드
3. 실행 위치 기준 `resource/image`, `resource/sound` 폴더가 존재하는지 확인
4. Enter 시작 → 이동 → Target 획득 → 장애물 피격 → CLEAR/FAIL → 재시작까지 확인

## 문서
- 최종 기획서: `docs/GameDesign.pdf`
- 클래스 구성: `docs/ClassDesign.md`
- 리소스 목록/출처: `docs/ResourceList.md`

## 최종 Git Tag
`final`
