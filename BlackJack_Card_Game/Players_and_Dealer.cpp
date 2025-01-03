#include "Players_and_Dealer.h"

// 1. Non-CardCounting Player

// Set Initial Balance
Player::Player(int initial_balance) : sum(0), is_busted(false), balance(initial_balance) {}

// When a player receives new card, AddCard() is called
void Player::AddCard(int card) {
    cards.push_back(card);

    UpdateSum();
}

// Calculate the sum of card
void Player::UpdateSum() {
    sum = 0;
    int ace_count = 0;

    for (int card : cards) {
        if (card == 1)
            ace_count++;

        sum += (card > 10) ? 10 : card;
    }
    while (ace_count > 0 && sum + 10 <= 21) {
        sum += 10;
        ace_count--;
    }

    is_busted = (sum > 21);
}

// Current card sum
int Player::GetSum() const { return sum; }

// if sum > 21 -> Bust
bool Player::IsBusted() const { return is_busted; }

// Print all cards which the player has
void Player::PrintCards() const {
    cout << "Cards: ";
    for (int card : cards) cout << card << " ";
    cout << "(Sum: " << sum << ")" << endl;
}

// Adjust the balance which the player has
void Player::AdjustBalance(int amount) {
    balance += amount;
}

// return balance
int Player::GetBalance() const {
    return balance;
}

// 2. Dealer
Dealer::Dealer() : Player() {}

// Decide whether the dealer hits
// sum >= 17 -> Stand | sum < 17 -> Hit
bool Dealer::DecideHit() {
    return sum < 17;
}

// 3. CardCountingPlayer
CardCountingPlayer::CardCountingPlayer(int initial_balance, int total_cards)
    : Player(initial_balance), total_cards(total_cards), card_drawn(total_cards, false) {}

// Indicate card usage
void CardCountingPlayer::MarkCardDrawn(int index) {
    card_drawn[index] = true;
}

// Calculate Probability
double CardCountingPlayer::Probability(int target_value) {
    int remaining_target = 0;
    int total_remaining = 0;

    for (int i = 0; i < total_cards; i++) {
        if (!card_drawn[i]) {
            total_remaining++;

            if ((i % 13 + 1) == target_value)
                remaining_target++;
        }
    }
    return static_cast<double>(remaining_target) / total_remaining;
}

// sum >= 17 -> Stand
// sum < 17 && Probability > 0.2 -> Hit
bool CardCountingPlayer::DecideHit() {
    if (sum >= 17)
        return false;

    return Probability(10) > 0.2;
}