#ifndef __BLACKJACK_H
#define __BLACKJACK_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

class BlackjackGame {
private:
    Dealer dealer;
    CardCountingPlayer player;
    vector<int> deck;

    void ShuffleDeck();
    int DrawCard();

public:
    BlackjackGame();
    void PlayGame(int num_rounds);
};

#endif