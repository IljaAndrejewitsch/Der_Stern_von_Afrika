/**
*   \file	Sportsman.ñpp
*   \author Ilia Budnikov
*/

#include "../include/Sportsman.hpp"
#include "../include/State.hpp"

Sportsman::Sportsman(PascalString name, banknotesVec banknotes,
    int extraSteps, Spaces start)
    : Player(name, banknotes, start), extraSteps_(extraSteps)
{
    typeName_ = PascalString("Sportler"); // not really costly
                                        // to initialize individually,
                                       // but saves us the trouble of
                                      // creating one more Player constructor
}

Sportsman::~Sportsman()
{
}

int Sportsman::extraSteps() {
    return extraSteps_;
}

void Sportsman::makeTurn(uint steps) {
    // delegation to the current state with extra steps
    currentState()->makeTurn(steps + extraSteps_);
}
