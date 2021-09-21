/**
*   \file   Circle.hpp
*   \author Ilia Budnikov
*/

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "ColoredShape.hpp"
#include <math.h>

// Topic: Inheritance
// Topic: Interface inheritance
// Topic: Abstraktionen (more concrete than ColoredShape)
class Circle : public ColoredShape {
public:
    Circle(int x, int y, int radius, Colors color);
    virtual ~Circle();
    void draw();
private:
    int radius_;
};
#endif