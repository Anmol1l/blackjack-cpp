#include "Card.h"
#include "Deck.h"
#include <iostream>

struct Player {
    int score {};
};

bool playBlackJack() {
    Deck deck = {};
    deck.shuffle();

    const Player dealer {deck.dealCard().value()};
    const Player player {deck.dealCard().value() + deck.dealCard().value()};

    std::cout << "The dealer is showing: " << dealer.score << '\n';
    std::cout << "You have score: " << player.score << '\n';

    if (player.score > dealer.score)
        return true;

    return false;
}

int main()
{
    Deck deck{};
    std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';

    deck.shuffle();
    std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';
    Player p {};

    if (playBlackJack())
        std::cout << "You win!\n";
    else
        std::cout << "You lose!\n";

    return 0;
}
