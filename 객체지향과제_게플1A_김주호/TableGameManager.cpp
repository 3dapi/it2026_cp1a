#include "TableGameManager.h"

#include <algorithm>
#include <random>

// 전역 게임 매니저의 실제 정의
GameManager g_gameManager;

void GameManager::Init(int startingCash)
{
    playerCash = startingCash;      
    StartGame();
}

void GameManager::StartGame()
{
    //딜러 카드랑 플레이어 카드를 초기화
    playerHand.clear();
    dealerHand.clear();

    currentBet = 0;
    nextCardIndex = 0;

    //기본값 세팅
    gameState = GameState::Betting;
    gameResult = GameResult::None;
    //딜러 두번쨰 카드를 하나 숨겨
    dealerCardHidden = true;

	//덱 생성 및 섞기
    CreateDeck();
    ShuffleDeck();
}

void GameManager::RestartGame()
{
    // 현재 보유 금액은 유지하고 새 판만 준비
    StartGame();
}

bool GameManager::PlayerBet(int amount)
{
    if (gameState != GameState::Betting)
    {
        return false;
    }

    if (amount <= 0 || amount > playerCash)
    {
        return false;
    }

    currentBet = amount;
    playerCash -= amount;


	// 처음 두 장씩 지급
    DealStartingCards();

    gameState = GameState::PlayerTurn;

    // 처음 두 장으로 블랙잭이 나온 경우
    if (GetPlayerScore() == 21 ||
        GetDealerScore() == 21)
	{   // 블랙잭이 나온 경우 딜러의 두 번째 카드를 공개하고 승패 결정
        dealerCardHidden = false;
        DecideGameResult();
    }

    return true;
}

bool GameManager::PlayerHit()
{
    if (gameState != GameState::PlayerTurn)
    {
        return false;
    }

    playerHand.push_back(DrawCard());

    CheckPlayerBust();

    return true;
}

bool GameManager::PlayerStand()
{
    if (gameState != GameState::PlayerTurn)
    {
        return false;
    }

    gameState = GameState::DealerTurn;
    dealerCardHidden = false;

    DealerPlay();
    DecideGameResult();

    return true;
}

void GameManager::CreateDeck()
{
    const string suits[4] =
    {
        "Spade",
        "Heart",
        "Diamond",
        "Club"
    };

    int index = 0;
    int key = 1;

    for (int suitIndex = 0;
        suitIndex < 4;
        ++suitIndex)
    {
        for (int number = 1;
            number <= 13;
            ++number)
        {
            int value = number;

            if (number == 1)
            {
                value = 11;
            }
            else if (number >= 10)
            {
                value = 10;
            }

            deck[index].key = key;
            deck[index].suit = suits[suitIndex];
            deck[index].number = number;
            deck[index].value = value;

            ++index;
            ++key;
        }
    }

    nextCardIndex = 0;
}

void GameManager::ShuffleDeck()
{
    random_device randomDevice;
    mt19937 randomEngine(randomDevice());

    shuffle(
        deck.begin(),
        deck.end(),
        randomEngine
    );

    nextCardIndex = 0;
}

Card GameManager::DrawCard()
{
    if (nextCardIndex >= deck.size())
    {
        CreateDeck();
        ShuffleDeck();
    }

    return deck[nextCardIndex++];
}

void GameManager::DealStartingCards()
{
    playerHand.push_back(DrawCard());
    dealerHand.push_back(DrawCard());

    playerHand.push_back(DrawCard());
    dealerHand.push_back(DrawCard());
}

void GameManager::DealerDrawCard()
{
    dealerHand.push_back(DrawCard());
}

void GameManager::DealerPlay()
{
    while (GetDealerScore() < 17)
    {
        DealerDrawCard();
    }
}

int GameManager::CalculateScore(
    const vector<Card>& hand
) const
{
    int score = 0;
    int aceCount = 0;

    for (const Card& card : hand)
    {
        score += card.value;

        if (card.number == 1)
        {
            ++aceCount;
        }
    }

    // 21점 초과 시 A를 11점에서 1점으로 변경
    while (score > 21 && aceCount > 0)
    {
        score -= 10;
        --aceCount;
    }

    return score;
}

void GameManager::CheckPlayerBust()
{
    if (GetPlayerScore() <= 21)
    {
        return;
    }

    gameResult = GameResult::DealerWin;
    gameState = GameState::GameOver;
    dealerCardHidden = false;

    ProcessBetResult();
}

void GameManager::DecideGameResult()
{
    const int playerScore = GetPlayerScore();
    const int dealerScore = GetDealerScore();

    if (playerScore > 21)
    {
        gameResult = GameResult::DealerWin;
    }
    else if (dealerScore > 21)
    {
        gameResult = GameResult::PlayerWin;
    }
    else if (playerScore > dealerScore)
    {
        gameResult = GameResult::PlayerWin;
    }
    else if (playerScore < dealerScore)
    {
        gameResult = GameResult::DealerWin;
    }
    else
    {
        gameResult = GameResult::Draw;
    }

    gameState = GameState::GameOver;
    dealerCardHidden = false;

    ProcessBetResult();
}

void GameManager::ProcessBetResult()
{
    const int finishedBet = currentBet;

    // 같은 판의 정산이 두 번 실행되는 것 방지
    currentBet = 0;

    if (gameResult == GameResult::PlayerWin)
    {
        playerCash += finishedBet * 2;
    }
    else if (gameResult == GameResult::Draw)
    {
        playerCash += finishedBet;
    }
}

int GameManager::GetPlayerCash() const
{
    return playerCash;
}

int GameManager::GetCurrentBet() const
{
    return currentBet;
}

int GameManager::GetPlayerScore() const
{
    return CalculateScore(playerHand);
}

int GameManager::GetDealerScore() const
{
    return CalculateScore(dealerHand);
}

GameState GameManager::GetGameState() const
{
    return gameState;
}

GameResult GameManager::GetGameResult() const
{
    return gameResult;
}

const vector<Card>&
GameManager::GetPlayerHand() const
{
    return playerHand;
}

const vector<Card>&
GameManager::GetDealerHand() const
{
    return dealerHand;
}

bool GameManager::IsDealerCardHidden() const
{
    return dealerCardHidden;
}