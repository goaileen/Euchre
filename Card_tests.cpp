// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_suit_and_rank) {
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(two_spades.get_suit(), Card::SUIT_SPADES);

    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), Card::RANK_THREE);
    ASSERT_EQUAL(three_spades.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_suit(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_suit(Card::SUIT_SPADES), Card::SUIT_SPADES);

    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(jack_spades.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_CLUBS), Card::SUIT_CLUBS);
    //when left bower
    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_SPADES), Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_HEARTS), Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(), Card::SUIT_SPADES);
}

TEST(test_card_type) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades.is_face());
    ASSERT_FALSE(three_spades.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(three_spades.is_trump(Card::SUIT_CLUBS));
    ASSERT_TRUE(three_spades.is_trump(Card::SUIT_SPADES));

    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(jack_spades.is_face());
    ASSERT_TRUE(jack_spades.is_right_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(jack_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_CLUBS)); // since it is a left bower
    ASSERT_FALSE(jack_spades.is_trump(Card::SUIT_HEARTS));

}

TEST(test_card_self_comparison) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);

    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_TRUE(nine_diamonds < ten_spades);
}

TEST(test_card_trump_comparison) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);


    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, Card::SUIT_SPADES)); //vs left bower
    ASSERT_TRUE(Card_less(king_spades, jack_spades, Card::SUIT_SPADES)); //vs trump
    ASSERT_TRUE(Card_less(ace_diamonds, jack_spades, Card::SUIT_SPADES));// vs none

    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, jack_hearts, Card::SUIT_SPADES));
    // same scenario
    ASSERT_TRUE(Card_less(king_spades, jack_spades, jack_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_diamonds, jack_spades, jack_hearts, Card::SUIT_SPADES));

    ASSERT_TRUE(Card_less(ace_diamonds, jack_clubs, Card::SUIT_SPADES));// vs left bower
    ASSERT_TRUE(Card_less(ace_diamonds, king_spades, Card::SUIT_SPADES));// vs trump

    ASSERT_TRUE(Card_less(ace_diamonds, jack_clubs, jack_hearts, Card::SUIT_SPADES));
    // vs left bower
    ASSERT_TRUE(Card_less(ace_diamonds, king_spades, jack_hearts, Card::SUIT_SPADES));
    // vs trump

    ASSERT_TRUE(Card_less(king_spades, jack_clubs, Card::SUIT_SPADES));
    // trump vs left bower
    ASSERT_TRUE(Card_less(king_spades, jack_clubs, jack_hearts, Card::SUIT_SPADES));
    //left bower vs trump
}

TEST(test_card_led_comparison) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);

    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS); // normal highest

    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);

    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);//led suit


    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, nine_hearts, Card::SUIT_SPADES));
    //left vs right bower
    ASSERT_TRUE(Card_less(ace_hearts, jack_spades, nine_hearts, Card::SUIT_SPADES));
    //led vs right bower
    ASSERT_TRUE(Card_less(ace_hearts, jack_clubs, nine_hearts, Card::SUIT_SPADES));
    //led vs left bower
    ASSERT_TRUE(Card_less(king_spades, jack_spades, nine_hearts, Card::SUIT_SPADES));
    //trump vs trump
    ASSERT_TRUE(Card_less(ace_diamonds, jack_spades, nine_hearts, Card::SUIT_SPADES));
    // normal vs right bower
    ASSERT_TRUE(Card_less(ace_diamonds, jack_clubs, nine_hearts, Card::SUIT_SPADES));
    // normal vs left bower

    ASSERT_TRUE(Card_less(ace_diamonds, ace_hearts, nine_hearts, Card::SUIT_SPADES));
    //normal vs led suit
    ASSERT_TRUE(Card_less(ace_hearts, jack_spades, nine_hearts, Card::SUIT_SPADES));
    //led vs right
    ASSERT_TRUE(Card_less(ace_hearts, jack_clubs, nine_hearts, Card::SUIT_SPADES));
    //led vs left
    ASSERT_TRUE(Card_less(jack_hearts, ace_hearts, nine_hearts, Card::SUIT_SPADES));
    //led suit vs led suit

    ASSERT_TRUE(Card_less(ace_hearts, jack_hearts, nine_hearts, Card::SUIT_HEARTS));
    //ace vs jack in the trump(same trump and led)

    ASSERT_FALSE(Card_less(jack_clubs, jack_clubs, nine_hearts, Card::SUIT_SPADES));
    // self
}

TEST(test_card_none_comparison) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS); // normal highest
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);//led suit

    ASSERT_TRUE(Card_less(three_spades, ace_diamonds, Card::SUIT_HEARTS));//
    ASSERT_TRUE(Card_less(ace_spades, ace_diamonds, Card::SUIT_HEARTS));//same rank
    ASSERT_FALSE(Card_less(jack_diamonds, ace_diamonds, Card::SUIT_HEARTS));//left vs ace

    ASSERT_TRUE(Card_less(ace_spades, ace_diamonds, jack_clubs, Card::SUIT_HEARTS));
    //same rank
    ASSERT_TRUE(Card_less(jack_diamonds, ace_diamonds, jack_clubs, Card::SUIT_SPADES));
    //same suit
}

TEST(test_operator_overloading) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS); // normal highest
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(three_spades < ace_diamonds);
    ASSERT_TRUE(ace_spades < ace_diamonds);
    ASSERT_TRUE(jack_diamonds < ace_diamonds);

    ASSERT_TRUE(ace_diamonds > three_spades);
    ASSERT_TRUE(ace_diamonds > ace_spades);
    ASSERT_TRUE(ace_diamonds > jack_diamonds);

    ASSERT_TRUE(three_spades <= ace_diamonds);
    ASSERT_TRUE(ace_spades <= ace_diamonds);
    ASSERT_TRUE(jack_diamonds <= ace_diamonds);
    ASSERT_TRUE(ace_diamonds <= ace_diamonds);


    ASSERT_TRUE(ace_diamonds >= three_spades);
    ASSERT_TRUE(ace_diamonds >= ace_spades);
    ASSERT_TRUE(ace_diamonds >= jack_diamonds);
    ASSERT_TRUE(ace_diamonds >= ace_diamonds);

    ASSERT_TRUE(ace_diamonds == ace_diamonds);

    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_TRUE(three_spades != ace_diamonds);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);

}

TEST(test_Card_less_self) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
        Card::SUIT_CLUBS));
}

TEST(test_card_insertion) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST_MAIN()
