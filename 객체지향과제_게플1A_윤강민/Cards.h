#pragma once

#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

enum class Suit { Spade, Heart, Diamond, Club };

enum class Street { Preflop, Flop, Turn, River };

struct Card {
    int rank = 2;
    Suit suit = Suit::Spade;
};

inline bool isRed(Suit suit) {
    return suit == Suit::Heart || suit == Suit::Diamond;
}

//¾ÕÀÚ¸®
inline char suitLetter(Suit suit) {
    switch (suit) {
    case Suit::Spade: return 'S';
    case Suit::Heart: return 'H';
    case Suit::Diamond: return 'D';
    default: return 'C';
    }
}

inline std::string rankName(int rank) {
    switch (rank) {
    case 11: return "J";
    case 12: return "Q";
    case 13: return "K";
    case 14: return "A";
    default: return std::to_string(rank);
    }
}

inline std::string cardText(const Card& card) {
    return rankName(card.rank) + suitLetter(card.suit);
}

inline std::mt19937& rng() {
    static std::mt19937 generator([] {
        std::random_device device;
        std::seed_seq seed{
            device(), device(),
            static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count())};
        return std::mt19937(seed);
    }());
    return generator;
}

inline double rand01() {
    return std::uniform_real_distribution<double>(0.0, 1.0)(rng());
}

class Deck {
public:
    Deck() { reset(); }

    void reset() {
        cards_.clear();
        for (int rank = 2; rank <= 14; ++rank) {
            for (int suit = 0; suit < 4; ++suit) {
                cards_.push_back({rank, static_cast<Suit>(suit)});
            }
        }
        std::shuffle(cards_.begin(), cards_.end(), rng());
    }

    Card draw() {
        Card card = cards_.back();
        cards_.pop_back();
        return card;
    }

private:
    std::vector<Card> cards_;
};
