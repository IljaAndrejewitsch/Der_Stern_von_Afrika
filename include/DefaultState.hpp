/**
*   \file   DefaultState.hpp
*   \author Ilia Budnikov
*/


#ifndef DEFAULTSTATE_HPP
#define DEFAULTSTATE_HPP

#include "State.hpp"

//  Default state of a player (no one has the diamond).
//  It's better to inherit from this class and just overwrite methods if necessary.
//  Can be used as a some sort of adapter to use the interface State easily and properly
// Topic: Abstraction
// Topic: Inheritance
// Topic: Interface inheritance
// Topic: Abstraktionen
class DefaultState : public State {
public:
    // Topic: Best Practice 5
    // "single argument constructors should usually be explicit"
    explicit DefaultState(Player * player);
    virtual ~DefaultState();

    //  Helper for go().
    //  Returns all listed neighbors to remember the listing sequence
    //  and the chosen direction (space) from the list
    // (-1 instead of the space if the player has chosen to give up).
    // Topic: wichtige Container der C++-Standardbibliothek, pair
    std::pair<neighborsVec, int> chooseOption();
    // Topic: subtyping polymorhism
    // s. State.hpp
    virtual void go();
    virtual void makeTurn(uint steps);
    virtual void wasCaughtByHighwayman();
protected:
    Player * player_; // working with raw pointers
                      // because weak_ptr + enable_shared_from_this<Player>
                      // is meaningless overengineering in this program
};

#endif
