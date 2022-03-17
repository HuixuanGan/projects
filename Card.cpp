// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include <cassert>
#include <iostream>
#include <string>
#include <cstring>


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


// below are helper methods
static bool is_valid_rank(const std::string &rank_in) {
    for (int i = 0; i < NUM_RANKS; i++) {
        if (rank_in == RANK_NAMES_BY_WEIGHT[i]) {
            return true;
        }
    }
    return false;
}

static bool is_valid_suit(const std::string &suit_in) {
    for (int i = 0; i < NUM_SUITS; i++) {
        if (suit_in == SUIT_NAMES_BY_WEIGHT[i]) {
            return true;
        }
    }
    return false;
}

static bool is_suits_same_color(const std::string suit1,
                           const std::string suit2) {
    // black: spades and clubs
    return (suit1 == Card::SUIT_SPADES && suit2 == Card::SUIT_CLUBS)||
    (suit1 == Card::SUIT_CLUBS && suit2 == Card::SUIT_SPADES)||
    // red: diamonds and hearts
    (suit1 == Card::SUIT_DIAMONDS && suit2 == Card::SUIT_HEARTS)||
    (suit1 == Card::SUIT_HEARTS && suit2 == Card::SUIT_DIAMONDS);
}

static int get_suit_order(const std::string suit_in) {
    for (int i = 0 ; i < NUM_SUITS; i++) {
        if (suit_in == SUIT_NAMES_BY_WEIGHT[i]) {
            return i;
        }
    }
    return -1;
}

static int get_rank_order(const std::string rank_in) {
    for (int i = 0; i < NUM_RANKS; i++) {
        if (rank_in == RANK_NAMES_BY_WEIGHT[i]) {
            return i;
        }
    }
    return -1;
}


//EFFECTS Initializes Card to the Two of Spades
Card::Card() {
    std::string rank_in = std::string(Card::RANK_TWO);
    std::string suit_in = std::string(Card::SUIT_SPADES);
    this -> rank = rank_in;
    this -> suit = suit_in;
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in) {
    assert(is_valid_rank(rank_in) &&
           is_valid_suit(suit_in));
    this -> rank = rank_in;
    this -> suit = suit_in;
}
//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return this -> rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const {
    return this -> suit;

}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {
    assert(is_valid_suit(trump));
    if (rank == Card::RANK_JACK && is_suits_same_color(suit, trump)) {
        return trump;
    }
    else {
        return this -> suit;
    }
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const{
    return rank == Card::RANK_JACK ||
           rank == Card::RANK_QUEEN ||
           rank == Card::RANK_KING ||
           rank == Card::RANK_ACE;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const{
    assert(is_valid_suit(trump));
    if (rank == Card::RANK_JACK &&
        suit == trump) {
        return true;
    }
    return false;
}
//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const{
    assert(is_valid_suit(trump));
    if (rank == Card::RANK_JACK &&
        !(is_right_bower(trump)) &&
        is_suits_same_color(suit, trump)) {
        return true;
    }
    return false;
}
//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const{
    assert(is_valid_suit(trump));
    return suit == trump ||is_left_bower(trump);
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    std::string left_rank = lhs.get_rank();
    std::string right_rank = rhs.get_rank();
    std::string left_suit = lhs.get_suit();
    std::string right_suit = rhs.get_suit();
    if (get_rank_order(left_rank) < get_rank_order(right_rank)) {
        return true;
    }
    if (get_rank_order(left_rank) > get_rank_order(right_rank)) {
        return false;
    }
    return get_suit_order(left_suit) < get_suit_order(right_suit);
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    return lhs < rhs || lhs == rhs;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    return rhs < lhs;
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    return rhs <= lhs;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    return lhs.get_rank() == rhs.get_rank() &&
    lhs.get_suit() == rhs.get_suit();
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    return !(lhs == rhs);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
    assert(is_valid_suit(suit));
        if (suit == Card::SUIT_HEARTS) {
            return Card::SUIT_DIAMONDS;
        }
        else if (suit == Card::SUIT_DIAMONDS) {
            return Card::SUIT_HEARTS;
        }
        else if (suit == Card::SUIT_CLUBS) {
            return Card::SUIT_SPADES;
        }
        return Card::SUIT_CLUBS;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
    assert(is_valid_suit(trump));
    // a is bower
    if (a.is_right_bower(trump)) {
        return false;
    }
    else if (a.is_left_bower(trump)) {
        return b.is_right_bower(trump);
    }

    // a is trump card
    else if (a.is_trump(trump)) {
        // b is bower
        if (b.is_right_bower(trump) || b.is_left_bower(trump)) {
            return true;
        }
        // b is trump
        else if (b.is_trump(trump)) {
            return a < b;
        }
        // b is not trump
        return false;
    }
    // a is not trump
    else {
        // b is bower
        if (b.is_right_bower(trump) || b.is_left_bower(trump)) {
            return true;
        }
        // b is trump
        else if (b.is_trump(trump)) {
            return true;
        }
        // b is not trump
        else {
            return a < b;
        }
    }
}
//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    assert(is_valid_suit(trump));
    std::string led_suit = led_card.get_suit();
    // a is bower
    if (a.is_right_bower(trump)) {
        return false;
    }
    else if (a.is_left_bower(trump)) {
        return b.is_right_bower(trump);
    }
    // a is trump card
    else if (a.is_trump(trump)) {
        // b is bower
        if (b.is_right_bower(trump) || b.is_left_bower(trump)) {
            return true;
        }
        // b is trump
        if (b.is_trump(trump)) {
            return a < b;
        }
        // b is not trump
        return false;
    }
    // a is led suit
    else if (a.get_suit() == led_suit) {
        // b is bower
        if (b.is_right_bower(trump) || b.is_left_bower(trump)) {
            return true;
        }
        // b is trump
        else if (b.is_trump(trump)) {
            return true;
        }
        // b is led suit
        else if (b.get_suit() == led_suit) {
            return a < b;
        }
        // b is in other suit
        return false;
    }
    // a is neither bower, trump, or led suit
    else {
        // b is bower
        if (b.is_right_bower(trump) || b.is_left_bower(trump)) {
            return true;
        }
        // b is trump
        else if (b.is_trump(trump)) {
            return true;
        }
        // b is led suit
        else if (b.get_suit() == led_suit) {
            return true;
        }
        // b is neither
        return a < b;
    }
    
}

