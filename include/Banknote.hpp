/**
*   \file	Banknote.hpp
*   \author Ilia Budnikov
*/

#ifndef Banknote_hpp
#define Banknote_hpp

typedef unsigned int uint;

// Topic: Abstraction, struct
struct Banknote {
public:
    // Topic: Best Practice 5
    // "single argument constructors should usually be explicit"
    explicit Banknote(uint value);
    virtual ~Banknote();

    // Topic: Best Practice 8
    // "do not prefix queries and modifiers with get / set"
    
    // getter and setter with method overwriting
    uint value() { return value_; }
    void value(uint value) { value_ = value; }

    // Topic optional: friend declaration
    friend bool operator== (Banknote left, Banknote right);
private:
    uint value_;
};

#endif