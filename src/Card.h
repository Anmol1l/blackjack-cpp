#ifndef BLACKJACK_CPP_DECK_H
#define BLACKJACK_CPP_DECK_H
#include <array>

struct Card {
    enum Rank {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks,
    };

    enum Suit {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,

        max_suits,
    };

    static constexpr std::array allRanks{
        rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen,
        rank_king
    };
    static constexpr std::array allSuits{suit_club, suit_diamond, suit_heart, suit_spade};

    Rank rank{};
    Suit suit{};

    friend std::ostream &operator<<(std::ostream &out, const Card &card);

    int value() const;
};


#endif //BLACKJACK_CPP_DECK_H
