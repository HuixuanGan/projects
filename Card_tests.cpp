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

TEST(test_default_ctor) {
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_get_rank) {
    Card c(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::RANK_KING, c.get_rank());
}

TEST(test_get_suit) {
    Card c(Card::RANK_TWO, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::SUIT_CLUBS, c.get_suit());
}

TEST(test_get_suit_with_trump) {
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::SUIT_CLUBS, c.get_suit(Card::SUIT_CLUBS));
}

TEST(test_is_face) {
    Card c(Card::RANK_KING, Card::SUIT_CLUBS);
    ASSERT_TRUE(c.is_face());
    
    Card c2(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_FALSE(c2.is_face());
    
    Card c3(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(c3.is_face());
}

TEST(test_is_trump_simple) {
    Card c(Card::RANK_TWO, Card::SUIT_CLUBS);
    ASSERT_TRUE(c.is_trump(Card::SUIT_CLUBS));
    
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c2.is_trump(Card::SUIT_SPADES));
}

TEST(test_is_trump_left_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c.is_trump(Card::SUIT_CLUBS));
}

TEST(test_is_right_bower_correct) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(c.is_right_bower(Card::SUIT_CLUBS));
}

TEST(test_is_right_bower_false) {
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_CLUBS));
    
    Card c2(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_CLUBS));
}

TEST(test_is_left_bower_correct) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_left_bower(Card::SUIT_DIAMONDS));
}

TEST(test_is_left_bower_false) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_HEARTS));
    
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_HEARTS));
    
    Card c3(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_CLUBS));
}

TEST(operator_simple_case) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c4(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    
    ASSERT_TRUE(c > c2);
    ASSERT_TRUE(c >= c2);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c >= c4);
    
    ASSERT_TRUE(c < c3);
    ASSERT_TRUE(c <= c3);
    ASSERT_TRUE(c4 < c2);
    ASSERT_TRUE(c4 <= c2);
    
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c == c2);
    
    ASSERT_FALSE(c != c);
    ASSERT_TRUE(c != c2);
    ASSERT_TRUE(c2 != c3);
    ASSERT_TRUE(c != c4);
}

TEST(test_print_to_stream) {
    stringstream ss;
    Card c;
    ss << c;
    ASSERT_EQUAL(ss.str(), "Two of Spades");
}

TEST(test_card_less_no_led_suit) {
    string cur_trump = Card::SUIT_CLUBS;
    // right bow
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    // left bow
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    // trump card
    Card c3(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_CLUBS);
    // non-trump card
    Card c5(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c6(Card::RANK_KING, Card::SUIT_DIAMONDS);
    
    ASSERT_FALSE(Card_less(c, c, cur_trump));
    ASSERT_FALSE(Card_less(c, c2, cur_trump));
    ASSERT_TRUE(Card_less(c2, c, cur_trump));
    ASSERT_TRUE(Card_less(c3, c, cur_trump));
    ASSERT_TRUE(Card_less(c4, c3, cur_trump));
    ASSERT_TRUE(Card_less(c5, c3, cur_trump));
    ASSERT_TRUE(Card_less(c5, c6, cur_trump));
}

TEST(test_card_less_with_led_suit) {
    string cur_trump = Card::SUIT_SPADES;
    string cur_led = Card::SUIT_CLUBS;
    
    // right bow
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    // left bow
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    // trump card
    Card c3(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    // led card
    Card c5(Card::RANK_KING, Card::SUIT_CLUBS);
    Card c6(Card::RANK_TEN, Card::SUIT_CLUBS);
    // rest card
    Card c7(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c8(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    
    ASSERT_FALSE(Card_less(c, c2, c5, cur_trump));
    ASSERT_FALSE(Card_less(c4, c5, c5, cur_trump));
    ASSERT_FALSE(Card_less(c4, c5, c5, cur_trump));
    
    ASSERT_TRUE(Card_less(c1, c7, c5, cur_trump));
    ASSERT_TRUE(Card_less(c2, c, c5, cur_trump));
    ASSERT_TRUE(Card_less(c3, c2, c5, cur_trump));
    ASSERT_TRUE(Card_less(c4, c3, c5, cur_trump));
    ASSERT_TRUE(Card_less(c5, c3, c5, cur_trump));
    ASSERT_TRUE(Card_less(c7, c5, c5, cur_trump));
    ASSERT_TRUE(Card_less(c8, c7, c5, cur_trump));
}

TEST_MAIN()
