/**
*   \file   ColoredShape.hpp
*   \author Ilia Budnikov
*/

#ifndef COLOREDSHAPE_HPP
#define COLOREDSHAPE_HPP

#include "AnsiConsole.hpp"
#include "Position.hpp"

// Topic: Abstraktionen (hoehes Niveau)
class ColoredShape {
public:
    ColoredShape(int x, int y, Colors color);
    virtual ~ColoredShape();

    Colors color();
    Position position();

    // Topic: virtual method
    // Topic: Interface inheritance, abstract class
    // Topic optional: pure virtual methods
    virtual void draw() = 0; // pure virtual
private:
    Position position_;
    Colors color_;
};

#endif