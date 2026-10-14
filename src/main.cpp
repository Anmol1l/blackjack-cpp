#include "Card.h"
#include "Deck.h"
#include <iostream>

namespace Settings {
    constexpr int bust {21};
    constexpr int stopDraw {17};
}

struct Player {
    int score{};
};

int dealerDraw(Deck& deck) {
    Card dealerCard = {deck.dealCard()};
    std::cout << "The dealer flips a " << dealerCard << ".  ";
    return dealerCard.value();
}

bool playBlackJack() {
    Deck deck = {};
    deck.shuffle();

    Player dealer{deck.dealCard().value()};
    Player player{deck.dealCard().value() + deck.dealCard().value()};

    std::cout << "The dealer is showing: " << dealer.score << '\n';
    std::cout << "You have score: " << player.score << '\n';

    while (dealer.score < Settings::stopDraw) {
        dealer.score += dealerDraw(deck);
        std::cout << "They now have: " << dealer.score << '\n';
    }

    if (dealer.score > Settings::bust) {
        std::cout << "The dealer went bust!\n";
        return true;
    }

    if (player.score > dealer.score)
        return true;

    return false;
}

int main() {
    if (playBlackJack())
        std::cout << "You win!\n";
    else
        std::cout << "You lose!\n";

    return 0;
}
