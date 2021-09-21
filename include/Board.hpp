/**
*   \file   Board.hpp
*   \author Ilia Budnikov
*/

#ifndef BOARD_HPP
#define BOARD_HPP

#include "AnsiConsole.hpp"
#include "println.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "Space.hpp"
#include "Player.hpp"
#include "WithDiamondState.hpp"
#include "PlayerFactory.hpp"
#include "PascalString.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <iterator>
#include <typeinfo>
#include <chrono>
#include <thread>

typedef std::vector<std::shared_ptr<Space>>  spacesVec;
typedef std::vector<std::shared_ptr<Player>> playersVec;
// Topic: Funktionszeiger
typedef void (Player::*specialActionPtr_void_void)(void);
class Board;
typedef std::shared_ptr<Board> boardPtr;

class Board {
public:
    // Topic: Design Pattern Singleton
    static boardPtr board();
    // clears spaces_ and uses printResults()
    virtual ~Board();
    
    spacesVec & spaces();
    // Topic: wichtige Container der C++-Standardbibliothek
    // vector von Funktionen
    std::vector<specialActionPtr_void_void> & specialActions();
    playersVec & players();
    // Topic: fruehe Bindung,
    // overloaded methods
    std::shared_ptr<Player> currentPlayer();
    void currentPlayer(std::shared_ptr<Player> player);

    bool kapstadtWasVisited();
    void kapstadtWasVisited(bool wasVisited);

    // Topic: Best Practice 7
    // "use a consistent naming convention, camelCase or under_score"

    // spaceWithAction_ is considered to be empty,
    // if there are no elements or only takeDiamond().
    // Checks if spaceWithAction_ is empty.
    bool checkIfSWAEmpty();

    // fills the spaces_ vector at the beginning of the game
    void fillSpacesVec();
    // fills the specialActions_ vector at the beginning of the game
    void fillSpecialActions();

    // adds players in the game (users to players)
    void addPlayers();

    // special actions
    // perform a special action that connected with the current space
    void performAction();
    // Change the correlation between spaces and special actions.
    // Advice: the spaceWithAction_ map should not be
    // empty (or only with the takeDiamond() inside) to be "shuffled"
    void shuffleSpaceWithAction();
    // In some case a player can lose the diamond (f.e. highwayman).
    // If it happens the the diamond should be taken to Kapstadt.
    void takeDiamondToKapstadt();
private:
    // creats spaces_ and uses printGreeting()
    Board();
    static std::weak_ptr<Board> board_;

    //  spaces on the game board
    // (Spaces is for enum, spaces_ is for vector)
    spacesVec spaces_;

    //  vector of functions, every represents a special actions
    //  that can occur when a player a space steps
    // (functions are stored in the class Player)
    std::vector<specialActionPtr_void_void> specialActions_;

    // Topic: wichtige Container der C++-Standardbibliothek
    //  map of spaces and special actions that occur
    //  when a player steps on it
    // (no entry - no special action on a space)
    std::map<Spaces, specialActionPtr_void_void> spaceWithAction_;

    // All the players in one array.
    // The players' sequence of moves is as the storage sequence.
    playersVec players_;

    // the player is the next to go
    std::shared_ptr<Player> currentPlayer_;

    // variable to mark
    // that a player has already visited Kapstadt once
    bool kapstadtWasVisited_ = false;
};

// Topic: Best Practice 12 "prefer free-standing functions"

// start and end of the game
// prints start greeting and creates players
void printGreeting();
// prints game results, takes the winner to praise
void printResults(std::shared_ptr<Player> winner);

// checks if there anybody who hasn't lost yet
bool checkLost();
// counts the amount of player who hasn't lost yet
int howManyPlay();
// implementation of the overall gaming process
// rolls a dice and returns the result of the roll
int rollDice();
// prints the available actions at the beginning of the turn
void printActions();
// prints actions that should be available to perform by every choice making
void printAddActions();
// the main game process
void play();

// draw Africa map
// Drawing goes from top to bottom,
// because of the corresponding direction of the coordinate axes.
// draws the edging of the African continent
void drawEdging();
// draws routes between points
void drawRoutes();
// marks african cities/countries on the map
void drawSpaces();
// marks players on the map
void drawPlayers();
// draws Africa map without player
void drawAfricaNoPlayers();
// brings all the pieces of the map together
void drawAfrica();

// == helpers ==
// (declaration and definition of the template function should be in .hpp
//  to can use the function in other files)

// Topic: Templates

// std::shared_ptr doesn't support
// pointer-to-member access operator (i.e. ->* and .*),
// this function helps in a way to solve the problem.
// Can be used with a raw pointer and other smart pointers.
template <typename Ptr, typename MemberFunctor>
void invokeViaPointer(Ptr ptr, MemberFunctor func) {
    return ((*ptr).*func)();
}

//  finds all the keys (vector) in a map by value
template <typename First, typename Second>
bool searchByValue(std::vector<First>& foundKeys, std::map<First, Second> map, Second value) {
    bool found = false;
    auto it = map.begin();

    // iterate through the map
    while (it != map.end()) {
        // value of this entry matches with given value
        if (it->second == value) {
            found = true;
            // add the found key
            foundKeys.push_back(it->first);
        }

        it++;
    }

    return found;
}

#endif
