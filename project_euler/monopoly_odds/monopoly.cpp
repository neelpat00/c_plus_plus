#include <algorithm>
#include <random>
#include <vector>
#include <iostream>
#include <ctime>

void print_vector(const std::vector<int>& vec) {
    for (int val : vec) {
        std::cout << val << " ";
    }
}

int roll_dice(int side = 6) 
{

    return std::rand() % side + 1;
}


int check_cards(int new_position, 
    std::vector<int>& cc_deck, int& cc_index,
    std::vector<int>& ch_deck, int& ch_index) 
{
    // Go to jail
    if (new_position == 30) 
    {
        new_position = 10; // Go to jail
    }

    // Community Chest
    if (new_position == 2 || new_position == 17 || new_position == 33) 
    {
        int cc_card = cc_deck[cc_index]; // Pick up the first car
        cc_index = (cc_index + 1) % 16; // Move to the next card

        if (cc_card == 0) { new_position = 0; }       // GO TO ADVANCE
        else if (cc_card == 1) { new_position = 10; } // GO TO JAIL
        // Cards 2-15 do nothing
    }

    // Chance
    if (new_position == 7 || new_position == 22 || new_position == 36) 
    {
        int ch_card = ch_deck[ch_index];
        ch_index = (ch_index + 1) % 16;

        if (ch_card == 0) { new_position = 0; }       // GO TO ADVANCE
        else if (ch_card == 1) { new_position = 10; } // GO TO JAIL
        else if (ch_card == 2) { new_position = 11; } // GO C1
        else if (ch_card == 3) { new_position = 24; } // GO E3
        else if (ch_card == 4) { new_position = 39; } // GO H2
        else if (ch_card == 5) { new_position = 5; }  // GO R1
        else if (ch_card == 6 || ch_card == 7) 
        {
            if (new_position <= 5 || new_position > 35) { new_position = 5;}
            else if (new_position <= 15 && new_position > 5) { new_position = 15;}
            else if (new_position <= 25 && new_position > 15) { new_position = 25;}
            else if (new_position <= 35 && new_position > 25) { new_position = 35;}
        }
        else if (ch_card == 8) 
        {
            // Utilities at 12 and 28
            if (new_position < 12 || new_position > 28) {new_position = 12;}
            else {new_position = 28;}
        }
        else if (ch_card == 9) 
        {
            // Go back 3 squares
            new_position = (new_position - 3 + 40) % 40;  // The +40 ensures positive
            new_position = check_cards(new_position, cc_deck, cc_index, ch_deck, ch_index);
        }
    }

    return new_position;
}

int board_position(int position, int die1, int die2, 
                   std::vector<int>& cc_deck, int& cc_index,
                   std::vector<int>& ch_deck, int& ch_index) 
{
    int new_position = (position + die1 + die2) % 40;

    // check for special cards

    new_position  = check_cards(new_position, cc_deck, cc_index, ch_deck, ch_index);

    return new_position;
}



void shuffle_deck(std::vector<int>& deck) 
{
    // Need a random number generator for shuffle
    std::random_device rd;
    std::mt19937 g(rd());  // Mersenne Twister random generator

    std::shuffle(deck.begin(), deck.end(), g);
}

int main()
{
    std::srand(std::time(0));

    // Need to shuffle and initiliase the chance and community chest cards
    std::vector<int> cc_deck = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::vector<int> ch_deck = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    
    shuffle_deck(cc_deck);
    shuffle_deck(ch_deck);

    int cc_index = 0;
    int ch_index = 0;

    // Track visits
    std::vector<int> visits(40, 0);  // 40 squares, all start at 0
    
    int position = 0;
    int doubles_count = 0;
    int num_rolls = 1000000; 
    
    for (int i = 0; i < num_rolls; i++) 
    {
        int die1 = roll_dice(4);  // Don't forget the 4!
        int die2 = roll_dice(4);

        // Check for doubles
        if (die1 == die2) {
            doubles_count++;
            
            if (doubles_count == 3) {
                position = 10;  // Go to jail
                doubles_count = 0;  // Reset!
            } else {
                // Normal move with board_position
                position = board_position(position, die1, die2, cc_deck, cc_index, ch_deck, ch_index);
            }
        } else {
            doubles_count = 0;  // Reset when not doubles
            position = board_position(position, die1, die2, cc_deck, cc_index, ch_deck, ch_index);
        }
        
        visits[position]++;  // Count visit AFTER all moves
    }

    std::vector<std::pair<int, int>> square_visits;
    for (int i = 0; i < 40; i++) {
        square_visits.push_back({i, visits[i]});
    }

    std::sort(
        square_visits.begin(), 
        square_visits.end(), 
        [](const std::pair<int,int>& a, const std::pair<int,int>& b) {
            return a.second > b.second;
        }
    );

    int first = square_visits[0].first;
    int second = square_visits[1].first;
    int third = square_visits[2].first;

    std::cout << "Top 3 squares: " << first << ", " << second << ", " << third << std::endl;

    return 0;
}
