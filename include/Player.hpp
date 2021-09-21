/**
*   \file   Player.hpp
*   \author Ilia Budnikov
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Banknote.hpp"
#include "Bank.hpp"
#include "Space.hpp"
#include "CheckInput.hpp"
#include "MorseCodeParser.hpp"
class State;
class Board;
#include <vector>

// Topic: Abstraktionen
// All the subclasses should be added to the PlayerFactory.
// This version is used as the default player type.
class Player {
public:
    Player(PascalString name,
        banknotesVec banknotes, Spaces start);
    Player(PascalString name,
        banknotesVec banknotes, Spaces start,
        std::shared_ptr<State> defaultState,
        std::shared_ptr<State> withDiamondState,
        std::shared_ptr<State> robberState);
    virtual ~Player();

    // Topic: Best Practice 8
    // "do not prefix queries and modifiers with get / set"
    // Topic: Objektkopien, copy by return
    PascalString name();
    std::shared_ptr<State> currentState();
    void currentState(std::shared_ptr<State> newState);
    std::shared_ptr<State> defaultState();
    std::shared_ptr<State> withDiamondState();
    std::shared_ptr<State> robberState();
    Spaces currentSpace();
    // Topic: fruehe Bindung,
    // overloaded methods
    // Methods simplify the changing of the player's status (s. below).
    bool won();
    void won(bool won);
    bool lost();
    void lost(bool lost);
    bool bankHelped();
    void bankHelped(bool bankHelped);
    bool breakTurn();
    void breakTurn(bool breakTurn);
    // true, if no STOP flags are set
    bool canStep();
    int skipSteps();
    void skipSteps(int toSkip);
    banknotesVec & banknotes();
    PascalString typeName();
    // return the sum of values of player's banknotes
    uint budget();

    // Topic optional: friend declarations
    // Topic: operator overloading
    friend bool operator== (Player left, Player right);
    friend bool operator!= (Player left, Player right);

    // Checks if a banknote of this value is available.
    // Values > 500 cannot be checked.
    bool checkBanknote(uint value);
    // deletes a banknote, returns true if deleted
    bool deleteBanknote(uint value);
    // Topic: Objektkopien, pass via parameter
    // adds the banknote to the player
    void addBanknote(Banknote banknote);

    // Helper for goSailing() and goFlying().
    // Changes a 500 banknotes with 5*100 banknotes.
    void change500();
    // Topic: subtyping polymorhism
    // can be if necessary overwritten
    // are used by go()
    virtual void goOnFoot(Spaces toGo);
    virtual void goSailing(Spaces toGo);
    virtual void goFlying(Spaces toGo);
    // Helper for go().
    // Checks if a player can (have enough money) to go and is not stuck.
    bool checkGo(); // is used by go()
    // moving a player around the game board by "steps" steps
    virtual void go();
    // with this method the number of steps in derived classes can be changed
    virtual void makeTurn(uint steps); // uses go()

    // checks if a player stays on the same space with another player
    bool checkIfAnotherOnSpace();
    // Return the player that stays on the same space.
    // If there is no player then return this (the same player)
    std::shared_ptr<Player> whoWithMeOnSpace();

    // == special actions ==
    // new actions should be added to the specialActions_
    // in the class Board (in the fillSpecialActions())
    
    // Diamond is found.
    // The player takes the diamond,
    // all the current states will be changed.
    // Can't be overwritten in subclasses or in a state (no delegation).
    void takeDiamond();
    
    // The player has found a gemstone.
    // All the gemstones are same,
    // by and large only the reward differs.
    // This method can be used from all the gemstones.
    // !!! Condition: sum is divided by 100 with no rest.
    void takeGemstone(uint sum);
    
    // Topaz is found.
    // The player takes the topaz and gets 200.
    void takeTopaz();
    
    // Emerald is found.
    // The player takes the emerald and gets 300.
    void takeEmerald();
    
    // Ruby is found.
    // The player takes the ruby and gets 500.
    void takeRuby();
   
    // The player enters the Morse code,
    // which will be recognized by the MorseCodeParser.
    // As long as the message does not match the patterns,
    // the player must keep trying.
    // The action takes place in a cave.
    void fallToTrap();

    // The player was fascinated by
    // the beauty of african nature.
    // The current turn ends.
    void wasFascinatedByBeauty();

    // The player was caught by a group of slave traders.
    // Being enslaved the player has to fight the guards,
    // then he manages to escape.
    // The behaviour can be change depending on the player type.
    virtual void wasCaughtBySlaveTrader();

    // The player was caught by a highwayman during the travelling.
    // The behaviour can be change depending on the player type.
    virtual void wasCaughtByHighwayman();

    // constant values to describe the player's status (s. below)
    // if the player has won
    const static uint8_t WON = 0b1;
    // if the player is lost (was stuck, because didn't have enough money)
    const static uint8_t LOST = 0b10;
    // if the bank helped once
    const static uint8_t BANK_HELPED = 0b100;
    // if the player's should be immediately broken
    const static uint8_t BREAK_TURN = 0b1000;
     
    // Bit pattern for all the marked flags,
    // with which the player can't continue the current turn.
    // !!! Should be changed for newly added bit flags,
    // which influence the player in the same way.
    const static uint16_t STOP = 0b1011;
protected:
    // To create every state only once.
    std::shared_ptr<State> defaultState_;
    std::shared_ptr<State> withDiamondState_;
    std::shared_ptr<State> robberState_;
    // current state of the player
    std::shared_ptr<State> currentState_;

    // total cash position of the player
    banknotesVec banknotes_;
    
    // name of the player's type (Seemann, etc)
    PascalString typeName_ = PascalString("Standardtyp");

    // Topic: Bitmanipulation
    // Current status of the player is managed using bit flags.
    // Player can have max 16 status-flags,
    // so up to 2^16 different status combinations.
    uint16_t status = 0;

    // Shows how many steps (not turns) the player must skip.
    // Can be used also for future special actions.
    int skipSteps_ = 0;

    // name of the player
    PascalString name_;

    // position - occupied space
    Spaces currentSpace_;
};

#endif
