// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"

// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

bool isValidSuit(const std::string& suit_in) {
    if (suit_in == "Spades" || suit_in == "Hearts" ||
        suit_in == "Clubs" || suit_in == "Diamonds") {
        return true;
    }
    else return false;
}

Card::Card()
{
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

Card::Card(const std::string& rank_in, const std::string& suit_in)
{
    bool isRankMatch = false;
    bool isSuitMatch = false;
    for (int i = 0; i < NUM_RANKS; i++) {
        if (rank_in == RANK_NAMES_BY_WEIGHT[i]) {
            rank = RANK_NAMES_BY_WEIGHT[i];
            isRankMatch = true;
            break;
        }
    }

    for (int i = 0; i < NUM_SUITS;i++) {
        if (suit_in == SUIT_NAMES_BY_WEIGHT[i]) {
            suit = SUIT_NAMES_BY_WEIGHT[i];
            isSuitMatch = true;
            break;
        }
    }

    if (!isRankMatch || !isSuitMatch) {
        assert(false);
    }
}

std::string Card::get_rank() const
{
    return rank;
}

std::string Card::get_suit() const
{
    return suit;
}

std::string Card::get_suit(const std::string& trump) const
{
    if (is_left_bower(trump)) {
        return trump;
    }
    else {
        return suit;
    }
}

bool Card::is_face() const
{
    if (rank == RANK_JACK || rank == RANK_QUEEN ||
        rank == RANK_KING || rank == RANK_ACE) {
        return true;
    }
    else {
        return false;
}
}

bool Card::is_right_bower(const std::string& trump) const
{
    assert(isValidSuit(trump));
    if (trump == suit && rank == RANK_JACK) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_left_bower(const std::string& trump) const
{
    assert(isValidSuit(trump));
    if (rank == RANK_JACK) {
        if (trump == SUIT_SPADES && suit == SUIT_CLUBS) {
            return true;
        }
        else if (trump == SUIT_CLUBS && suit == SUIT_SPADES) {
            return true;
        }
        else if (trump == SUIT_HEARTS && suit == SUIT_DIAMONDS) {
            return true;
        }
        else if (trump == SUIT_DIAMONDS && suit == SUIT_HEARTS) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Card::is_trump(const std::string& trump) const
{
    assert(isValidSuit(trump));
    if (suit == trump || is_left_bower(trump)) {
        return true;
    }
    else {
        return false;
    }
}

bool operator<(const Card& lhs, const Card& rhs)
{
    if (lhs.get_rank() == rhs.get_rank()) {
        for (int i = 0; i < NUM_SUITS; i++) {
            if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()) {
                return false;
            }
            // rhs is lower. if same, then return false
            if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()) {
                return true;
            }
            //lhs is lower. Array is lower -> higher
        }
        assert(false);
    }
    else {
        for (int i = 0; i < NUM_RANKS; i++) {
            if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
                return false;
            }
            //rhs is lower. if same, then return false
            if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
                return true;
            }
            //lhs is lower. Array is lower -> higher
        }
        assert(false);
    }
}

bool operator<=(const Card& lhs, const Card& rhs)
{
    if (lhs < rhs || lhs == rhs) {
        return true;
    }
    else {
        return false;
    }
}

bool operator>(const Card& lhs, const Card& rhs)
{
    if (rhs < lhs) {
        return true;
    }
    else {
        return false;
    }
}

bool operator>=(const Card& lhs, const Card& rhs)
{
    if (rhs <= lhs) {
        return true;
    }
    else {
        return false;
    }
}

bool operator==(const Card& lhs, const Card& rhs)
{
    if (lhs.get_suit() == rhs.get_suit() &&
        lhs.get_rank() == rhs.get_rank()) {
        return true;
    }
    else {
        return false;
    }
}

bool operator!=(const Card& lhs, const Card& rhs)
{
    if (lhs == rhs) {
        return false;
    }
    else {
        return true;
    }
}

std::string Suit_next(const std::string& suit)
{
    assert(isValidSuit(suit));
    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else {
        return Card::SUIT_HEARTS;
    }
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

int get_rank_in_trump(const Card& a, const std::string& trump) {
    if (a.is_trump(trump)) {
        if (a.is_right_bower(trump)) return 6;
        if (a.is_left_bower(trump)) return 5;
        std::string aRank = a.get_rank();
        if (aRank == Card::RANK_ACE) return 4;
        if (aRank == Card::RANK_KING) return 3;
        if (aRank == Card::RANK_QUEEN) return 2;
        if (aRank == Card::RANK_TEN) return 1;
        if (aRank == Card::RANK_NINE) return 0;
    }
//    else {
//        return -1;
//    }
    return -1;
}

bool Card_less(const Card& a, const Card& b, const std::string& trump)
{
    bool isAtrump = a.is_trump(trump);
    bool isBtrump = b.is_trump(trump);
    if (isAtrump && !isBtrump) {
        return false;
    }
    else if (!isAtrump && isBtrump) {
        return true;
    }
    else if (isAtrump && isBtrump) {
        if (get_rank_in_trump(a, trump) < get_rank_in_trump(b, trump)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {//if !isAtrump && !isBtrump
        return a < b;
    }
}

bool Card_less(const Card& a, const Card& b, const Card& led_card,
    const std::string& trump)
{
    bool isAtrump = a.is_trump(trump);
    bool isBtrump = b.is_trump(trump);
    bool isAledTrump = (a.is_trump(led_card.get_suit()) &&
        !a.is_left_bower(led_card.get_suit()));
    bool isBledTrump = (b.is_trump(led_card.get_suit()) &&
        !b.is_left_bower(led_card.get_suit()));
    
    // if led and trump suit is the same
    if (led_card.get_suit() == trump) {
        return Card_less(a, b, trump);
    }
    if (isAtrump && !isBtrump) {
        return false;
    }
    else if (!isAtrump && isBtrump) {
        return true;
    }
    else if (isAtrump && isBtrump) {
        if (get_rank_in_trump(a, trump) < get_rank_in_trump(b, trump))
            return true;
        else return false;
    }
    else if (isAledTrump && !isBledTrump) {
        return false;
    }
    else if (!isAledTrump && isBledTrump) {
        return true;
    }
    else if (isAledTrump && isBledTrump) {
        return a < b; // same suit so only need to compare rank
    }
    else {
        return a < b; // no trump no led suit
    }

}
// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
