/**
*   \file   Line.hpp
*   \author Ilia Budnikov
*/

#ifndef LINE_HPP
#define LINE_HPP

#include "ColoredShape.hpp"

class Line : public ColoredShape {
public:
    Line(int x, int y, int x2, int y2, std::string form, Colors color);
    virtual ~Line();
    void draw();
private:
    Position    position2_;
    std::string form_;
};

#endif