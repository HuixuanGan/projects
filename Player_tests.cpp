// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_simple_player_make_trump_round_1_pass) {
    Player * c = Player_factory("Chuan", "Simple");
    const int round = 1;
    string trump;
    c -> add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    c -> add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    c -> add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    c -> add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    
    ASSERT_FALSE(c -> make_trump(Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                                 true, round, trump));
    delete c;
}

TEST(test_simple_player_make_trump_round_1_order_up) {
    Player * c = Player_factory("Chuan", "Simple");
    const int round = 1;
    string trump;
    c -> add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    c -> add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    
    ASSERT_TRUE(c -> make_trump(Card(Card::RANK_TEN, Card::SUIT_CLUBS), false, round, trump));
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
    delete c;
}

TEST(test_simple_player_make_trump_round_2_pass) {
    Player * c = Player_factory("Chuan", "Simple");
    const int round = 2;
    string trump;
    c -> add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    c -> add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    
    ASSERT_FALSE(c -> make_trump(Card(Card::RANK_KING, Card::SUIT_DIAMONDS), false, round, trump));
    delete c;
}

TEST(test_simple_player_make_trump_round_2_dealer) {
    Player * c = Player_factory("Chuan", "Simple");
    const int round = 2;
    string trump;
    c -> add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    c -> add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    
    ASSERT_TRUE(c -> make_trump(Card(Card::RANK_KING, Card::SUIT_DIAMONDS), true, round, trump));
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);
    delete c;
}

TEST(test_simple_player_make_trump_round_2_order_up) {
    Player * c = Player_factory("Chuan", "Simple");
    const int round = 2;
    string trump;
    c -> add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    c -> add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    
    ASSERT_TRUE(c -> make_trump(Card(Card::RANK_KING, Card::SUIT_DIAMONDS), false, round, trump));
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);
    delete c;
}

// roundabout test with adding, dropping, and play several times
TEST(test_simple_player_processing_card) {
    Player * c = Player_factory("Chuan", "Simple");
    c -> add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    c -> add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    
    // add Spades card, should drop the Jack of Hearts
    c -> add_and_discard(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    
    Card * led_card = new Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    // play card, should return Nine of Spades
    ASSERT_EQUAL(Card(Card::RANK_NINE, Card::SUIT_SPADES),
                 c -> play_card(*led_card, Card::SUIT_SPADES));
    
    c -> add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    Card * led_card_1 = new Card(Card::RANK_QUEEN,
                                 Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card(Card::RANK_TEN, Card::SUIT_CLUBS), c -> play_card(*led_card_1, Card::SUIT_SPADES));
    
    delete c;
    delete led_card;
    delete led_card_1;
}

TEST(test_simple_player_lead_card_with_non_trump) {
    Player * c = Player_factory("Chuan", "Simple");
    c -> add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    c -> add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                 c -> lead_card(Card::SUIT_SPADES));
    delete c;
}

TEST(test_simple_player_lead_card_all_trump) {
    Player * c = Player_factory("Chuan", "Simple");
    c -> add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    c -> add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_SPADES),
                      c -> lead_card(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_CLUBS),
                 c -> lead_card(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card(Card::RANK_ACE, Card::SUIT_SPADES),
                 c -> lead_card(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card(Card::RANK_KING, Card::SUIT_SPADES),
                 c -> lead_card(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card(Card::RANK_TEN, Card::SUIT_SPADES),
                 c -> lead_card(Card::SUIT_SPADES));
    delete c;
}

TEST(test_player_get_name_1) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_insertion) {
   //Create a Human player
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
  delete human;
  delete alice;
}


TEST(test_simple_player_lead_card_1) {
  // Bob's hand
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

  delete bob;
}
TEST(test_simple_player_lead_card_2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_SPADES) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}
TEST(test_simple_player_lead_card_3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_SPADES) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_led, jack_clubs); //check led card

  delete bob;
}

TEST(test_simple_player_play_card_1) {
  // Bob's hand
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
  delete bob;
}
TEST(test_simple_player_play_card_2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  delete bob;
}
TEST(test_simple_player_play_card_3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  delete bob;
}
TEST(test_simple_player_play_card_4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  delete bob;
}
TEST(test_simple_player_play_card_5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  delete bob;
}

TEST(test_simple_player_play_card_6) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
    bob->add_and_discard(
      Card(Card::RANK_NINE, Card::SUIT_SPADES) // upcard
    );
    Card card_led = bob->lead_card(Card::SUIT_SPADES);
    
  Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
  Card card_played = bob->play_card(
    nine_hearts,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_SPADES));
  delete bob;
}

TEST_MAIN()
