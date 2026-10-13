#ifndef BLACKJACK_CPP_DECK_H
#define BLACKJACK_CPP_DECK_H
#include <array>
#include "Card.h"

class Deck {
private:
    std::array<Card, 52> m_cards{};
    std::size_t m_currCard {0};
public:
    Deck();
    Card dealCard();
    void shuffle();
};


#endif //BLACKJACK_CPP_DECK_H
