#include "Players_and_Dealer.h"
#include "Blackjack_game.h"

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    BlackjackGame game;
    game.PlayGame(10);

    return 0;
}