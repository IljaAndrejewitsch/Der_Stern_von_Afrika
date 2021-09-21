/**
*   \file   PascalString.hpp
*   \author Ilia Budnikov
*/

#ifndef PASCALSTRING_HPP
#define PASCALSTRING_HPP

#include "println.hpp"
#include <cstring>
#include <stack>

// Topic: Darstellung, working with Text via PascalString
// Topic: Abstraction, struct
struct PascalString {
public:
    PascalString();

    // Topic: Best Practice 5
    // "single argument constructors should usually be explicit"
    // takes a string
    explicit PascalString(std::string string);
    // takes a cString
    explicit PascalString(const char * cString);
    virtual ~PascalString();

    int hashCode();
    int length();
    char * characters();
    void length(int length);
    void characters(const char * cString);
    // Sets a value to the characters_ array by index.
    // If index < 0 or > 256 sets nothing.
    void setByIndex(int index, char value);

    // Topic: operator overloading
    // Topic: Objektkopien
    // overloading the assignment operator for two PascalStrings
    PascalString & operator= (PascalString other);
    // Overloading the assignment operator for PascalString = std::stack<char>.
    // No reason to make it generic, working only with char.
    // Changed the the stack, should be passed by value.
    PascalString & operator= (std::stack<char> stack);
    // addition assignment operator overloading
    PascalString & operator+= (PascalString right);
    // Topic optional: type cast operator overloading
    // makes it possible to cast a PascalString to int
    explicit operator int() const;

    // Topic optional: friend declarations
    // Topic: operator overloading
    friend std::string as_string(PascalString p);
    friend std::istream & operator>> (std::istream & in, PascalString & toRead);
    friend bool operator== (PascalString left, PascalString right);
    friend bool operator== (PascalString left, const char * right);
    friend bool operator!= (PascalString left, PascalString right);
    friend bool operator< (PascalString left, PascalString right);
    // to concatenate two PascalStrings
    friend PascalString operator+(PascalString left, PascalString right);
private:
    int length_;
    char characters_[256];  // Chars of some character string.
                            // 255 for Characters + 1 spare.
    // to can differ every PascalString as a unique instance
    static int hashCodeStatic_;
    int hashCode_ = 0;
};

// (deprecated) to use std::unordered_map<PascalString, ...>
// Topic opional: namespaces
namespace std {
    template <>
    struct hash<PascalString> {
        size_t operator()(PascalString pStr) const {
            return pStr.hashCode();
        }
    };
}

#endif
