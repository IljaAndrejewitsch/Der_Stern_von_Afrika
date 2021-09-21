/**
*   \file	PlayerFactory.hpp
*   \author Ilia Budnikov
*/

#ifndef PLAYERFACTORY_HPP
#define PLAYERFACTORY_HPP

#include "Player.hpp"
#include "RichMan.hpp"
#include "Sailor.hpp"
#include "Sportsman.hpp"
#include "Bank.hpp"
#include "State.hpp"
class DefaultState;
class WithDiamondState;
class RobberState;
class SportsmanDefaultState;
class RichManDefaultState;
#include <map>
#include <memory>

enum class Types {
    DEFAULT   = 0,
    SAILOR    = 1,
    SPORTSMAN = 2,
    RICHMAN   = 3
};

// Topic: Design Pattern Factory method
class PlayerFactory {
public:
    PlayerFactory();
    virtual ~PlayerFactory();
    // creates a player with a certain type
    static std::shared_ptr<Player> createType(PascalString name, Spaces start, Types type);

    // Topic: wichtige Container der C++-Standardbibliothek, map
    // all player types with corresponding descriptions
    static std::map<Types, PascalString> typesDescriptions;
};

#endif