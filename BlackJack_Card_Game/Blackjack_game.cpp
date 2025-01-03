#include "Players_and_Dealer.h"
#include "Blackjack_game.h"

BlackjackGame::BlackjackGame() : dealer(), player(100000, 312) {
    deck.resize(312);

    for (int i = 0; i < 312; i++)
        deck[i] = i % 13 + 1;
}

void BlackjackGame::ShuffleDeck() {
    for (int i = 0; i < deck.size(); i++)
        swap(deck[i], deck[rand() % deck.size()]);

}

int BlackjackGame::DrawCard() {
    for (int i = 0; i < deck.size(); i++) {
        if (deck[i] != -1) {
            int card = deck[i];
            deck[i] = -1;
            return card;
        }
    }
    return -1;
}

void BlackjackGame::PlayGame(int num_rounds) {
    ShuffleDeck();

    for (int round = 0; round < num_rounds; round++) {
        dealer = Dealer();
        player = CardCountingPlayer(player.GetBalance(), 312);

        for (int i = 0; i < 2; i++) {
            int player_card = DrawCard();
            player.AddCard(player_card);
            player.MarkCardDrawn(player_card);

            int dealer_card = DrawCard();
            dealer.AddCard(dealer_card);
        }

        cout << "Round " << round + 1 << endl;
        cout << "Dealer: ";
        dealer.PrintCards();
        cout << "Player: ";
        player.PrintCards();

        while (!player.IsBusted() && player.DecideHit()) {
            int card = DrawCard();

            player.AddCard(card);
            player.MarkCardDrawn(card);
            cout << "Player hits: ";
            player.PrintCards();
        }

        if (player.IsBusted()) {
            cout << "Player busted! Dealer wins." << endl << endl;
            continue;
        }

        while (!dealer.IsBusted() && dealer.DecideHit()) {
            int card = DrawCard();

            dealer.AddCard(card);
            cout << "Dealer hits: ";
            dealer.PrintCards();
        }

        if (dealer.IsBusted() || player.GetSum() > dealer.GetSum()) {
            cout << "Player wins!" << endl << endl;
            player.AdjustBalance(100);
        }
        else if (player.GetSum() == dealer.GetSum()) {
            cout << "It's a draw!" << endl << endl;
        }
        else {
            cout << "Dealer wins!" << endl << endl;
            player.AdjustBalance(-100);
        }
    }

    cout << "Final Balance: " << player.GetBalance() << endl;
}