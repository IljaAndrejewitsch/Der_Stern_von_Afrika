/**
*   \file   Bank.cpp
*   \author Ilia Budnikov
*/

// Topic: haeufige Fehlerquelle,
// user header nach template-header
#include "../include/Bank.hpp"
#include "../include/Board.hpp"

// Topic: Best Practice 15
// "by default keep your stuff in the implementation file"

// Singleton
/**
Special thanks to
http://btorpey.github.io/blog/2014/02/12/shared-singletons/
*/
std::weak_ptr<Bank> Bank::bank_;

bankPtr Bank::bank() {
    shared_ptr<Bank> ptr = bank_.lock();

    if (!ptr) {
        ptr.reset(new Bank());
        bank_ = ptr;
    }

    return ptr;
}

Bank::Bank() {
    // Topic: Best Practice 21
    // "for-loops in C++ are often not written like this"
    for (int i = 0; i != 8; ++i)
        banknotes_.push_back(Banknote(500));

    // Topic: grundlegende Kontrollstrukturen
    // Iteration
    for (int i = 0; i != 19; ++i)
        banknotes_.push_back(Banknote(100));
}

Bank::~Bank()
{
}

banknotesVec & Bank::banknotes() {
    // Topic: Best Practice 33 "real professionals indent by four spaces"
    return banknotes_;
}

uint Bank::budget() {
    // Topic: Bitmuster
    // 0 will be correspondingly interpreted
    uint budget = 0;
    
    for (auto banknote : banknotes_)
        budget += banknote.value();
        
    return budget;
}

bool Bank::checkBanknote(uint value) {
    // Topic: grundlegende Kontrollstrukturen
    // Selektion
    if ((value > 100) && (value < 500)) {
        // Topic: wichtige Algorithmen der C++-Standardbibliothek,
        // count and find

        // value can be put together from 100 banknotes
        uint amountOf100 =
            std::count(banknotes().begin(), banknotes().end(), Banknote(100));
        if (amountOf100 >= (value / 100)) // e.g. 4 >= (300/100)
            return true;
    }
    else {
        // searching for a banknote of the value
        auto it = std::find(banknotes_.begin(), banknotes_.end(), Banknote(value));
        return it != banknotes_.end();
    }

    return false;
}

// Topic: Objektkopien, pass via parameter
void Bank::addBanknote(Banknote banknote) {
    banknotes_.push_back(banknote);
}

void Bank::change500() {
    boardPtr board = Board::board();

    // change money with players
    playersVec & players = board->players();
    // Topic: Datentypen
    int iter = 0;
    int amountOf100 = 0; // amount of 100 value Banknotes
    std::shared_ptr<Player> toChangeWith;
    do {
        // take the next player, someone has enough 100 value Banknotes
        toChangeWith = players.at(iter);
        ++iter;

        // searching for all the available 100 banknotes
        amountOf100 =
            std::count(toChangeWith->banknotes().begin(),
                toChangeWith->banknotes().end(), Banknote(100));
    } while (amountOf100 < 5);
    // we have found a player to change with
    for (int i = 0; i != 5; ++i) { // exchange
        toChangeWith->deleteBanknote(100);
        addBanknote(Banknote(100));
    }
    deleteBanknote(500);
    toChangeWith->addBanknote(Banknote(500));
}

bool Bank::deleteBanknote(uint value) {
    // Topic: grundlegende Kontrollstrukturen
    // Sequenz

    // searching for a banknote of the value
    auto toDelete = std::find(banknotes_.begin(), banknotes_.end(), Banknote(value));
    // deleting the banknote
    auto deleted = 
        banknotes_.erase(toDelete);

    return (deleted != banknotes_.end() || banknotes_.empty());
}

Banknote Bank::giveBanknote(uint value) {
    // if there was a banknote of this value
    if (deleteBanknote(value))
        return Banknote(value);
    
    // Topic: Value Types
    return Banknote(0); // "placebo"
}
