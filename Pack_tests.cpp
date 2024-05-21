// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

//TEST(test_pack_default_ctor) {
////    Pack pack;
////    Card first_card = pack.deal_one();
////    ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
//    Pack pack;
//    Card first_card = pack.deal_one();
//    Card last_card;
//    ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
//    for (int i = 0; i < 24; i++) {
//        last_card = pack.deal_one();
//    }
//    ASSERT_EQUAL(first_card, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
//}
//
//TEST(test_pack_istream_ctor) {
//  const string filename = "pack.in";
//  ifstream ifs(filename);
//  assert(ifs.is_open());
//  Pack pack(ifs);
//    Card last_card;
//  Card first_card = pack.deal_one();
//    for (int i = 0; i < 24; i++) {
//        last_card = pack.deal_one();
//    }
//    // Should be well behaved when you print it though!
//    
//    string output_correct = "Nine of Spades\n";
//    std::ostringstream ss_output;
//    operator<<(ss_output, first_card);
//    string actual = ss_output.str();
//    std::cout << actual << std::endl;
//    ASSERT_EQUAL(actual, output_correct);
//    
//    string output_correct2 = "Ace of Diamonds\n";
//    std::ostringstream ss_output2;
//    operator<<(ss_output2, last_card);
//    string actual2 = ss_output2.str();
//    std::cout << actual2 << std::endl;
//    ASSERT_EQUAL(actual2, output_correct2);
//    
//  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
//    ASSERT_EQUAL(last_card, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
//}
//
//TEST(test_pack_reset) {
//  Pack pack;
//  pack.deal_one();
//  pack.reset();
//  Card first_card = pack.deal_one();
//    Card last_card;
//  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
//    pack.reset();
//    for (int i = 0; i < 24; i++) {
//        last_card = pack.deal_one();
//    }
//    pack.reset();
//    ASSERT_EQUAL(last_card, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
//}
//
//TEST(test_pack_empty) {
//  Pack pack;
//    // 24 being pack_size
//  for (int i = 0; i < 24; ++i) {
//    pack.deal_one();
//    ASSERT_FALSE(pack.empty());
//  }
//  pack.deal_one();
//  ASSERT_TRUE(pack.empty());
//}
//
//TEST(test_pack_shuffle) {
//  Pack pack;
//  pack.shuffle();
//  Card first_card = pack.deal_one();
//    Card mid_card;
//  ASSERT_EQUAL(first_card, Card(Card::RANK_KING, Card::SUIT_CLUBS));
//    for (int i = 0; i < 12; i++) {
//        mid_card = pack.deal_one();
//    }
//    pack.reset();
//    first_card = pack.deal_one();
//    ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
//    
//}
 

TEST_MAIN()
