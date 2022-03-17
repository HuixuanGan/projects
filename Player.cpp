// Project UID 1d9f47bfc76643019cfbf037641defe1
//
//  Simple_player.cpp
//  p3-euchre
//
//  Created by Keyi Hua on 2/12/22.
//

#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Card.h"
#include "Player.h"

class HumanPlayer : public Player{
public:
    HumanPlayer (const std::string &name_in):
        name(name_in){
    }
    const std::string & get_name () const override{
        return name;
    }
    void add_card(const Card &c) override{
        if (MAX_HAND_SIZE>=hand.size()){
            hand.push_back(c);
        }
    }
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const override{
        for (int i = 0; i < static_cast<int>(hand.size()); i += 1) {
            std::cout << "Human player " << get_name () << "'s hand: [" << i << "] ";
            std::cout << hand[i].get_rank() << " of ";
            std::cout << hand[i].get_suit() << std::endl;
          }
        assert (round == 1||round == 2);
        std::cout <<"Human player "<< get_name();
        std::cout << ", please enter a suit, or \"pass\""<<":"<<std::endl;
            std::string input;
            std::string pass = "pass";
            std::cin >> input;
            if (input == pass){
                return false;
            }
            else if (round == 1){
                order_up_suit = upcard.get_suit();
                return true;
            }
            else if (round == 2){
                if (input != upcard.get_suit()){
                    order_up_suit = input;
                    return true;
                }
            }
        return false;
    }
    void add_and_discard (const Card &upcard) override {
        std::sort(hand.begin(), hand.end());
        for (int i = 0; i < static_cast<int>(hand.size()); i += 1) {
            std::cout << "Human player " << get_name () << "'s hand: [" << i << "] ";
            std::cout << hand[i].get_rank() << " of ";
            std::cout << hand[i].get_suit() << std::endl;
          }
        if(hand.size()>=1){
            std::cout << "Human player" << get_name ();
            std::cout  << ", please select a card to discard:" << std::endl;
            int index;
            std::cin >> index;
            if(index == -1){
                std::cout<<"Discard upcard: [-1]"<<std::endl;
            }
            else{
            hand.push_back(upcard);
            hand.erase(hand.begin() + index);
            }
            std::sort(hand.begin(), hand.end());
        }
    }
    Card lead_card(const std::string &trump)override{
        std::sort(hand.begin(), hand.end());
        for (int i = 0; i < static_cast<int>(hand.size()); i += 1) {
            std::cout << "Human player " << get_name ();
            std::cout << "'s hand: [" << i << "] ";
            std::cout << hand[i].get_rank() << " of ";
            std::cout << hand[i].get_suit() << std::endl;
          }
        std::cout<<"Human player "<< get_name () << ", please select a card:" <<std::endl;
        int index;
        std::cin >> index;
        Card played = hand[index];
        hand.erase(hand.begin() + index);
        return played;
    }
    Card play_card(const Card &led_card, const std::string &trump)override{
        std::sort(hand.begin(), hand.end());
        for (int i = 0; i < static_cast<int>(hand.size()); i += 1) {
            std::cout << "Human player " << get_name () << "'s hand: [" << i << "] ";
            std::cout << hand[i].get_rank() << " of ";
            std::cout << hand[i].get_suit() << std::endl;
          }
        std::cout<<"Human player "<< get_name () << ", please select a card:" <<std::endl;
        int index;
        std::cin >> index;
        Card played = hand[index];
        hand.erase(hand.begin() + index);
        return played;
    }
private:
    std::string name;
    std::vector<Card> hand;
    std::vector<Card> editted_cards;
    
    void sort_hand_card_with_trump(const std::string trump_suit) {
        std::sort(hand.begin(),
                  hand.end(),
                  [trump_suit](Card a, Card b) {
            return Card_less(a, b, trump_suit);
        });
    }
    
    // helper function to sort hand cards
    // considering both led card and trump suit
    void sort_hand_card_with_trump_led(const std::string trump_suit,
                                       const Card &led_card) {
        std::sort(hand.begin(), hand.end(),
                  [led_card, trump_suit](Card a, Card b) {
            return Card_less(a, b, led_card, trump_suit);
        });
    }
};




class SimplePlayer : public Player {
 public:
    
    SimplePlayer(const std::string &name) {
        this -> name = name;
    }
    
    
    //EFFECTS returns player's name
    const std::string & get_name() const override{
        return this -> name;
    }
       
    
    
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        assert(hand_cards.size() <= Player :: MAX_HAND_SIZE);
        
        hand_cards.push_back(c);
    }
     
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                        int round, std::string &order_up_suit) const override {
        assert(round == 1 || round == 2);
        
        // round 1
        if (round == 1) {
            std::string suit = upcard.get_suit();
            int num_face_trump = get_num_face_cards_of_suit(suit);
            // check if have two or more trump face cards
            if (num_face_trump >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            return false;
        }
        else {
            int num_same_color_num = get_num_face_cards_of_suit(Suit_next(upcard.get_suit()));
            // check if have one or more face cards with the next suit
            // or if it's dealer
            // next suit: suit with the same color as the suit of the up card
            if (num_same_color_num >= 1 || is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            return false;
        }
    }
    
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        assert(hand_cards.size() >= 1);
        // add card to hand cards
        hand_cards.push_back(upcard);
        
        // sort the hand cards, trump suit is considered
        sort_hand_card_with_trump(upcard.get_suit());
        
        // discard the lowest-valued card
        hand_cards.erase(hand_cards.begin());
    }
    
    
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) override {
        assert(hand_cards.size() >= 1);
        
        sort_hand_card_with_trump(trump);
        for (int i = int(hand_cards.size()) - 1; i >= 0; i--) {
            // check if there is non-trump card
            if (!hand_cards.at(i).is_trump(trump)) {
                Card res = hand_cards.at(i);
                hand_cards.erase(hand_cards.begin() + i);
                return res;
            }
        }
        // if no non-trump card, return the highest trump card
        Card res = *(hand_cards.end() - 1);
        hand_cards.pop_back();
        return res;
    }
    
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    
    // If a Simple Player can follow suit, they play the highest card that
    // follows suit. Otherwise, they play the lowest card in their hand.
    //  The card is removed from the player's hand.
    
    Card play_card(const Card &led_card, const std::string &trump) override {
        assert(hand_cards.size() >= 1);
        // sort card based on led suit & trump
        sort_hand_card_with_trump_led(trump, led_card);
        
        // play the highest card that follows suit
        for (int i = int(hand_cards.size()) - 1; i >= 0; i--) {
            if (hand_cards.at(i).get_suit(trump) == led_card.get_suit(trump)) {
                Card res = hand_cards.at(i);
                hand_cards.erase(hand_cards.begin() + i);
                return res;
            }
        }
        
        // otherwise, play lowest card
        Card res = *hand_cards.begin();
        hand_cards.erase(hand_cards.begin());
        return res;
    }
    
 private:
    std::string name;
    std::vector<Card> hand_cards;
    
    // helper function
    // get number of face cards with the specified suit
    const int get_num_face_cards_of_suit(const std::string suit) const {
        int count = 0;
        for (int i = 0; i < static_cast<int>(hand_cards.size()); i++) {
            if (hand_cards.at(i).is_trump(suit) && hand_cards.at(i).is_face()) {
                count++;
            }
        }
        return count;
    }
    
    // helper function to sort hand cards (only considering trump)
    void sort_hand_card_with_trump(const std::string trump_suit) {
        std::sort(hand_cards.begin(),
                  hand_cards.end(),
                  [trump_suit](Card a, Card b) {
            return Card_less(a, b, trump_suit);
        });
    }
    
    // helper function to sort hand cards
    // considering both led card and trump suit
    void sort_hand_card_with_trump_led(const std::string trump_suit,
                                       const Card &led_card) {
        std::sort(hand_cards.begin(), hand_cards.end(),
                         [led_card, trump_suit](Card a, Card b) {
            return Card_less(a, b, led_card, trump_suit);
        });
    }
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
    // check the value of strategy and return
      // the corresponding player type.
      if (strategy == "Simple") {
        // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
      }
      // Repeat for Human Player
      else if (strategy == "Human") {
          return new HumanPlayer(name);
          
      }
      // Invalid strategy if we get here
      assert(false);
      return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}

