/**
*   \file	RichManDefaultState.cpp
*   \author Ilia Budnikov
*/

#include "../include/RichManDefaultState.hpp"

// Topic: Best Practice 6
// "initialize the state of the object properly"
RichManDefaultState::RichManDefaultState(Player * player)
    : DefaultState(player) // base initializer_list
{
}

RichManDefaultState::~RichManDefaultState()
{
}

void RichManDefaultState::makeTurn(uint steps) {
    // the player makes as many moves as the dice obligates
    // + his extraSteps = -1
    if (steps > 0) { // if can go
        // Topic: statische Bindung
        // durch Vollqualifizierung eines Methodennames
        DefaultState::makeTurn(steps);
    }
    else {
        println("\nObwohl du eine 1 gewuerfelt hast, bringt dich die \"-1 Schritt\"-Regel dazu,\ndass du bleibst, wo du bist.");
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}
