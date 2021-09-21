/**
*   \file	RichManDefaultState.hpp
*   \author Ilia Budnikov
*/

#ifndef RICHMANDEFAULTSTATE_HPP
#define RICHMANDEFAULTSTATE_HPP

#include "DefaultState.hpp"
#include "RichMan.hpp"

// Topic: Inheritance
// Topic: Implementation inheritance
// Topic: Abstraktionen
// DefaultState of a player of the type RichMan
class RichManDefaultState : public DefaultState {
public:
    // Topic: Best Practice 5
    // "single argument constructors should usually be explicit"
    explicit RichManDefaultState(Player * player);
    virtual ~RichManDefaultState();

    // Topic: spaete Bindung, overwriting
    virtual void makeTurn(uint steps);
};

#endif