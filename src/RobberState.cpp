/**
*   \file	RobberState.cpp
*   \author Ilia Budnikov
*/

#include "../include/RobberState.hpp"
#include "../include/Board.hpp"

RobberState::RobberState(Player * player)
    : player_(player)
{
}

RobberState::~RobberState()
{
}

void RobberState::go() {
    // doing everything as the default state, but...
    player_->defaultState()->go();

    //...  if the caught player's state is "with diamond", then steal the diamond
    // Topic optional: typeid
    auto currentState = player_->whoWithMeOnSpace()->currentState().get();
    auto withDiamondState = player_->withDiamondState().get();
    if (typeid(*(currentState)) ==
        typeid(*(withDiamondState))) {
        println("\n! ===================");
        println("\nDu hast den Diamanttraeger eingeholt!");
        std::this_thread::sleep_for(std::chrono::seconds(4));
        player_->takeDiamond();
        println("\n=====================");
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void RobberState::makeTurn(uint steps) {
    // Topic: dynamische Bindung
    // doing everything as the default state, only one step more
    player_->defaultState()->makeTurn(steps + 1); // it can DefaultState class
                                                  // or its subclasses
}

void RobberState::wasCaughtByHighwayman() {
    println("Zum Glueck bist du auch kein guter Kerl.");
    println("Ihr habt einen Haendedruck getauscht und seid weitergegangen.");
}
