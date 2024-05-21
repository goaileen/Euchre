// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <sstream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    
    Player * b = Player_factory("B", "Simple");
    ASSERT_EQUAL("B", b->get_name());
    
    Player * ivan = Player_factory("Ivan", "Human");
    
    ASSERT_EQUAL("Ivan", ivan->get_name());
    
    delete alice;
    delete b;
    delete ivan;
}

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()

    Player * ivan = Player_factory("Ivan", "Human");
    ostringstream oss;
    oss << * ivan;
    
    ASSERT_EQUAL(oss.str(), "Ivan");
    
    delete human;
    delete alice;
    delete ivan;
    
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes trump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);
    
    // alice will not orderup
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_SIX, Card::SUIT_CLUBS));
    
    // Alice makes trump
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    orderup = alice->make_trump(
      nine_diamonds,    // Upcard
      false,           // Alice is not the dealer
      1,              // First round
      trump           // Suit ordered up (if any)
    );
    ASSERT_FALSE(orderup);
    
    // round 2, order up if 1+ suit same color face card/bowers
    Player * ivan = Player_factory("Ivan", "Simple");
    ivan->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    ivan->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    ivan->add_card(Card(Card::RANK_SEVEN, Card::SUIT_SPADES));
    ivan->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    ivan->add_card(Card(Card::RANK_SIX, Card::SUIT_CLUBS));
    
    // Ivan makes trump
    // upcard is eight of hearts
    // ivan will orderup diamonds (same color suit as hearts)
    Card eight_hearts(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    orderup = ivan->make_trump(
        eight_hearts,
        false,
        2,
        trump
    );
    
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
    
    // screw the dealer
    Player * judea = Player_factory("Judea", "Simple");
    judea->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    judea->add_card(Card(Card::RANK_EIGHT, Card::SUIT_CLUBS));
    judea->add_card(Card(Card::RANK_SEVEN, Card::SUIT_SPADES));
    judea->add_card(Card(Card::RANK_FIVE, Card::SUIT_SPADES));
    judea->add_card(Card(Card::RANK_THREE, Card::SUIT_HEARTS));
    
    // judea makes trump
    // upcard is five of diamonds
    // judea will orderup hearts (same color suit as diamonds)
    Card five_diamonds(Card::RANK_FIVE, Card::SUIT_DIAMONDS);
    orderup = judea->make_trump(
        five_diamonds,
        true,
        2,
        trump
    );
    
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);
    
    // have only 2 trump cards
    Player* bob1 = Player_factory("Bob", "Simple");
        bob1->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
        bob1->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
        bob1->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
        bob1->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
        bob1->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
        // Bob makes trump
        orderup = bob1->make_trump(
            nine_spades,    // Upcard
            true,           // Bob is also the dealer
            1,              // First round
            trump           // Suit ordered up (if any)
        );
        // Verify Bob1's order up and trump suit
        ASSERT_TRUE(orderup);
        ASSERT_EQUAL(trump, Card::SUIT_SPADES);
    
    Player* bob2 = Player_factory("Bob", "Simple");
    // have only 2 trump cards(including left bower)
        bob2->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
        bob2->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
        bob2->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
        bob2->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
        bob2->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
        // Bob makes trump
        orderup = bob2->make_trump(
            nine_spades,    // Upcard
            true,           // Bob is also the dealer
            1,              // First round
            trump           // Suit ordered up (if any)
        );
        // Verify Bob1's order up and trump suit
        ASSERT_TRUE(orderup);
        ASSERT_EQUAL(trump, Card::SUIT_SPADES);
    
    // have only 1 trump cards
    Player* bob3 = Player_factory("Bob", "Simple");
        bob3->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
        bob3->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
        bob3->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
        bob3->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
        bob3->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
        // Bob makes trump
        orderup = bob3->make_trump(
            nine_spades,    // Upcard
            true,           // Bob is also the dealer
            1,              // First round
            trump           // Suit ordered up (if any)
        );
        // Verify Bob1's order up and trump suit
        ASSERT_FALSE(orderup);
        ASSERT_EQUAL(trump, Card::SUIT_SPADES);

        orderup = bob3->make_trump(
            nine_spades,    // Upcard
            true,           // Bob is also the dealer
            2,              // Second round
            trump           // Suit ordered up (if any)
        );
        ASSERT_TRUE(orderup); // screw the dealer
        ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

        orderup = bob3->make_trump(
            nine_spades,    // Upcard
            false,
            2,              // Second round
            trump           // Suit ordered up (if any)
        );
        ASSERT_TRUE(orderup);
        ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
    
    // have only 1 trump cards
    Player* bob4 = Player_factory("Bob", "Simple");
    bob4->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    bob4->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    bob4->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    bob4->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    bob4->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    string trump1;
    Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    orderup = bob4->make_trump(
        nine_clubs,    // Upcard
         false,
         2,              // Second round
         trump1         // Suit ordered up (if any)
     );
     ASSERT_TRUE(orderup);
     ASSERT_EQUAL(trump1, Card::SUIT_SPADES);

    // have only 1 trump cards
     Player* bob5 = Player_factory("Bob", "Simple");
     bob5->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
     bob5->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
     bob5->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
     bob5->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
     bob5->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
     string trump2 = Card::SUIT_HEARTS;
     orderup = bob5->make_trump(
         nine_clubs,    // Upcard
         false,
         2,              // Second round
         trump2       // Suit ordered up (if any)
     );
     ASSERT_FALSE(orderup);
     ASSERT_EQUAL(trump2, Card::SUIT_HEARTS);

    delete bob;
    delete alice;
    delete ivan;
    delete judea;
    delete bob1;
    delete bob2;
    delete bob3;
    delete bob4;
    delete bob5;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
    // bob leads with highest non trump
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

    // alice leads trick with highest trump (only trump cards in hand)
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

    alice->add_and_discard(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    
    card_led = alice->lead_card(Card::SUIT_SPADES);
    
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(card_led, jack_clubs); //check led card
    // alice will play jack of the trump suit (highest trump)
    
    Player* bob1 = Player_factory("Bob", "Simple");
    //it has right bower and left bower but play highest non trump card
        bob1->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
        bob1->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
        bob1->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
        bob1->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
        bob1->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

        // Bob leads
        Card bob1_led = bob1->lead_card(Card::SUIT_HEARTS);

        ASSERT_EQUAL(bob1_led, ace_spades); //check led card

        Player* bob2 = Player_factory("Bob", "Simple");//it only has trump cards
        bob2->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
        bob2->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));

        // Bob leads
        Card bob2_led = bob2->lead_card(Card::SUIT_HEARTS);

        Card left_bower(Card::RANK_JACK, Card::SUIT_DIAMONDS);
        ASSERT_EQUAL(bob2_led, left_bower); //check led card

        Player* bob3 = Player_factory("Bob", "Simple");//it only has trump cards
        bob3->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
        bob3->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

        // Bob leads
        Card bob3_led = bob3->lead_card(Card::SUIT_HEARTS);

        Card right_bower(Card::RANK_JACK, Card::SUIT_HEARTS);
        ASSERT_EQUAL(bob3_led, right_bower); //check led card

        Player* bob4 = Player_factory("Bob", "Simple");//it only has trump cards
        bob4->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
        bob4->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

        // Bob leads
        Card bob4_led = bob4->lead_card(Card::SUIT_HEARTS);

        Card correct(Card::RANK_JACK, Card::SUIT_CLUBS);
        ASSERT_EQUAL(bob4_led, correct); //check led card

        Player* bob5 = Player_factory("Bob", "Simple");//it only has trump cards
        bob5->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

        // Bob leads
        Card bob5_led = bob5->lead_card(Card::SUIT_HEARTS);

        Card correct_5(Card::RANK_JACK, Card::SUIT_DIAMONDS);
        ASSERT_EQUAL(bob5_led, correct_5); //check led card

        Player* bob6 = Player_factory("Bob", "Simple");//it only has trump cards
        bob6->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

        // Bob leads
        Card bob6_led = bob6->lead_card(Card::SUIT_CLUBS);

        Card correct_6(Card::RANK_JACK, Card::SUIT_DIAMONDS);
        ASSERT_EQUAL(bob6_led, correct_6); //check led card

    delete bob;
    delete alice;
    delete bob1;
    delete bob2;
    delete bob3;
    delete bob4;
    delete bob5;
    delete bob6;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
    // bob plays lowest card in his hand (cannot follow suit)
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
                                    
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

    // Alice plays a card
    // alice plays highest card that follows suit
    Card five_clubs(Card::RANK_FIVE, Card::SUIT_CLUBS);
    card_played = alice->play_card(
      five_clubs,  // five of clubs is led
      "Hearts"        // Trump suit
                                      
    );

    // Verify the card Alice played
    ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_CLUBS));

    // cant follow suit should play lowest card in hand
    // jack of diamonds is conisdered a heart, cannot play it
    // lowest card is nine of clubs
    Player * gabriel = Player_factory("Gabriel", "Simple");
    gabriel->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    gabriel->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    gabriel->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    // Gabriel plays a card
    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    card_played = gabriel->play_card(
      king_diamonds,  // king of Diamonds is led
      "Hearts"        // Trump suit

    );

    // Verify the card Gabriel played
    ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_CLUBS));

    Player * ivan = Player_factory("Ivan", "Simple");
    ivan->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    ivan->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    ivan->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    ivan->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    ivan->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

    // Ivan plays a card
    card_played = ivan->play_card(
      nine_diamonds,  // Nine of Diamonds is led
      "Hearts"        // Trump suit
                                      
    );

    // Verify the card Ivan played
    ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    
    Player * judea = Player_factory("Judea", "Simple");
    judea->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    judea->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    judea->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    judea->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    judea->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));

    // Judea plays a card
    Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
    card_played = judea->play_card(
      king_spades,  // King of Spades is led
      "Spades"        // Trump suit -- trump + led suit are same
                                      
    );
    // Verify the card Judea played
    ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));
    
    Player* bob1 = Player_factory("Bob", "Simple");
        bob1->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
        bob1->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));//left bower

        Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
        Card bob1_card_played = bob1->play_card(
            king_hearts,  // king of hearts is led
            "Hearts"        // Trump suit
        );
        // Verify the card Bob played
        ASSERT_EQUAL(bob1_card_played, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

        Player* bob2 = Player_factory("Bob", "Simple");
        bob2->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
        bob2->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
        bob2->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

        Card king_clubs(Card::RANK_KING, Card::SUIT_CLUBS);
        Card bob2_card_played = bob2->play_card(
            king_clubs,  // king of clubs is led
            "Hearts"        // Trump suit
        );
        // Verify the card Bob played
        ASSERT_EQUAL(bob2_card_played, Card(Card::RANK_ACE, Card::SUIT_CLUBS));

        Player* bob3 = Player_factory("Bob", "Simple");
        bob3->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
        bob3->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

        Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
        Card bob3_card_played = bob3->play_card(
            jack_hearts,  // jack of hearts is led
            "Diamonds"        // Trump suit
        );
        // Verify the card Bob played
        ASSERT_EQUAL(bob3_card_played, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));

        Player* bob4 = Player_factory("Bob", "Simple");
        bob4->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
        bob4->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

        Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
        Card bob4_card_played = bob4->play_card(
            jack_spades,  // Jack of Spades is led
            "Hearts"        // Trump suit
        );
    
        // Verify the card Bob played
        ASSERT_EQUAL(bob4_card_played, Card(Card::RANK_ACE, Card::SUIT_HEARTS));

        Player* bob5 = Player_factory("Bob", "Simple");
        bob5->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
        bob5->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
        bob5->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));

        Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
        Card bob5_card_played = bob5->play_card(
            jack_clubs,  // jack of clubs is led
            "Spades"        // Trump suit
        );
        // Verify the card Bob played
        ASSERT_EQUAL(bob5_card_played, Card(Card::RANK_NINE, Card::SUIT_CLUBS));

        Player* bob6 = Player_factory("Bob", "Simple");
        bob6->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
        bob6->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));

        Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
        Card bob6_card_played = bob6->play_card(
            ten_clubs,  //ten of clubs is led
            "Spades"        // Trump suit
        );
        // Verify the card Bob played
        ASSERT_EQUAL(bob6_card_played, Card(Card::RANK_TEN, Card::SUIT_HEARTS));

        Player* bob7 = Player_factory("Bob", "Simple");
        bob7->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
        bob7->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
        bob7->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));

        Card bob7_card_played = bob7->play_card(
            ten_clubs,  //ten of clubs is led
            "Spades"        // Trump suit
        );
        // Verify the card Bob played
        ASSERT_EQUAL(bob7_card_played, Card(Card::RANK_TEN, Card::SUIT_HEARTS));

        Player* bob8 = Player_factory("Bob", "Simple");
        bob8->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
        bob8->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
        bob8->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

        Card king_dia(Card::RANK_KING, Card::SUIT_DIAMONDS);
        Card bob8_card_played = bob8->play_card(
            king_dia,  //king of diamonds is led
            "Hearts"        // Trump suit
        );
        // Verify the card Bob played
        ASSERT_EQUAL(bob8_card_played, Card(Card::RANK_NINE, Card::SUIT_CLUBS));

        Player* bob9 = Player_factory("Bob", "Simple");
        bob9->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
        bob9->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
        bob9->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

        Card jack_dia(Card::RANK_JACK, Card::SUIT_DIAMONDS);
        Card bob9_card_played = bob9->play_card(
            jack_dia,  //jack of diamonds led
            "Hearts"        // Trump suit
        );
        // Verify the card Bob played
        ASSERT_EQUAL(bob9_card_played, Card(Card::RANK_JACK, Card::SUIT_HEARTS));

    
    delete bob;
    delete alice;
    delete gabriel;
    delete ivan;
    delete judea;
    delete bob1;
    delete bob2;
    delete bob3;
    delete bob4;
    delete bob5;
    delete bob6;
    delete bob7;
    delete bob8;
    delete bob9;
}
TEST_MAIN()
