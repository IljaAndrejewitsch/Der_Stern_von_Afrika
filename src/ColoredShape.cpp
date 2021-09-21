/**
*   \file   ColoredShape.cpp
*   \author Ilia Budnikov
*/

#include "../include/ColoredShape.hpp"

// Topic: Best Practice 6
// "initialize the state of the object properly"
ColoredShape::ColoredShape(int x, int y, Colors color)
    : position_(Position(x, y)), color_(color) // member initializer_list
{
}

ColoredShape::~ColoredShape()
{
}

Colors ColoredShape::color() {
    return color_;
}

Position ColoredShape::position() {
    return position_;
}
