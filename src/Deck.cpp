#include "Deck.h"
#include <cassert>
#include "Random.h"
#include <algorithm>

Deck::Deck() {
    std::size_t index{0};
    for (auto suit: Card::allSuits) {
        for (auto rank: Card::allRanks) {
            m_cards[index] = Card{rank, suit};
            index++;
        }
    }
}

Card Deck::dealCard() {
    assert(m_currCard < m_cards.size() && "Deck ran out of cards");
    return m_cards[m_currCard++];
}

void Deck::shuffle() {
    std::ranges::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
    m_currCard = 0;
}