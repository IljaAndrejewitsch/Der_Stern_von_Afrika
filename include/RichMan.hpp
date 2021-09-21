/**
*   \file	RichMan.hpp
*   \author Ilia Budnikov
*/

#ifndef RICHMAN_HPP
#define RICHMAN_HPP

#include "Player.hpp"

// Topic: Inheritance
// Topic: Implementation inheritance,
// but can also use Player as the common type for subtyping
// Topic: Abstraktionen
class RichMan : public Player {
public:
    RichMan(PascalString name, banknotesVec banknotes,
        int extraSteps, Spaces start);
    virtual ~RichMan();

    int extraSteps();

    // Topic: spaete Bindung, overwriting
    virtual void makeTurn(uint steps);
protected:
    // Steps, that a player can take extra, if he/she is of a certain type.
    // The value can be negative, for the current type it's -1 (s. PlayerFactory).
    int extraSteps_;
};

#endif