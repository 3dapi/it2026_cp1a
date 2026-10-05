# 3주차 개발 기록

## 교수 피드백 반영
이전 코드에 대해 클래스로 작성하라는 피드백을 받아 게임 전체 흐름을 Game 클래스로 묶었다.
Player, Target, Obstacle도 각각 별도 클래스로 두고 Game 객체가 이 객체들을 멤버로 관리하도록 수정했다.

## 이번 주 구현
- Game.h / Game.cpp 추가
- GameState를 Game 클래스에서 관리
- Player, Target, Obstacle 생성자와 초기화 코드 정리
- 그래픽 리소스를 resource/image에 정리
- 시작 화면 title / prompt를 실제 게임에 출력
- Enter 입력으로 Start -> Play 전환
- 결과 화면용 Clear / Fail 그래픽 준비
- 사운드 리소스 파일 준비

## 다음 주 계획
- 게임 화면에 점수 / Life / 남은 시간 값 표시
- 준비한 효과음과 배경음을 게임 상황에 맞게 적용
- 시작부터 종료까지 전체 플레이 테스트 및 오류 수정
