/**
*   \file	WithDiamondState.cpp
*   \author Ilia Budnikov
*/

#include "../include/WithDiamondState.hpp"
#include "../include/Board.hpp"

WithDiamondState::WithDiamondState(Player * player)
    : player_(player)
{
}

WithDiamondState::~WithDiamondState()
{
}


void WithDiamondState::go() {
    // doing everything as the default state, but...
    player_->defaultState()->go();

    // ...(Tanger or Kairo) and with the diamond? => winner
    if ((player_->currentSpace() == Spaces::Tanger) ||
        (player_->currentSpace() == Spaces::Kairo)) {
        player_->won(true);
    }
    else if (player_->checkIfAnotherOnSpace()) {
        // The situation is improbable, but it should be handled.
        // A player with a diamond on a personal whim
        // went to a space with a robber player.
        println("\n! ===================");
        println("\nDu bist auf einen anderen Spieler-Raeuber gestossen!");
        std::this_thread::sleep_for(std::chrono::seconds(4));
        std::shared_ptr<Player> newOwner = player_->whoWithMeOnSpace();
        newOwner->takeDiamond();
        println("\n=====================");
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void WithDiamondState::makeTurn(uint steps) {
    // Topic: dynamische Bindung
    // doing everything as the default state
    player_->defaultState()->makeTurn(steps); // it can DefaultState class
                                              // or the subclasses
}

void WithDiamondState::wasCaughtByHighwayman() {
    // doing everything as the default state, but...
    player_->defaultState()->wasCaughtByHighwayman();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    // ...the diamond is taken away
    println("\n...Aber nicht nur.");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    println("\nBei dir fehlt der Diamant!");
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // diamond to Kapstadt
    boardPtr board = Board::board();
    board->takeDiamondToKapstadt();
    println("\nEs geht ein Geruecht um, dass dieser in Kapstadt bereits verkauft wurde...");
}
