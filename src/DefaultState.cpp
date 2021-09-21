/**
*   \file   DefaultState.cpp
*   \author Ilia Budnikov
*/

#include "../include/DefaultState.hpp"
#include "../include/Board.hpp"
#include "../include/WithDiamondState.hpp"

DefaultState::DefaultState(Player * player)
    : player_(player) // member initializer_list
{
}

DefaultState::~DefaultState()
{
}

// helper for go()
std::pair<neighborsVec, int> DefaultState::chooseOption() {
    boardPtr board = Board::board();
    std::shared_ptr<Space> currentSpace =
        board->spaces().at(static_cast<int>(player_->currentSpace()));

    // to show a number before all the available spaces to go,
    // that a player can then choose
    int num = 1; // create again in every iteration to keep the code understandable
    int additionalNum = -1; // to know when player has chosen the additional actions
                            // and not an available direction from the list
    neighborsVec toRemember; // to remember all the neighbors that were listed
    do {
        println("\nWohin moechtest du gehen, ", player_->name(), "?:");

        num = 1;
        // print only available routes
        for (auto neighbor : currentSpace->neighbors()) {
            if ((((neighbor.second == WayToReach::ONFOOT)) ||
                ((neighbor.second == WayToReach::SAILING) && (player_->budget() >= 100)) ||
                ((neighbor.second == WayToReach::FLYING) && (player_->budget() >= 300)))) {
                // to make it clear, how the player can make the next hop
                PascalString nextWayToReach;
                // Topic: Umwandlung,
                // static_cast<>()
                // problems with tabulation; words > 12 are too long
                if (board->spaces().at(static_cast<int>(neighbor.first))->name().length() < 12) {
                    // this word is too short
                    if (neighbor.first == Spaces::Mali) {
                        nextWayToReach += PascalString(" ");
                    }

                    nextWayToReach += PascalString("\t");
                }
                switch (static_cast<int>(neighbor.second)) {
                    case static_cast<int>(WayToReach::ONFOOT) :
                        nextWayToReach += PascalString("\t(zu Fuss)");
                        break;
                    case static_cast<int>(WayToReach::SAILING) :
                        nextWayToReach += PascalString("\t(mit einem Schiff)");
                        break;
                    case static_cast<int>(WayToReach::FLYING) :
                        nextWayToReach += PascalString("\t(mit einem Flugzeug)");
                        break;
                }
                // print the information about the neighbor
                println(num, ". ",
                    board->spaces().at(static_cast<int>(neighbor.first))->name(), nextWayToReach);
                if (additionalNum == -1) // doing it for the first time
                    toRemember.push_back(neighbor); // neighbor was listed, remember
                ++num;
            }
        }
        additionalNum = num;
        println(additionalNum, ". Andere Moeglichkeiten");

        num = static_cast<int>(checkInput(std::cin,
            PascalString("\nWaehle eine der vorgeschlagenen Zahlen aus:"),
            dataTypeInput::INT, 1, additionalNum));
        if (num == additionalNum)
            printAddActions();

        // player gave up
        if (player_->lost())
            num = -1;

      // While an additional action was chosen or player didn't give up.
      // Direction from the list was chosen? => break loop.
      // Player gave up => break loop.
    } while ((num == additionalNum) && (num != -1));

    return { toRemember, num }; // return the pair
}

void DefaultState::go() {
    /* !!!
    uses one return to stop the go if the player has lost
    (has no money to to take a ship or gives up)
    **/

    // Topic: fortgeschrittene Kontrollstrukturen, 
    // Lambda Expression  
    // lambds-function to find and delete a banknote from bank of the certain value
    bankPtr bank = Bank::bank();
    auto giveToPlayer =
        [this, bank](uint value) {
        // giving the banknote to the player
        player_->addBanknote(bank->giveBanknote(value)); };

    // while a player have not enough money to get out,
    // bank can help him/her and hasn't helped before
    bool bankHelped = false; //  not to set bankHelped_ to the player again
                                // (with corresponding messages, s. below)
    if (!player_->bankHelped()) {
        while (!player_->checkGo() &&
                (bank->checkBanknote(100) || bank->checkBanknote(500))) {
            if (bank->checkBanknote(100)) {
                giveToPlayer(100);
                bankHelped = true;
            }
            else { // only 500 is available
                bank->change500(); // goes back to giveToPlayer in the loop
            }
        }
    }

    boardPtr board = Board::board();
    if (player_->checkGo()) { // if the player has no obstacles to move on

        if (bankHelped) { // if the bank helped during this move
            println("\n! ===================");
            println("\nDu hattest kein Geld, um weiter zu reisen.");
            println("Bank hat dir aber ein bisschen Geld fuer die Schiffahrt gegeben.");
            println("Missbrauche ihre Hilfsbeireitschaft lieber nicht!");
            println("\n======================");
            std::this_thread::sleep_for(std::chrono::seconds(7));
            player_->bankHelped(true);
        }

        // take all listed neighbors and the chosen direction from the list
        std::pair<neighborsVec, int> remembered_chosenNum = chooseOption();
        
        int num = remembered_chosenNum.second;
        // if didn't give up
        if (num != -1) {
            --num; // array starts with an index 0
            neighborsVec toRemember = remembered_chosenNum.first;
            // methods goOnFoot, etc. can be implemented by subclasses of the Player class
            switch (toRemember.at(num).second) { // how to get to the chosen space?
            case WayToReach::ONFOOT:
                player_->goOnFoot(toRemember.at(num).first);
                break;
            case WayToReach::SAILING:
                player_->goSailing(toRemember.at(num).first);
                break;
            case WayToReach::FLYING:
                player_->goFlying(toRemember.at(num).first);
                break;
            default: // not to interrupt the game in a case of a program failure
                player_->goOnFoot(toRemember.at(num).first);
            }

            // giving 500 for the first visit to Kapstadt
            if ((toRemember.at(num).first == Spaces::Kapstadt) &&
                (!board->kapstadtWasVisited())) {
                println("\n! ===================");
                if (bank->checkBanknote(500)) {
                    println("\nDu erhaltest 500, denn du bist am schnellsten nach Kapstadt gekommen!");
                    giveToPlayer(500);
                }
                else if (bank->checkBanknote(100)) { // min one 100 banknote
                    int amountOfGiven = 0;
                    // while <= 500 and bank has 100 banknotes
                    do {
                        giveToPlayer(100);
                        ++amountOfGiven;
                    } while ((amountOfGiven != 5) && (bank->checkBanknote(100)));
                    println("\nAls der schnellste Besucher hast du ", amountOfGiven * 100, " von der Bank erhalten!");
                }
                println("\n======================");
                std::this_thread::sleep_for(std::chrono::seconds(3));
                board->kapstadtWasVisited(true);
            }

            // perfors an action that the chosen space has at the current game period
            board->performAction();
        }
    }
    else { // if bank cannot help anymore, but the player is still stuck
        println("\n! ===================");
        std::shared_ptr<Space> currentSpace =
            board->spaces().at(static_cast<int>(player_->currentSpace()));
        println("\nDu hast nicht genug Geld fuer eine Schiffahrt!");
        println("Der Ort \"", currentSpace->name(), "\" ist dein Zuhause fuer den Rest deines Lebens!");
        player_->lost(true);
        std::this_thread::sleep_for(std::chrono::seconds(5));
        // Topic: haeufige Fehlerquelle, illegale Typumwandlungen
        // Topic: Umwandlung,
        // dynamic_pointer_cast<>()
        // if the player has the diamond
        if (dynamic_pointer_cast<WithDiamondState>(player_->currentState())) {
            println("\nLeider verlierst du auch den Diamanten.");
            // diamond to Kapstadt
            board->takeDiamondToKapstadt();
            println("Der Diamant wurde nach Kapstadt gebracht.");
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        println("\n======================");
    }
}

void DefaultState::makeTurn(uint steps) {
    // the player makes as many moves as the dice obligates
    int toSkip;
    for (uint i = 0; i != steps; ++i) {
        // The player can lose, win or be fascinated during the turn,
        // so shouldn't then make steps anymore.
        // But in case it didn't happen:
        if (player_->canStep()) {
            println("\n/// Schritt ", i + 1, " von ", steps, ":");
            toSkip = player_->skipSteps();
            if (toSkip > 0) {
                // in this case the player actually doesn't move,
                // but the steps continue to be counted
                player_->skipSteps(--toSkip);
                if (toSkip > 1) // still at least one step to skip
                    println("\nDu bleibst diesen Schritt und noch ", toSkip, " Schritte stehen.");
                else if (toSkip == 1)
                    println("\nDiesen und den naechsten Schritt bleibst du noch im Stillstand!");
                else
                    println("\nAb dem naechsten Schritt kannst du losgehen!");
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            else {
                player_->go(); // state can be changed during the current move
            }
        }
    }

    if (player_->breakTurn()) // if during the turn the breakTurn bit was set
        player_->breakTurn(false); // the turn was already broken, now can unset the flag
}

void DefaultState::wasCaughtByHighwayman() {
    println("\nLeider hast du Geld und gute Laune verloren.");
    bankPtr bank = Bank::bank();
    // take away all the player's money to the common bank
    for (auto banknote : player_->banknotes())
        bank->addBanknote(banknote);
    while (!player_->banknotes().empty()) {
        if (player_->checkBanknote(100)) {
            player_->deleteBanknote(100);
        }
        else {
            player_->deleteBanknote(500);
        }
    }
}
