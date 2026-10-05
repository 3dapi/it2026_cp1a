#pragma once

#include <array>
#include <vector>
#include <string>

using namespace std;
// 카드 문양
enum class CardSuit
{
    Spade = 101,
    Heart = 102,
    Diamond = 103,
    Club = 104
};

// 카드 숫자
enum class CardNumber
{
    Ace = 1,
    Two =2,
    Three=3,
    Four=4,
    Five=5,
    Six=6,
    Seven=7,
    Eight=8,
    Nine=9,
    Ten=10,
    Jack=11,
    Queen=12,
    King=13
};

// 카드 한 장의 정보
struct Card
{
    int key;           // 1~52
    std::string suit;  // Spade, Heart, Diamond, Club
	int number; // 1~13 1은 Ace, 11은 Jack, 12는 Queen, 13은 King
	int value; // 1~11, Ace는 1 또는 11, Face 카드(J, Q, K)는 10  
};

// 현재 게임 진행 상태
enum class GameState
{
    Ready,
    Betting,
    PlayerTurn,
    DealerTurn,
    GameOver
};

// 게임 결과
enum class GameResult
{
    None,
    PlayerWin,
    DealerWin,
    Draw
};

class GameManager
{
public:
    // 최초 초기화
    void Init(int startingCash = 1000);

    // 새로운 게임 시작
    void StartGame();

    // 게임을 처음부터 다시 시작
    void RestartGame();

    // 플레이어 행동
    bool PlayerBet(int amount);
    bool PlayerHit();
    bool PlayerStand();

    // 현재 정보 가져오기
    int GetPlayerCash() const;
    int GetCurrentBet() const;

    int GetPlayerScore() const;
    int GetDealerScore() const;

    GameState GetGameState() const;
    GameResult GetGameResult() const;

    const vector<Card>& GetPlayerHand() const;
    const vector<Card>& GetDealerHand() const;

    // 딜러의 두 번째 카드를 가려야 하는지 확인
    bool IsDealerCardHidden() const;

private:
    // 덱 관리
    void CreateDeck();
    void ShuffleDeck();
    Card DrawCard();

    // 카드 지급
    void DealStartingCards();
    void DealerDrawCard();
    void DealerPlay();

    // 점수와 승패 처리
    int CalculateScore(
        const vector<Card>& hand
    ) const;

    void CheckPlayerBust();
    void DecideGameResult();
    void ProcessBetResult();

private:
    // 52장 카드 덱
    array<Card, 52> deck{};

    // 플레이어와 딜러가 가지고 있는 카드
    vector<Card> playerHand;
    vector<Card> dealerHand;
    // 다음에 뽑을 카드 위치
    size_t nextCardIndex = 0;

    // 돈과 배팅
    int playerCash = 1000;
    int currentBet = 0;

    // 게임 상태
    GameState gameState = GameState::Ready;
    GameResult gameResult = GameResult::None;

    // 딜러의 숨겨진 카드 공개 여부
    bool dealerCardHidden = true;
};

int PlayerStartCash = 1000; // 플레이어의 시작 금액