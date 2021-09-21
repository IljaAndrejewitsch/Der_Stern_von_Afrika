/**
*   \file	Space.hpp
*   \author Ilia Budnikov
*/

#include "../include/Space.hpp"

Space::Space(const char * name, int x, int y, neighborsVec neighbors)
    : name_(name), position_(x, y), neighbors_(neighbors)
{
}

Space::~Space()
{
}

std::string Space::name() {
    return as_string(name_);
}

Position Space::position() {
    return position_;
}

neighborsVec & Space::neighbors() {
    return neighbors_;
}
