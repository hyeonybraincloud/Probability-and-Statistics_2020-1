#ifndef __PLAYERS_AND_DEALER_H
#define __PLAYERS_AND_DEALER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

class Player {
protected:
    vector<int> cards;
    int sum;
    bool is_busted;
    int balance;

public:
    Player(int initial_balance = 0);

    void AddCard(int card);
    void UpdateSum();
    int GetSum() const;
    bool IsBusted() const;
    void PrintCards() const;
    void AdjustBalance(int amount);
    int GetBalance() const;

    virtual bool DecideHit() = 0;
};

class Dealer : public Player {
public:
    Dealer();
    bool DecideHit() override;
};

class CardCountingPlayer : public Player {
private:
    vector<bool> card_drawn;
    int total_cards;

public:
    CardCountingPlayer(int initial_balance, int total_cards);
    void MarkCardDrawn(int index);
    double Probability(int target_value);
    bool DecideHit() override;
};

#endif