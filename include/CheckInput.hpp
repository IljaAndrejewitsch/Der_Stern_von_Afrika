/**
*   \file   CheckInput.hpp
*   \author Ilia Budnikov
*/

#ifndef CHECKINPUT_HPP
#define CHECKINPUT_HPP

#include "println.hpp"
#include "PascalString.hpp"
#include <chrono>
#include <thread>

// Topic optional: enumerations
// what should the function checkInput() wait as input
enum class dataTypeInput {
    INT,
    PASCALSTRING,
    MORSE
};

// Topic: Best Practice 23
// "inject side-effects if you must have them"
// Checks the correctness of the user input in different situations.
// Returns a correct input value as PascalString (=> type should bs convertable to PascalString and vice versa).
// For int values can check whether the value is within (including) acceptable limits.
// For PascalStrings the min and max length can be checked.
PascalString checkInput(std::istream & in, const PascalString & inputMessage,
    dataTypeInput dataType, int leftLimit = 0, int rightLimit = 0);

#endif