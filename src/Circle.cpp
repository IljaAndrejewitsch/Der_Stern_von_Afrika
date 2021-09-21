/**
*   \file   Circle.cpp
*/

#include "../include/Circle.hpp"

// Topic: Best Practice 6
// "initialize the state of the object properly"
Circle::Circle(int x, int y, int radius, Colors color)
    : ColoredShape(x, y, color), radius_(radius) // member initializer_list
{
}

Circle::~Circle()
{
}

void Circle::draw() {
    // Topic: fruehe Bindung, for x()
    int x_start = position().x() - radius_ / 2;
    int x_stop = position().x() + radius_ / 2;

    for (int i = x_start; i <= x_stop; i++) {
        double x_relative = double(i) - double(x_start);
        double h = sqrt(x_relative * (double(x_stop) - double(x_start) - x_relative));
        ansiConsole.printText(position().x() + int(x_relative) - radius_ / 2,
            position().y() + static_cast<int>(h), "#", color());
        ansiConsole.printText(position().x() + int(x_relative) - radius_ / 2,
            position().y() - static_cast<int>(h), "#", color());
    }
}
