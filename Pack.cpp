// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"

Pack::Pack()
{
    int cardIndex = 0;
    for (int i = 0; i < NUM_SUITS; i++) {
        for (int j = 7; j < NUM_RANKS; j++) {
            cards[cardIndex] = Card(RANK_NAMES_BY_WEIGHT[j], SUIT_NAMES_BY_WEIGHT[i]);
            cardIndex++;
        }
    }
    next = 0;
}

Pack::Pack(std::istream& pack_input)
{
    std::string rank;
    std::string suit;
    std::string of;
    for (int i = 0; i < PACK_SIZE; i++) {
        pack_input >> rank >> of >> suit;
        cards[i] = Card(rank, suit);
    }
    next = 0;
}

Card Pack::deal_one()
{
    return cards[next++];
}

void Pack::reset()
{
    next = 0;
}

void Pack::shuffle()
{
    for (int t = 0; t < 7; t++)
    {
        std::array<Card, PACK_SIZE> copyPack;
        copyPack = cards;
        int first_deck_start = 0;
        int second_deck_start = 12;
        for (int i = 0; i < PACK_SIZE; i++) {
            if (i % 2 == 0) {
                cards[i] = copyPack[second_deck_start++];
            }
            else {
                cards[i] = copyPack[first_deck_start++];
            }
        }
    }
    reset();
}

bool Pack::empty() const
{
    return next >= PACK_SIZE;
}
