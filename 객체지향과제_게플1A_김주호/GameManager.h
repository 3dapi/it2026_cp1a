#pragma once

#include <array>
#include <vector>

enum class CardSuit
{
    Spade = 101,
    Heart = 102,
    Diamond = 103,
    Club = 104
};

enum class CardNumber
{
    Ace = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

struct Card
{
    CardNumber number = CardNumber::Ace;
    CardSuit suit = CardSuit::Spade;

    int GetKey() const
    {
        return (static_cast<int>(suit) - 101) * 13
             + static_cast<int>(number) - 1;
    }
};

enum class Turn
{
    Player,
    Dealer
};

enum class GameState
{
    Ready,
    Playing,
    GameOver
};

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
    void Init(int startingCash = 1000);
    void GameStart();

    bool PlayerBet(int amount);
    bool PlayerHit();
    bool PlayerStand();

    int GetPlayerCash() const;
    int GetCurrentBet() const;
    int GetPlayerScore() const;
    int GetDealerScore() const;

    Turn GetCurrentTurn() const;
    GameState GetGameState() const;
    GameResult GetGameResult() const;

    const std::vector<Card>& GetPlayerHand() const;
    const std::vector<Card>& GetDealerHand() const;

private:
    void CreateDeck();
    void ShuffleDeck();
    Card DrawCard();

    void DealerPlay();
    void FinishGame();
    int CalculateScore(const std::vector<Card>& hand) const;

private:
    std::array<Card, 52> deck{};
    std::vector<Card> playerHand;
    std::vector<Card> dealerHand;

    int nextCardIndex = 0;

    int playerCash = 1000;
    int currentBet = 0;

    Turn currentTurn = Turn::Player;
    GameState gameState = GameState::Ready;
    GameResult gameResult = GameResult::None;
};
