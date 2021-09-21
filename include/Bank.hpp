/**
*   \file   Bank.hpp
*   \author Ilia Budnikov
*/

// Topic: Best Practice 3 "use include guards in header files"
#ifndef BANK_HPP
#define BANK_HPP

// Topic: Best Practice 25
// "include your own header file first, standard libraries last"
#include "Banknote.hpp"
#include <vector>
#include <algorithm>
#include <memory>

// Topic optional: Typalias
typedef std::vector<Banknote> banknotesVec;
class Bank;
// Topic: smart pointers
typedef std::shared_ptr<Bank> bankPtr;

class Bank {
// Topic: Best Practice 4
// "public stuff should be declared first, then the private stuff"
public:
    // Topic: Design Pattern Singleton
    static bankPtr bank();
    virtual ~Bank();
    
    // Topic: Best Practice 18
    // "the K&R vs BS war is over, use an extra space around & and *"
    banknotesVec & banknotes();
    uint budget();

    // Checks if a banknote of the value is available.
    // Only banknotes of the value 100 and 500 can be checked.
    bool checkBanknote(uint value);
    // deletes a banknote, returns true if deleted
    bool deleteBanknote(uint value);
    // adds the banknote to the bank
    void addBanknote(Banknote banknote);
    // Changes a 500 banknotes with 5*100 banknotes.
    void change500();
    // Returns "placebo", if there is no such banknote,
    // to elude exception handling and improve robustness.
    // Should be used with checkBanknote().
    Banknote giveBanknote(uint value);
private:
    Bank();
    // Topic: Best Practice 3
    // "do not _prefix member variables, use postfix_ if you must"
    static std::weak_ptr<Bank> bank_;

    banknotesVec banknotes_;
};

#endif
