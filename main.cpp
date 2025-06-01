#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <string>

class Card {
public:
    enum Suit { Clubs, Diamonds, Hearts, Spades };
    enum Rank {
        Two = 2, Three, Four, Five, Six,
        Seven, Eight, Nine, Ten,
        Jack, Queen, King, Ace
    };

    Card(Suit s, Rank r) : suit(s), rank(r) {}

    std::string toString() const {
        return rankToString() + " of " + suitToString();
    }

    int value() const {
        return static_cast<int>(rank);
    }

private:
    Suit suit;
    Rank rank;

    std::string suitToString() const {
        switch (suit) {
            case Clubs:    return "Clubs";
            case Diamonds: return "Diamonds";
            case Hearts:   return "Hearts";
            case Spades:   return "Spades";
        }
        return "";
    }

    std::string rankToString() const {
        switch (rank) {
            case Two:   return "Two";
            case Three: return "Three";
            case Four:  return "Four";
            case Five:  return "Five";
            case Six:   return "Six";
            case Seven: return "Seven";
            case Eight: return "Eight";
            case Nine:  return "Nine";
            case Ten:   return "Ten";
            case Jack:  return "Jack";
            case Queen: return "Queen";
            case King:  return "King";
            case Ace:   return "Ace";
        }
        return "";
    }
};

class Deck {
public:
    Deck() {
        for (int s = Card::Clubs; s <= Card::Spades; ++s) {
            for (int r = Card::Two; r <= Card::Ace; ++r) {
                cards.emplace_back(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r));
            }
        }
    }

    void shuffle() {
        std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        std::shuffle(cards.begin(), cards.end(), rng);
    }

    Card draw() {
        if (cards.empty()) {
            throw std::out_of_range("Deck is empty");
        }
        Card top = cards.back();
        cards.pop_back();
        return top;
    }

    size_t size() const {
        return cards.size();
    }

private:
    std::vector<Card> cards;
};

class Game {
public:
    void playRounds(int rounds) {
        deck.shuffle();
        for (int i = 1; i <= rounds; ++i) {
            if (deck.size() < 2) {
                std::cout << "Not enough cards to continue playing.\n";
                break;
            }
            Card card1 = deck.draw();
            Card card2 = deck.draw();
            std::cout << "Round " << i << ":\n";
            std::cout << "  Player 1 draws " << card1.toString() << "\n";
            std::cout << "  Player 2 draws " << card2.toString() << "\n";
            int winner = compareCards(card1, card2);
            if (winner == 0)
                std::cout << "  Result: It's a tie!\n\n";
            else
                std::cout << "  Result: Player " << winner << " wins the round!\n\n";
        }
    }

private:
    Deck deck;

    int compareCards(const Card& c1, const Card& c2) {
        if (c1.value() > c2.value()) return 1;
        if (c1.value() < c2.value()) return 2;
        return 0;
    }
};

int main() {
    std::cout << "Simple Card Game Simulation\n";
    Game game;
    game.playRounds(5); // play 5 rounds
    return 0;
}

