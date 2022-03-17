// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

// THESE TEST CASES ARE NOT VERY THOROUGH.
// YOU NEED TO WRITE YOUR OWN COMPREHENSIVE TEST CASES IN Pack_tests.cpp

static const int PACK_SIZE = 24;

TEST(test_pack_default_ctor) {
  Pack pack;
  Card first_card = pack.deal_one();
    for (int i = 0; i < 4; i++){
        pack.deal_one();
    }
    Card sixth_card = pack.deal_one();
    Card seventh_card = pack.deal_one();
    for (int i = 0; i < 5; i++){
        pack.deal_one();
    }
    Card thirteenth_card = pack.deal_one();
    for (int i = 0; i < 5; i++){
        pack.deal_one();
    }
    Card nineteenth_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  ASSERT_EQUAL(sixth_card, Card(Card::RANK_ACE, Card::SUIT_SPADES));
  ASSERT_EQUAL(seventh_card, Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  ASSERT_EQUAL(thirteenth_card, Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  ASSERT_EQUAL(nineteenth_card, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    for (int i = 0; i < 5; i++){
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
}

TEST(test_pack_istream_ctor) {
  const string filename = "pack.in";
  ifstream ifs(filename);
  assert(ifs.is_open());
  Pack pack(ifs);
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    for (int i = 0; i < 4; i++){
        pack.deal_one();
    }
    Card sixth_card = pack.deal_one();
    Card seventh_card = pack.deal_one();
    for (int i = 0; i < 5; i++){
        pack.deal_one();
    }
    Card thirteenth_card = pack.deal_one();
    for (int i = 0; i < 5; i++){
        pack.deal_one();
    }
    Card nineteenth_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  ASSERT_EQUAL(sixth_card, Card(Card::RANK_ACE, Card::SUIT_SPADES));
  ASSERT_EQUAL(seventh_card, Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  ASSERT_EQUAL(thirteenth_card, Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  ASSERT_EQUAL(nineteenth_card, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    for (int i = 0; i < 5; i++){
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
}

TEST(test_pack_reset) {
  Pack pack;
  pack.deal_one();
  pack.reset();
  Card first_card = pack.deal_one();
    for (int i = 0; i < 4; i++){
        pack.deal_one();
    }
    Card sixth_card = pack.deal_one();
    Card seventh_card = pack.deal_one();
    for (int i = 0; i < 5; i++){
        pack.deal_one();
    }
    Card thirteenth_card = pack.deal_one();
    for (int i = 0; i < 5; i++){
        pack.deal_one();
    }
    Card nineteenth_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  ASSERT_EQUAL(sixth_card, Card(Card::RANK_ACE, Card::SUIT_SPADES));
  ASSERT_EQUAL(seventh_card, Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  ASSERT_EQUAL(thirteenth_card, Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  ASSERT_EQUAL(nineteenth_card, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    for (int i = 0; i < 5; i++){
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
    
}

TEST(test_pack_empty) {
  Pack pack;
  for (int i = 0; i < PACK_SIZE - 1; ++i) {
    pack.deal_one();
    ASSERT_FALSE(pack.empty());
  }
  pack.deal_one();
  ASSERT_TRUE(pack.empty());
}

TEST(test_pack_shuffle) {
  Pack pack;
  pack.shuffle();
    Card first_card = pack.deal_one();
      Card second_card = pack.deal_one();
    for (int i = 0; i < 4; i++){
        pack.deal_one();
    }
      Card seventh_card = pack.deal_one();
      Card eighth_card = pack.deal_one();
    for (int i = 0; i < 4; i++){
        pack.deal_one();
    }
      Card thirteenth_card = pack.deal_one();
      Card fourteenth_card = pack.deal_one();
    for (int i = 0; i < 4; i++){
        pack.deal_one();
    }
      Card nineteenth_card = pack.deal_one();
      Card twentyth_card = pack.deal_one();
    for (int i = 0; i < 2; i++){
        pack.deal_one();
    }
      Card twentythird_card = pack.deal_one();
      Card twentyfourth_card = pack.deal_one();
   
    ASSERT_EQUAL(first_card, Card(Card::RANK_KING, Card::SUIT_CLUBS));
    ASSERT_EQUAL(second_card, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    ASSERT_EQUAL(seventh_card, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(eighth_card, Card(Card::RANK_KING, Card::SUIT_HEARTS));
    ASSERT_EQUAL(thirteenth_card, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(fourteenth_card, Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    ASSERT_EQUAL(nineteenth_card, Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(twentyth_card, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    ASSERT_EQUAL(twentythird_card, Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    ASSERT_EQUAL(twentyfourth_card, Card(Card::RANK_TEN, Card::SUIT_HEARTS));

  }

TEST_MAIN()
