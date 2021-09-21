/**
*   \file	Sailor.hpp
*   \author Ilia Budnikov
*/

#ifndef SAILOR_HPP
#define SAILOR_HPP

#include "Player.hpp"

// Topic: Inheritance
// Topic: Implementation inheritance,
// but can also use Player as the common type for subtyping
// Topic: Abstraktionen
// needs no own states, uses states of the default player
class Sailor : public Player {
public:
    Sailor(PascalString name, banknotesVec banknotes, Spaces start);
    virtual ~Sailor();

    // Topic: spaete Bindung, overwriting
    virtual void goSailing(Spaces toGo);
};

#endif
