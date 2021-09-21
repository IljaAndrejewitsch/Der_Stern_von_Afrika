/**
*   \file	RobberState.hpp
*   \author Ilia Budnikov
*/

#ifndef ROBBERSTATE_HPP
#define ROBBERSTATE_HPP

#include "State.hpp"

// Topic: Inheritance
// Topic: Interface inheritance
// Topic: Abstraktionen
// other player has the diamond
class RobberState : public State {
public:
    // Topic: Best Practice 5
    // "single argument constructors should usually be explicit"
    explicit RobberState(Player * player);
    virtual ~RobberState();

    // s. State.hpp
    // for the most part uses DefaultState implementations,
    // but like a wrapper changes the corresponding behaviour
    virtual void go();
    virtual void makeTurn(uint steps);
    virtual void wasCaughtByHighwayman();
protected:
    Player * player_; // working with raw pointers
                      // because weak_ptr + enable_shared_from_this<Player>
                      // is meaningless overengineering in this program
};

#endif