/**
*   \file   MorseCodeParser.hpp
*   \author Ilia Budnikov
*/

#ifndef MORSECODEPARSER_HPP
#define MORSECODEPARSER_HPP

#include "PascalString.hpp"
#include <map>
#include <vector>
#include <stack>

class MorseCodeParser {
public:
    MorseCodeParser();
    virtual ~MorseCodeParser();

    // Gets a correct morse code - string (no unsuitable characters)
    // and returns a decoded wort (recursive implemented).
    PascalString decode(PascalString toDecode);
    // Topic: wichtige Container der C++-Standardbibliothek
    // map and vector
    std::map<PascalString, PascalString> & codeWithLetter();
    std::vector<PascalString> & patterns();
private:
    // all the letter-code combinations
    std::map<PascalString, PascalString> codeWithLetter_ = {
        {PascalString("A"),PascalString("._")},   {PascalString("B"),PascalString("_...")},
        {PascalString("C"),PascalString("_._.")}, {PascalString("D"),PascalString("_..")},
        {PascalString("E"),PascalString(".")},    {PascalString("F"),PascalString(".._.")},
        {PascalString("G"),PascalString("--.")},  {PascalString("H"),PascalString("....")},
        {PascalString("I"),PascalString("..")},   {PascalString("J"),PascalString(".___")},
        {PascalString("K"),PascalString("_._")},  {PascalString("L"),PascalString("._..")},
        {PascalString("M"),PascalString("__")},   {PascalString("N"),PascalString("-.")},
        {PascalString("O"),PascalString("___")},  {PascalString("P"),PascalString(".__.")},
        {PascalString("Q"),PascalString("__._")}, {PascalString("R"),PascalString("._.")},
        {PascalString("S"),PascalString("...")},  {PascalString("T"),PascalString("_")},
        {PascalString("U"),PascalString(".._")},  {PascalString("V"),PascalString("..._")},
        {PascalString("W"),PascalString(".__")}, {PascalString("X"),PascalString("_.._")},
        {PascalString("Y"),PascalString("_.__")}, {PascalString("Z"),PascalString("__..")}
    };

    // some morse code patterns
    std::vector<PascalString> patterns_ = {
        PascalString("HELP"),
        PascalString("SOS"),
        PascalString("HILFE"),
        PascalString("TTT"),
        PascalString("HELPME"),
        PascalString("SAVEOURSOULS"),
        PascalString("SAVEME"),
        PascalString("SAVE")
    };
};

// == helpers for decoder ==
// removes the first character of the PascalString pStr
PascalString rmFirst(PascalString pStr);

// Topic: wichtige Container der C++-Standardbibliothek
// stack
// Topic: Templates
// (declaration and definition of the template function should be in .hpp to can use the function in other files)
// pops all elements of the passed stack
template <typename T>
void clearStack(std::stack<T> & toClear) {
    while (!toClear.empty()) {
        toClear.pop();
    }
}

#endif