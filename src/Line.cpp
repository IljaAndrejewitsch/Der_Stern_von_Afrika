/**
*   \file   Line.cpp
*   \author Ilia Budnikov
*/

#include "../include/Line.hpp"

// Topic: Best Practice 6
// "initialize the state of the object properly"
// member initializer_list
Line::Line(int x, int y, int x2, int y2, std::string form, Colors color)
    : ColoredShape(x, y, color), position2_(Position(x2, y2)), form_(form)
{
}

Line::~Line()
{
}

void Line::draw() {
    int x0 = position().x();
    int x1 = position2_.x();
    int y0 = position().y();
    int y1 = position2_.y();

    int dx = std::abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -std::abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;

    int err = dx + dy;
    int e2;

    while (true) {
        ansiConsole.printText(x0, y0, form_, color());

        if ((x0 == x1) && (y0 == y1))
            break;

        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}
