// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"
#include "Card.h"
#include <fstream>
#include <sstream>

/* Pack.h
 *
 * Represents a pack of playing cards
 * Project UID 1d9f47bfc76643019cfbf037641defe1
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2014-12-21
 */


  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack(){
    int i = 0;
    for (int j = 0; j < NUM_SUITS; ++j){
        for (int h = 7; h < NUM_RANKS; ++h){
            Card c(RANK_NAMES_BY_WEIGHT[h], SUIT_NAMES_BY_WEIGHT[j]);
            cards[i] = c;
            ++i;
        }
    }
    next = 0;
}

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input){
    std::string is = " of ";
    std::string rank;
    std::string suit;
    Card c;
    next = 0;
    while(pack_input >> rank >> is >> suit){
        Card c(rank, suit);
        cards[next] = c;
        ++next;
    }
    next = 0;
}

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
    return cards[next++];
}

  // EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
    cards[next];
}

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    std::array <Card, PACK_SIZE> Final;
    for (int j = 0; j < 7; j++){
        for(int i = 0; i < PACK_SIZE/2; ++i){
        Final[2 * i] = cards[i + PACK_SIZE/2];
        Final[2 * i + 1 ]=cards[i];
        }
        j++;
        if(j < 7){
            for(int h = 0; h < PACK_SIZE/2; ++h){
              cards[2 * h] = Final[h + PACK_SIZE/2];
              cards[2 * h + 1] = Final[h];
            }
        }
    }
    for(int f = 0; f < PACK_SIZE; f++){
        cards[f] = Final[f];
    }
    next = 0;
}
  // EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
    if (next == 24){
        return true;
    }
    return false;
}
