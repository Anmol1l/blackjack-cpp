#include "Card.h"
#include "Deck.h"
#include <iostream>

namespace Settings {
    constexpr int bust{21};
    constexpr int stopDraw{17};
}

struct Player {
    int score{};
    int aceCount{};
};

bool hasExtraInput() {
    return !std::cin.eof() && std::cin.peek() != '\n';
}

void ignoreExtraInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char getInput() {
    while (true) {
        char input{};
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

void checkForAce(Player &p, const Card &c) {
    if (c.rank == Card::rank_ace)
        ++p.aceCount;
}

int dealerDraw(Player &dealer, Deck &deck) {
    const Card dealerCard = {deck.dealCard()};
    std::cout << "The dealer flips a " << dealerCard << ".  ";
    checkForAce(dealer, dealerCard);
    return dealerCard.value();
}

int playerDraw(Player &player, Deck &deck) {
    const Card playerCard = {deck.dealCard()};
    std::cout << "You were delt " << playerCard << ".  ";
    checkForAce(player, playerCard);
    return playerCard.value();
}

bool playBlackJack() {
    Deck deck = {};
    deck.shuffle();

    Card dealerCard{deck.dealCard()};
    Player dealer{.score = dealerCard.value()};
    Card playerCard1{deck.dealCard()};
    Card playerCard2{deck.dealCard()};
    Player player{.score = playerCard1.value() + playerCard2.value()};

    checkForAce(dealer, dealerCard);
    checkForAce(player, playerCard1);
    checkForAce(player, playerCard2);

    std::cout << "The dealer is showing: " << dealerCard << " (" << dealer.score << ")\n";
    std::cout << "You are showing: " << playerCard1 << ' ' << playerCard2 << " (" << player.score << ")\n";

    while (true) {
        const char input{getInput()};
        if (input == 'h') {
            player.score += playerDraw(player, deck);
            // std::cout << "You now have: " << player.score << '\n';
        }

        if (player.score > Settings::bust) {
            while (player.aceCount > 0 && player.score > Settings::bust) {
                player.score -= 10;
                --player.aceCount;
            }
            if (player.score > Settings::bust) {
                std::cout << "You now have: " << player.score << '\n';
                std::cout << "You went bust!\n";
                return false;
            }
        }

        if (input == 's')
            break;

        std::cout << "You now have: " << player.score << '\n';
    }

    while (dealer.score < Settings::stopDraw) {
        dealer.score += dealerDraw(dealer, deck);

        if (dealer.score > Settings::bust) {
            while (dealer.aceCount > 0 && dealer.score > Settings::bust) {
                dealer.score -= 10;
                --dealer.aceCount;
            }

            if (dealer.score > Settings::bust) {
                std::cout << "They now have: " << dealer.score << '\n';
                std::cout << "The dealer went bust!\n";
                return true;
            }
        }

        std::cout << "They now have: " << dealer.score << '\n';
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
