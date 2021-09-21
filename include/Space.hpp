/**
*   \file	Space.hpp
*   \author Ilia Budnikov
*/

#ifndef POINT_HPP
#define POINT_HPP

#include "Position.hpp"
#include "PascalString.hpp"
#include <vector>
#include <utility>
#include <string>

//  Cities and countries of Africa,
//  spaces of the map.
//  Their sequence in the spaces_ vector
//  of the class Board is listed hier.
// (used german to keep it simple)
enum class Spaces {
    Tanger, Algier, Tunis, Tripolis, Kairo,
    Marokko, Algerien, Libyen, Sahara, Aegypten,
    Kanarische_Inseln, Mauretanien, Mali, Tschadsee, Bur_Sudan,
    St_Helena, Goldkueste, Nigeria, Bangui, Sudan,
    Republik_Kongo, Somalia, Mosambik, Kapstadt,
    NONE
};

// way to reach the other location (space)
enum class WayToReach {
    ONFOOT,
    SAILING,
    FLYING
};

// Topic: wichtige Container der C++-Standardbibliothek
// pair and vector
// description see below
typedef std::vector<std::pair<Spaces, WayToReach>> neighborsVec;

class Space {
public:
    Space(const char * name, int x, int y, neighborsVec neighbors);
    virtual ~Space();

    // working with std::string
    std::string name();
    Position position();
    neighborsVec & neighbors();
private:
    PascalString name_; // using PascalStrings
    Position position_;

    // All the spaces that can be reached from the current one.
    // Just like a map, but should use indexes.
    // Space and identificator
    // 0 - direct, 1 - sailing, 2 - flying.
    neighborsVec neighbors_;
};

#endif