// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <cassert>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "Pack.h"
#include "Card.h"
#include "Player.h"

using namespace std;

// Game ADT representing a single hand
class Game {
public:
    // REQUIRES the args are sa required
    // EFFECTS set up packs, players, and the scores
    Game(int argc, char * argv[], istream & pack_input) {
        // set shuffle
        shuffle = !(strcmp(argv[2], "shuffle"));
        
        // set players
        for (int i = 0; i < 4; i++) {
            players[i] = Player_factory(argv[4 + 2 * i], argv[5 + 2 * i]);
        }
        
        // set pack
        pack = new Pack(pack_input);
        
        // set scores
        team_1_score = 0;
        team_2_score = 0;
        target_score = atoi(argv[3]);
        
        hand_played = 0;
    }
    
    // EFFECTS Get hands played
    int get_hand_played() const {
        return hand_played;
    }
    
    // EFFECTS Determine if game is over
    bool is_over() const{
        return (team_1_score >= target_score) ||
        (team_2_score >= target_score);
    }
    
    // EFFECTS Get the name of current dealer
    string get_dealer_name() const {
        return players[get_dealer_index()] -> get_name();
    }
    
    // EFFECT Print the winner team
    void print_winner(ostream & game_out) const {
        if (is_over()) {
            if (team_1_score > team_2_score) {
                game_out << *players[0] << " and " << *players[2] << " win!" << endl;
            }
            else {
                game_out << *players[1] << " and " << *players[3] << " win!" << endl;
            }
        }
    }
    
    // MODIFIES game_out
    // EFFECTS Play one single hand
    void play_single_hand(ostream & game_out) {
        make_shuffle();
        deal_cards();
        Card upcard = pack -> deal_one();
        
        // announce the hand
        game_out << "Hand " << get_hand_played() << endl;
        game_out << get_dealer_name() << " deals" << endl;
        game_out << upcard << " turned up" << endl;
        
        // make trump
        int order_up_player_index = -1;
        string order_up_suit = "";
        if (test_trump(upcard, 1, order_up_suit, game_out) != -1) {
            order_up_player_index = make_trump(upcard, 1, order_up_suit, game_out);
             players[get_dealer_index()] -> add_and_discard(upcard);
        }
        else {
            make_trump(upcard, 1, order_up_suit, game_out);
            order_up_player_index = make_trump(upcard, 2, order_up_suit, game_out);
        }
        
        game_out << endl;
        
        // trick taking
        int round_winners[5];
        // 5 rounds of trick
        int pre_win = (get_dealer_index() + 1) % 4;
        for (int i = 0; i < 5; i++) {
            round_winners[i] = play_trick_single_round(order_up_suit, pre_win, game_out);
            game_out << endl;
            pre_win = round_winners[i];
        }
        
        update_scores(round_winners, 5, order_up_player_index, game_out);
        print_scores(game_out);
        game_out << endl;
        hand_played++;
    
    }
    
private:
    Player * players[4];
    Pack * pack;
    bool shuffle;
    int hand_played;
    int team_1_score;
    int team_2_score;
    int target_score;
    
    // EFFECTS Get the dealer's index
    int get_dealer_index() const {
        return hand_played % 4;
    }
    
    // EFFECTS Make shuffle and reset
    void make_shuffle() {
        if (shuffle) {
            pack -> shuffle();
        }
        
        pack -> reset();
    }
    
    // EFEFCTS Deal cards
    void deal_cards() {
        // 3-2-3-2 round
        for (int i = 1; i < 5; i++) {
            // deal three times
            if (i % 2 == 1) {
                for (int j = 0; j < 3; j++) {
                    players[(i + get_dealer_index()) % 4] -> add_card(pack -> deal_one());
                }
            }
            else {
                for (int j = 0; j < 2; j++) {
                    players[(i + get_dealer_index()) % 4] -> add_card(pack -> deal_one());
                }
            }
        }
        
        // 2-3-2-3 round
        for (int i = 1; i < 5; i++) {
            // deal three times
            if (i % 2 == 1) {
                for (int j = 0; j < 2; j++) {
                    players[(i + get_dealer_index()) % 4] -> add_card(pack -> deal_one());
                }
            }
            else {
                for (int j = 0; j < 3; j++) {
                    players[(i + get_dealer_index()) % 4] -> add_card(pack -> deal_one());
                }
            }
        }
    }
    int test_trump(const Card & upcard, int round, string & order_up_suit, ostream & game_out) const {
        if (round == 1) {
            // starting from eldest hand
            for (int i = 1; i < 5; i++) {
                int player_index = (get_dealer_index() + i) % 4;
                // ordered up
                if (players[player_index] -> make_trump(upcard, player_index == get_dealer_index(), 1, order_up_suit)) {
                    return player_index;
                }
            }
        }
        // round 2
        else {
            for (int i = 1; i < 5; i++) {
                int player_index = (get_dealer_index() + i) % 4;
                if (players[player_index] -> make_trump(upcard, player_index == get_dealer_index(), 2, order_up_suit)) {
                    return player_index;
                }
            }
        }
        return -1;
    }
    
        
    int make_trump(const Card & upcard, int round, string & order_up_suit, ostream & game_out) const {
        // round 1
        if (round == 1) {
            // starting from eldest hand
            for (int i = 1; i < 5; i++) {
                int player_index = (get_dealer_index() + i) % 4;
                // ordered up
                if (players[player_index] -> make_trump(upcard, player_index == get_dealer_index(), 1, order_up_suit)) {
                    // print decision of the player
                    game_out << *players[player_index] << " orders up " << order_up_suit << endl;
                    return player_index;
                }
                else {
                    game_out << *players[player_index] << " passes" << endl;
                }
            }
        }
        // round 2
        else {
            for (int i = 1; i < 5; i++) {
                int player_index = (get_dealer_index() + i) % 4;
                if (players[player_index] -> make_trump(upcard, player_index == get_dealer_index(), 2, order_up_suit)) {
                    game_out << *players[player_index] << " orders up " << order_up_suit << endl;
                    return player_index;
                }
                else {
                    game_out << *players[player_index] << " passes" << endl;
                }
            }
        }
        return -1;
    }
    
    // REQUIRES trump is a valid suit, start index is within 0 to 3
    // EFFECT Play a single round of trick
    // RETURNS the round winner index
    int play_trick_single_round(string & trump, int start_index, ostream & game_out) {
        int win_index = 0;
        Card win_card;
        Card led_card;
        for (int i = 0; i < 4; i++) {
            int player_index = (i + start_index) % 4;
            // leader
            if (i == 0) {
                win_card = players[player_index] -> lead_card(trump);
                led_card = win_card;
                // print
                cout << led_card << " led by " << *players[player_index] << endl;
                win_index = player_index;
            }
            // non-leader
            else {
                Card played = players[player_index] -> play_card(led_card, trump);
                if (Card_less(win_card, played, led_card, trump)) {
                    win_index = player_index;
                    win_card = played;
                }
                // print
                cout << played << " played by " << *players[player_index] << endl;
            }
        }
        cout << *players[win_index] << " takes the trick" << endl;
        return win_index;
    }
    
    
    // EFFECTS Update team scores based on trick winners
    void update_scores(int * winners, int size, int order_up_index, ostream & game_out) {
        int team1_wins = 0;
        int team2_wins = 0;
        for (int i = 0; i < size; i++) {
            if (winners[i] == 0 || winners[i] == 2) {
                team1_wins += 1;
            }
            else {
                team2_wins += 1;
            }
        }
        
        // team 1 wins
        if (team1_wins > team2_wins) {
            game_out << *players[0] << " and " << *players[2] << " win the hand" << endl;
            // team 1 ordered up
            if (order_up_index == 0 || order_up_index == 2) {
                // march case
                if (team1_wins == 5) {
                    game_out << "march!" << endl;
                    team_1_score += 2;
                }
                // other cases
                else {
                    team_1_score += 1;
                }
            }
            // team 1 did not order up (euchre)
            else {
                team_1_score += 2;
                game_out << "euchred!" << endl;
            }
        }
        // team 2 wins
        else {
            game_out << *players[1] << " and " << *players[3] << " win the hand" << endl;
            // team 2 ordered up
            if (order_up_index == 1 || order_up_index == 3) {
                // march case
                if (team2_wins == 5) {
                    game_out << "matched!" << endl;
                    team_2_score += 2;
                }
                // other cases
                else {
                    team_2_score += 1;
                }
            }
            // team 2 did not order up (euchre)
            else {
                team_2_score += 2;
                game_out << "euchred!" << endl;
            }
        }
    }
    
    // EFFECTS Print current team scores
    void print_scores(ostream & game_out) const {
        game_out << * players[0] << " and " << * players[2] <<
        " have " << team_1_score << " points" << endl;
        game_out << * players[1] << " and " << * players[3] <<
        " have " << team_2_score << " points" << endl;
    }
};

// helper function stubs
bool check_args(int argc, char * argv[]);

int main(int argc, char * argv[]) {
    if (!check_args(argc, argv)) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return -1;
    }
    
    // open input file
    ifstream pack_in(argv[1]);
    if (!pack_in.is_open()) {
        cout << "Error opening " << argv[1] << endl;
        return -1;
    }
    
    // play game
    Game new_game(argc, argv, pack_in);
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    while(!new_game.is_over()) {
        new_game.play_single_hand(cout);
    }
    new_game.print_winner(cout);
    pack_in.close();
    return 0;
}




bool check_args(int argc, char * argv[]) {
    if (argc != 12) {
        return false;
        
    }

    const char * shuffle_type_1 = "shuffle";
    const char * shuffle_type_2 = "noshuffle";
    const char * player_type_1 = "Human";
    const char * player_type_2 = "Simple";
    
    if (strcmp(argv[2], shuffle_type_1) != 0 &&
        strcmp(argv[2], shuffle_type_2) != 0) {
        cout << argv[2] << endl;

        return false;
    }

    if (atoi(argv[3]) < 1 || atoi(argv[3]) > 100) {
        return false;
    }
    
    

    for (int i = 5; i < 12; i += 2) {
        if (strcmp(argv[i], player_type_1) != 0 &&
            strcmp(argv[i], player_type_2) != 0) {
            return false;
        }
    }
    
    return true;
}
