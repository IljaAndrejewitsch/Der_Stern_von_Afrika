#ifndef STATE_HPP
#define STATE_HPP

#include "Player.hpp" // every (reasonable) state subclass uses members of a player
#include <memory> // player should be a shared pointer,
    // 'cause the player is passed via shared_ptr to every state-constructor

typedef unsigned int uint;

// Topic: Design Pattern State
// Interface State.
// All the direct subclasses should be added as members to the Player class.
class State {
public:
    // for more details s. Player.hpp

    // pure vitual methods
    // going process
    virtual void go() = 0;
    // with this method the number of steps in derived classes can be changed
    virtual void makeTurn(uint steps) = 0;

    // special actions
    virtual void wasCaughtByHighwayman() = 0;
};

#endif