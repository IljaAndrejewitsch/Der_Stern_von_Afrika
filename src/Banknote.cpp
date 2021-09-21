/**
*   \file	Banknote.cpp
*   \author Ilia Budnikov
*/

#include "../include/Banknote.hpp"

// Topic: Best Practice 6
// "initialize the state of the object properly"
Banknote::Banknote(uint value) : value_(value) // member initializer list
{
}

Banknote::~Banknote()
{
}

// Topic: operator overloading
bool operator== (Banknote left, Banknote right) {
    return left.value() == right.value();
}
