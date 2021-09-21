/**
*   \file	Player.cpp
*   \author Ilia Budnikov
*/

#include "../include/Player.hpp"
#include "../include/Board.hpp"
#include "../include/State.hpp" // all the states use the Player class
#include "../include/DefaultState.hpp"
#include "../include/WithDiamondState.hpp"
#include "../include/RobberState.hpp"

// Topic: Best Practice 6
// "initialize the state of the object properly"
// member initializer_list
Player::Player(PascalString name,
    banknotesVec banknotes, Spaces start)
    : defaultState_(std::make_shared<DefaultState>(this)),         // this is for Player *,
      withDiamondState_(std::make_shared<WithDiamondState>(this)), // not weak_ptr with
      robberState_(std::make_shared<RobberState>(this)),           // shared_from_this()
      currentState_(defaultState_), // defining state members
      banknotes_(banknotes), name_(name), currentSpace_(start)
{
}

Player::Player(PascalString name,
    banknotesVec banknotes, Spaces start,
    std::shared_ptr<State> defaultState,
    std::shared_ptr<State> withDiamondState,
    std::shared_ptr<State> robberState)
    : defaultState_(defaultState),
      withDiamondState_(withDiamondState),
      robberState_(robberState),
      currentState_(defaultState_),
      banknotes_(banknotes), name_(name), currentSpace_(start)
{
}

Player::~Player()
{
}

PascalString Player::name() {
    return name_;
}

std::shared_ptr<State> Player::currentState() {
    return currentState_;
}

void Player::currentState(std::shared_ptr<State> newState) {
    currentState_ = newState;
}

std::shared_ptr<State> Player::defaultState() {
    return defaultState_;
}

std::shared_ptr<State> Player::withDiamondState() {
    return withDiamondState_;
}

std::shared_ptr<State> Player::robberState() {
    return robberState_;
}

Spaces Player::currentSpace() {
    return currentSpace_;
}

bool Player::won() {
    // Topic: Bitoperationen
    // cast to bool:
    // the result is 0 (false) if the value equals 0,
    // otherwise, the result is 1 (true).
    return (status & WON);
}

void Player::won(bool won) {
    // Topic: Bitoperationen
    if (won) // set flag
        status |= WON;
    else     // remove flag (invert and multiply bitwise)
        status &= ~static_cast<uint16_t>(WON);
}

// --- see won() / won(bool)
bool Player::lost() {
    return (status & LOST);
}

void Player::lost(bool lost) {
    if (lost)
        status |= LOST;
    else // works without static_cast, but it's better to keep it logically clear
        status &= ~static_cast<uint16_t>(LOST);
}

bool Player::bankHelped() {
    return (status & BANK_HELPED);
}

void Player::bankHelped(bool bankHelped) {
    if (bankHelped)
        status |= BANK_HELPED;
    else
        status &= ~static_cast<uint16_t>(BANK_HELPED);
}

bool Player::breakTurn() {
    return (status & BREAK_TURN);
}

void Player::breakTurn(bool breakTurn) {
    if (breakTurn)
        status |= BREAK_TURN;
    else
        status &= ~static_cast<uint16_t>(BREAK_TURN);
}

bool Player::canStep() {
    // can't move if min 1 STOP flag is set
    return !(status & STOP);
}
// ---

int Player::skipSteps() {
    return skipSteps_;
}

void Player::skipSteps(int toSkip) {
    skipSteps_ = toSkip;
}

banknotesVec & Player::banknotes() {
    return banknotes_;
}

PascalString Player::typeName() {
    return typeName_;
}

uint Player::budget() {
    uint budget = 0;

    for (auto banknote : banknotes_)
        budget += banknote.value();

    return budget;
}

bool Player::checkBanknote(uint value) {
    if ((value > 100) && (value < 500)) {
        // value can be put together from 100 banknotes
        uint amountOf100 =
            std::count(banknotes().begin(), banknotes().end(), Banknote(100));
        if (amountOf100 >= (value/100)) // e.g. 4 >= (300/100)
            return true;
    }
    else {
        // Topic: wichtige Algorithmen der C++-Standardbibliothek, find
        // searching for a banknote of the value
        auto it = std::find(banknotes_.begin(), banknotes_.end(), Banknote(value));
        return it != banknotes_.end();
    }

    return false;
}

bool Player::deleteBanknote(uint value) {
    // Topic: wichtige Algorithmen der C++-Standardbibliothek, find
    // searching for a banknote of the value
    auto toDelete = std::find(banknotes_.begin(), banknotes_.end(), Banknote(value));
    // deleting the banknote
    auto deleted =
        banknotes_.erase(toDelete);

    return (deleted != banknotes_.end() || banknotes_.empty());
}

void Player::addBanknote(Banknote banknote) {
    banknotes_.push_back(banknote);
}

// Topic: operator overloading
bool operator== (Player left, Player right) {
    // names are unique
    return (left.name() == right.name());
}

bool operator!= (Player left, Player right) {
    return !(left == right);
}

// == helper for goSailing() and goFlying() ==
void Player::change500() {
    bankPtr bank = Bank::bank();

    // Topic: wichtige Algorithmen der C++-Standardbibliothek, count
    // checking if the bank can change
    int amountOf100 =
        std::count(bank->banknotes().begin(), bank->banknotes().end(), Banknote(100));

    if (amountOf100 < 5) { // then the bank has not enought 100 for 500
        // Change money with players.
        // One of players has definitely >= 5 * 100 banknotes.
        // The worst case scenario for sailing:
        // This player has 0, bank has max 4, then others have (19-4)/3=5 (max 4 player).
        // ... for flying:
        // This player has 2, bank has max 4, then the other 3 have 4, 4, 5.
        boardPtr board = Board::board(); // to take the array of players
        playersVec & players = board->players();

        int iter = 0;
        std::shared_ptr<Player> toChangeWith;
        do {
            // searching for another player
            do {
                toChangeWith = players.at(iter);
                ++iter;
            } while (*toChangeWith == *board->currentPlayer());

            // Topic: wichtige Algorithmen der C++-Standardbibliothek, count
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
    else {
        for (int i = 0; i != 5; ++i) { // exchange
            bank->deleteBanknote(100);
            addBanknote(Banknote(100));
        }
        deleteBanknote(500);
        bank->addBanknote(Banknote(500));
    }
}

// === going process ===
void Player::goOnFoot(Spaces toGo) {
    currentSpace_ = toGo;
}

void Player::goSailing(Spaces toGo) {
    if (budget() >= 100) { // just in case, go() already checked this
        bankPtr bank = Bank::bank();
        currentSpace_ = toGo;

        if (!checkBanknote(100)) // if only 500
            change500();

        // -100
        deleteBanknote(100);
        bank->addBanknote(Banknote(100));
    }
}

void Player::goFlying(Spaces toGo) {
    if (budget() >= 300) { // just in case, go() already checked this
        bankPtr bank = Bank::bank();
        currentSpace_ = toGo;
        
        if (!checkBanknote(300)) // not enough 100 banknotes
            change500();

        // -300
        for (int i = 0; i != 3; ++i) {
            deleteBanknote(100);
            bank->addBanknote(Banknote(100));
        }
    }
}

bool Player::checkGo() {
    boardPtr board = Board::board();

    neighborsVec & neighbors =
        board->spaces().at(static_cast<int>(currentSpace_))->neighbors();
    for (auto neighbor : neighbors) {
        if ((((neighbor.second == WayToReach::ONFOOT)) ||
             ((neighbor.second == WayToReach::SAILING) && (budget() >= 100)) ||
             ((neighbor.second == WayToReach::FLYING)  && (budget() >= 300))))
            return true;
    }

    return false; // player is stuck
}

void Player::go() {
    // delegation to the current state
    currentState_->go();
}

void Player::makeTurn(uint steps) {
    // delegation to the current state
    currentState_->makeTurn(steps);
}

// == helpers ==
bool Player::checkIfAnotherOnSpace() {
    boardPtr board = Board::board();

    // checking if a another player has the same position on the board
    for (auto player : board->players()) {
        if (currentSpace() == player->currentSpace() &&
            *this != *player)
            return true;
    }

    return false;
}

std::shared_ptr<Player> Player::whoWithMeOnSpace() {
    boardPtr board = Board::board();

    if (checkIfAnotherOnSpace()) {
        // searching for another player that has the same position on the board
        for (auto player : board->players()) {
            if (currentSpace() == player->currentSpace() &&
                *this != *player) // names are unique
                return player;
        }
    }

    // searching for the same player to return as shared pointer
    for (auto player : board->players()) {
        if (*this == *player)
            return player;
    }

    // it's an unreal case, but should return in any case
    return board->players().at(0);
}

// == special actions ==

void Player::takeDiamond() {
    boardPtr board = Board::board();
    // the diamond is found, shuffle again
    board->shuffleSpaceWithAction();

    println("\
                                    .     '     ,\n\
                                      _________\n\
                                    _/_|_____|_\\_\n\
                                     '. \\   / .'\n\
                                       '.\\ /.'\n\
                                         '.'\n");
    if (howManyPlay() != 1) {
        // set all the players to the robber state
        for (auto player : board->players())
            player->currentState(player->robberState());

        println("\nNun ist ", name_, " der Diamanttraeger!\
\nLaufe schell los und verkaufe den Diamanten, ", name_, "!");
        println("\nAlle anderen Spieler sind jetzt Raeuber (+1 Extraschritt).\
\nIhr sollt den Diamanten wegnehmen!");
    }
    else { // only one player
        println("\nDu hast den Diamanten gefunden!\
\nLaufe schell los und verkaufe diesen, ", name_, "!");
    }

    // this player is now with diamond
    currentState(withDiamondState());
}

void Player::takeGemstone(uint sum) {
    bankPtr bank = Bank::bank();

    if (bank->budget() >= sum) { // if the bank can give the sum
        if (!(bank->checkBanknote(sum))) // not enough 100 banknotes
            bank->change500();

        // player gets money from the bank
        println("Du bekommst ", sum, " von der Bank.");
        // condition: sum is devided by 100 with no rest
        for (int i = 0; i != (sum / 100); ++i) { 
            bank->deleteBanknote(100);
            addBanknote(Banknote(100));
        }
    }
    else { // bank has no money to pay
        println("\nBedauerlicherweise hat die Bank nicht genug Geld,\num dir eine Belohnung auszuzahlen.");
    }
}

void Player::takeTopaz() {
    println("\nWas fuer ein wunderbarer himmelblauer Edelstein!\
\nDu hast ja einen Topas gefunden!");
    takeGemstone(200);
}

void Player::takeEmerald() {
    println("\nSo ein sattes Gruen...\
\nEin Smaragd gehoert nun dir!");
    takeGemstone(300);
}

void Player::takeRuby() {
    println("\nDu traust deinen Augen nicht...\
\nEin echter Rubin liegt in deinen Haenden.");
    takeGemstone(500);
}

void Player::fallToTrap() {
    println("\nEin unmerklicher Laubhaufen entpuppte sich als Falle.\
\nAch, diese einheimischen Staemme mit ihrer Jagd!\
\n\nZum Glueck wurdest du nicht verletzt, aber du steckst in einem tiefen Loch fest.\
\nDu hast in der einen Tasche eine Taschenlampe und in der anderen eine Notiz mit dem Morsealphabet ausgegraben.\
\n\nWarte bis zur Nacht und versuche zu signalisieren.\
\nVielleicht bemerkt es jemand!");
    std::this_thread::sleep_for(std::chrono::seconds(14));

    println("\nDas Morsealphabet:");

    // Topic: Entity Types
    // Topic: Object Lifecycle, new
    MorseCodeParser * parser = new MorseCodeParser();
    // print the Morse code table
    int newLine = 1;
    for (auto pair : parser->codeWithLetter()) {
        // 3 pairs pro line
        if (newLine % 3 != 0) {
            print(pair.first, " " ,pair.second, "\t");
        }
        else {
            println(pair.first, " ", pair.second);
        }
        ++newLine;
    }
    println("\n\nDu kannst \".\" oder \"_\" eingeben.");
    println("Buchstaben solltest du mit einer Leertaste voneinander trennen.");
    bool matchesPattern = false; // if an input matches a predefined pattern
    while (!matchesPattern) {
        PascalString morseCode = checkInput(std::cin,
            PascalString("\nWas moechtest du als Signal geben?"),
            dataTypeInput::MORSE);

        // Topic: Exception handling
        try {
            // decoding
            PascalString decoded = parser->decode(morseCode);
            
            for (auto pattern : parser->patterns()) {
                if (decoded == pattern) // overloaded
                    matchesPattern = true;
            }

            // if the code-string was wrong
            if (!matchesPattern) {
                println("\nHm, wahrscheinlich hat niemand verstanden, was \"", decoded, "\" bedeutet.");
                println("Aber verzweifele nicht! Versuche noch einmal.");
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            else {
                println("\n", decoded, "!");
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
        } catch (PascalString ex) {
            println(ex); // print the exception message
            std::this_thread::sleep_for(std::chrono::seconds(2));
            println("Das ist in Ordnung, versuche dein Versehen diesmal zu korrigieren.");
            println("Viellecht hast du die Leerzeichen zwischen den Buchstaben vergessen?");
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }

    println("\nMan hoert Schritte...");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    println("\nHurra!\
\nJemand hat das Signal erkannt!\
\nDein Versuch war erfolgreich! Freiheit!");

    // Topic: haeufige Fehlerquelle, delete
    delete parser;
}

void Player::wasFascinatedByBeauty() {
    println("\nSie waren fasziniert von der Schoenheit der afrikanischen Natur.\
\nEs ist besser anzuhalten und einfach die Aussicht zu geniessen...");

    breakTurn(true);
}

void Player::wasCaughtBySlaveTrader() {
    println("\nOh nein! Du bist auf eine Gruppe von Sklavenhaendlern gestossen. \
Sie haben dich schneller gefesselt, als du es merkte.\nAlles, was bleibt, ist sich ihnen zu ergeben...");
    std::this_thread::sleep_for(std::chrono::seconds(6));
    println("\nGluecklicherweise hast du in deinem Heimatland einen Kurs zur Freilassung aus Gefangenschaft absolviert,\
\nso dass du eine Chance zur Flucht hast.\nAber es braucht Zeit (3 Schritte)...");
    
    // the player must skip three steps
    skipSteps(3);
}

void Player::wasCaughtByHighwayman() {
    println("\nAch! Du wurdest von einem Wegelagerer erwischt!");
    currentState_->wasCaughtByHighwayman(); // delegation
}
