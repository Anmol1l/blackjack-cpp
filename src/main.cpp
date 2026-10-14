#include "Card.h"
#include "Deck.h"
#include <iostream>

namespace Settings {
    constexpr int bust{21};
    constexpr int stopDraw{17};
}

struct Player {
    int score{};
};

bool hasExtraInput() {
    return !std::cin.eof() && std::cin.peek() != '\n';
}

void ignoreExtraInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char getInput() {
    while (true) {
        char input {};
        std::cout << "(h) to hit, or (s) to stand: ";
        std::cin >> input;
        if (hasExtraInput()) {
            ignoreExtraInput();
            std::cout << "Enter a valid Input\n";
            continue;
        }
        if (input == 'h' || input == 's') {
            return input;
        }
    }
}

int dealerDraw(Deck &deck) {
    Card dealerCard = {deck.dealCard()};
    std::cout << "The dealer flips a " << dealerCard << ".  ";
    return dealerCard.value();
}

int playerDraw(Deck &deck) {
    Card playerCard = {deck.dealCard()};
    std::cout << "You were delt " << playerCard << ".  ";
    return playerCard.value();
}

bool playBlackJack() {
    Deck deck = {};
    deck.shuffle();

    Player dealer{deck.dealCard().value()};
    Player player{deck.dealCard().value() + deck.dealCard().value()};

    std::cout << "The dealer is showing: " << dealer.score << '\n';
    std::cout << "You have score: " << player.score << '\n';

    while (true) {
        const char input{getInput()};
        if (input == 'h') {
            player.score += playerDraw(deck);
            std::cout << "You now have: " << player.score << '\n';
        }

        if (player.score > Settings::bust) {
            std::cout << "You went bust \n";
            return false;
        }

        if (input == 's')
            break;
    }

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
