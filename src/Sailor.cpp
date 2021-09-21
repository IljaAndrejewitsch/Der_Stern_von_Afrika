/**
*   \file	Sailor.cpp
*   \author Ilia Budnikov
*/

#include "../include/Sailor.hpp"

Sailor::Sailor(PascalString name, banknotesVec banknotes, Spaces start)
    : Player(name, banknotes, start) // base initializer_list
{
    typeName_ = PascalString("Seemann"); // not really costly
                                        // to initialize individually,
                                       // but saves us the trouble of
                                      // creating one more Player constructor
}

Sailor::~Sailor()
{
}

void Sailor::goSailing(Spaces toGo) {
    // The same for a sailor as just walking.
    // goOnFoot() from the Player class delegates to a current state.
    goOnFoot(toGo);
}
