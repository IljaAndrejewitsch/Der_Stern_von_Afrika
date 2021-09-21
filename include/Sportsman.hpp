/**
*   \file	Sportsman.hpp
*   \author Ilia Budnikov
*/

#ifndef SPORTSMAN_HPP
#define SPORTSMAN_HPP

#include "Player.hpp"

// Topic: Inheritance
// Topic: Implementation inheritance,
// but can also use Player as the common type for subtyping
// Topic: Abstraktionen
class Sportsman : public  Player {
public:
    Sportsman(PascalString name, banknotesVec banknotes,
        int extraSteps, Spaces start);
    virtual ~Sportsman();

    int extraSteps();

    // Topic: spaete Bindung, overwriting
    virtual void makeTurn(uint steps);
protected:
    // Steps, that a player can take extra, if he/she is of a certain type.
    // The value for the current type is +1 (s. PlayerFactory).
    int extraSteps_;
};

#endif