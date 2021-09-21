/**
*   \file   main.cpp
*   \author Ilia Budnikov
*/

#include "../include/Board.hpp"
#include <ctime>

int main(/*int argc, char** argv, char** envp*/) {
    // Initialize random seed with the value
    // representing the current time.
    // is used in rollDice() and shuffleSpaceWithAction().
    std::srand(std::time(0));

    play();

    // Topic: Best Practice 22
    // "in C++ you do not need to explicitly return from main"
    //return 0;
}
