/**
*   \file	RichMan.cpp
*   \author Ilia Budnikov
*/

#include "../include/RichMan.hpp"
#include "../include/State.hpp" // all the states use the Player class
#include "../include/DefaultState.hpp"
#include "../include/WithDiamondState.hpp"
#include "../include/RobberState.hpp"
#include "../include/RichManDefaultState.hpp"

// member initializer list
RichMan::RichMan(PascalString name, banknotesVec banknotes,
    int extraSteps, Spaces start)
    : Player(name, banknotes, start,
      std::make_shared<RichManDefaultState>(this),
      std::make_shared<WithDiamondState>(this),
      std::make_shared<RobberState>(this)),
      extraSteps_(extraSteps)
{
    typeName_ = PascalString("Reiche"); // not really costly
                                        // to initialize individually,
                                       // but saves us the trouble of
                                      // creating one more Player constructor
}

RichMan::~RichMan()
{
}

int RichMan::extraSteps() {
    return extraSteps_;
}

void RichMan::makeTurn(uint steps) {
    // delegation to the current state with extra steps
    currentState()->makeTurn(steps + extraSteps_);
}
