/**
*   \file   PascalString.cpp
*   \author Ilia Budnikov
*/

#include "../include/PascalString.hpp"

int PascalString::hashCodeStatic_ = 0;

// Topic: Best Practice 6
// "initialize the state of the object properly"
PascalString::PascalString() // member initializer_list
    : length_(0), characters_{}, hashCode_(++hashCodeStatic_)
{
}

PascalString::PascalString(std::string string)
    : length_(string.size()), characters_{}, hashCode_(++hashCodeStatic_)
{
    for (int i = 0; i != length_; ++i)
        characters_[i] = string[i];
}

PascalString::PascalString(const char * cString)
    : length_(strlen(cString)), characters_{}, hashCode_(++hashCodeStatic_)
{
    for (int i = 0; i != length_; ++i)
        characters_[i] = cString[i];
}

PascalString::~PascalString()
{
}

int PascalString::length() {
    return length_;
}

char * PascalString::characters() {
    return characters_;
}

void PascalString::length(int length) {
    length_ = length;
}

void PascalString::characters(const char * cString) {
    for (int i = 0; i != length_; ++i) 
        characters_[i] = cString[i];
}

void PascalString::setByIndex(int index, char value) {
    if ((index >= 0) && (index <= 256))
        characters_[index] = value;
}

// converts PascalString to std::string
std::string as_string(PascalString toConvert) {
    toConvert.characters()[toConvert.length()] = 0;
    std::string string(toConvert.characters());
    return string;
}

// Topic: operator overloading
std::istream & operator>> (std::istream & in, PascalString & toRead) {
    std::string toReadString;
    in >> toReadString; // in case of > 256 symbols
    
    // cut everything after 256 (if < 256 nothing changes)
    toReadString = toReadString.substr(0,256);
    toRead.length(toReadString.size());
    toRead.characters(toReadString.c_str());

    return in;
}

PascalString & PascalString::operator= (PascalString other)
{
    // copy the characters to the PascalString object
    strcpy(characters_, other.characters());
    // define the length of the PascalString
    length_ = other.length();

    return *this;
}

PascalString & PascalString::operator= (std::stack<char> stack) {
    // if the stack has more characters than 256
    length_ = (stack.size() <= 256) ? stack.size() : 256;
    for (int i = length_ - 1; i != -1; --i) {
        characters_[i] = stack.top();
        stack.pop();
    }

    return *this;
}

int PascalString::hashCode() {
    return hashCode_;
}

PascalString::operator int() const {
    // see the comment below
    if (length_ > 0) {
        int result = atoi(this->characters_);
        if (result != 0 ||
           (result == 0 &&
            this->characters_[0] == '0')) {
            return result;
        }
    }

    // if string is empty or
    // atoi gave 0 and string is not "0" then return the unique hashCode
    return hashCode_;
}

bool operator== (PascalString left, PascalString right) {
    if (left.length() == right.length()) {
        for (int i = 0; i != left.length(); ++i) {
            // if there is one different character
            if (left.characters()[i] != right.characters()[i])
                return false;
        }
        
        return true;
    }

    // different lengths
    return false;
}

bool operator== (PascalString left, const char * right) {
    // no problem with lengths, compare to left.length()
    for (int i = 0; i != left.length(); ++i) {
        // if there is one different character
        if (left.characters()[i] != right[i])
            return false;
    }

    return true;
}

bool operator!= (PascalString left, PascalString right) {
    return !(left == right);
}

bool operator< (PascalString left, PascalString right) {
    if (left.length() != right.length())
        return left.length() < right.length();

    // compare with the sum of characters
    int sumLeft  = 0;
    int sumRight = 0;
    for (int i = 0; i != left.length(); ++i) {
        sumLeft += left.characters_[i];
        sumRight += right.characters_[i];
    }

    return sumLeft < sumRight;
}

PascalString operator+ (PascalString left, PascalString right) {
    PascalString result;
    if ((left.length() + right.length()) <= 256) {
        result.length(left.length()+right.length());
    }
    else { // truncate the real result string
        result.length(256);
    }

    // first part
    for (int i = 0; i != left.length(); ++i)
        result.setByIndex(i, left.characters()[i]);

    // remaining part, cannot be greater than the rest of the array
    for (int i = 0; (i != right.length()) && (i != 256 - left.length()); ++i)
        result.setByIndex(left.length()+i, right.characters()[i]);

    return result;
}

PascalString & PascalString::operator+= (PascalString right) {
    *this = (*this) + right;
    return (*this);
}
