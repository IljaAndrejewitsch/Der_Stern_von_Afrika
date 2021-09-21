/**
*   \file   MorseCodeParser.cpp
*   \author Ilia Budnikov
*/

#include "../include/MorseCodeParser.hpp"
#include "../include/Board.hpp"

MorseCodeParser::MorseCodeParser()
{
}

MorseCodeParser::~MorseCodeParser()
{
}

PascalString rmFirst(PascalString pStr) {
    PascalString pStrNew;
    pStrNew.length(pStr.length()-1); // length can be 0

    // starting with the second element of pStr
    for (int i = 1; i != pStr.length(); ++i)
        pStrNew.setByIndex(i - 1, pStr.characters()[i]);

    return pStrNew;
}

// Topic: grundlegende Kontrollstrukturen, Rekursion
// Topic: fortgeschrittene Kontrollstrukturen, Parser
PascalString MorseCodeParser::decode(PascalString toDecode) {
    // advise:
    // trace the implementation with an own input to understand it quickly

    // Goes through the code-string and read step by step letters between spaces.
    // If an unsuitable symbol combination found then throws an exception.

    // it's simpler to work without stack,
    // but work with a stack is a cognitive process
    static std::stack<char> stack; // To store tokens of toDecode step by step.
                                   // Characters go through the recursive calls
                                   // until a complete letter appears.
    PascalString result; // PascalString of the current part of toDecode
                         // that is stored in the stack now,
                         // to check whether this code-part is a letter

    if (toDecode.length() != 0) { // not at the end of the code-string
        if (isspace(toDecode.characters()[0])) {
            if (!stack.empty()) { // if it's the end of a letter
                result = stack; // overloaded
                // such a letter was found
                std::vector<PascalString> keys;
                // using searchByValue() helper from class Board
                if (searchByValue(keys, codeWithLetter_, result)) {
                    // start with a clean slate
                    clearStack(stack);
                    // return the letter, eat the space and go on
                    return keys.at(0) + decode(rmFirst(toDecode));
                }
                else { // was not found
                    // Topic: fortgeschrittene Kontrollstrukturen, Exceptions
                    // throw an exception because no letter for the string was found
                    throw PascalString(PascalString("\n\"") + result + PascalString("\" ist eine inkorrekte Zeichenkette."));
                }
            }
            else { // whitespace before the next word
                return decode(rmFirst(toDecode));
            }
        }
        else { // a new character => read it
            stack.push(toDecode.characters()[0]);
            // and go on
            return decode(rmFirst(toDecode));
        }
    }
    
    if (!stack.empty()) {
        result = stack; // stack has min 1 element (due to checkInput)
        // clear the rest for the next use of the method
        clearStack(stack);
        // such a letter was found
        std::vector<PascalString> keys;
        // using searchByValue() helper from class Board
        if (searchByValue(keys, codeWithLetter_, result)) {
            // the last letter, base case
            return keys.at(0); // .at(0) 'cause there is only one key pro value
        }
        else { // was not found
            // throw an exception because no letter for the string was found
            throw PascalString(PascalString("\n\"") + result + PascalString("\" ist eine inkorrekte Zeichenkette."));
        }
    }

    return PascalString(""); // whitespace at the end of the code
}

std::map<PascalString, PascalString> & MorseCodeParser::codeWithLetter() {
    return codeWithLetter_;
}

std::vector<PascalString> & MorseCodeParser::patterns() {
    return patterns_;
}
