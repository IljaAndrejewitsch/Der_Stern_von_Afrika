/**
*   \file	Position.hpp
*   \author Ilia Budnikov
*/

#ifndef POSITION_HPP
#define POSITION_HPP

// Topic: Abstraction, struct
// position of elemnts in the console (on the board)
struct Position {
public:
    Position(int x, int y) : x_(x), y_(y) {}
    virtual ~Position() {};

    // Topic: fruehe Bindung,
    // getter and setter with method overwriting
    int x() { return x_; }
    int y() { return y_; }
    void x(int x) { x_ = x; }
    void y(int y) { y_ = y; }
private:
    int x_;
    int y_;
};

#endif