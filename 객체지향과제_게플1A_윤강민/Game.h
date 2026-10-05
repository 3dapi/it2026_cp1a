#pragma once

#include "Bot.h"
#include "Cards.h"
#include "Evaluator.h"

#include <chrono>
#include <deque>
#include <string>
#include <vector>

struct GameConfig {
    bool headless = false;
    int maxHands = 100000;
};

struct Player {
    int id = 0;
    std::string name;
    bool isUser = false;
    Style style = Style::TightAggressive;
    int stack = 0;
    Card hole[2];
    bool dealt = false;
    bool folded = true;
    bool allIn = false;
    int contrib = 0;
    int streetContrib = 0;
    bool acted = false;
    bool cardsOut = false;
    int faceState = 0;
    bool winner = false;
    std::string handName;
    int bustHand = 0;
};

class Game {
public:
    explicit Game(GameConfig config = GameConfig());

    void run();

    const std::vector<Player>& players() const { return players_; }
    int handsPlayed() const { return handNo_; }

private:
    bool waitForNextHand();
    void showResult(bool won);

    void playHand();
    void updateLevel();
    void dealHoleCards();
    void advanceStreet();
    void dealBoard(int count);
    void bettingRound(int firstSeat);
    bool roundComplete() const;

    Action askUser(Player& player);
    Action askBot(Player& player);
    void applyAction(Player& player, Action action);
    void putChips(Player& player, int amount);

    void revealContenders();
    void flipCards(Player& player);
    void showdown();
    void awardUncontested();
    void distributePots(const std::vector<HandScore>& scores);
    void payOut(const std::vector<int>& payouts);
    void finishHand();

    int smallBlind() const;
    int bigBlind() const;
    int potTotal() const;
    int contenders() const;
    int canActCount() const;
    bool canAct(const Player& player) const;
    int aliveCount() const;
    int nextAlive(int from) const;
    int countCallers(const Player& player) const;

    void addLog(const std::string& text);
    void render();
    void pause(int milliseconds);

    GameConfig config_;
    std::vector<Player> players_;
    Deck deck_;
    std::vector<Card> board_;
    int hiddenBoard_ = 0;
    int dealerIdx_ = -1;
    int actingIdx_ = -1;
    int handNo_ = 0;
    int level_ = 0;
    Street street_ = Street::Preflop;
    int curBet_ = 0;
    int minRaise_ = 0;
    std::chrono::steady_clock::time_point levelEnd_;
    std::deque<std::string> log_;
};
