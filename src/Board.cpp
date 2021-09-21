/**
*   \file   Board.cpp
*   \author Ilia Budnikov
*/

#include "../include/Board.hpp"
#include "../include/CheckInput.hpp"

// Singleton
/**
Special thanks to
http://btorpey.github.io/blog/2014/02/12/shared-singletons/
*/

std::weak_ptr<Board> Board::board_;

boardPtr Board::board() {
    shared_ptr<Board> ptr = board_.lock();

    if (!ptr) {
        ptr.reset(new Board());
        board_ = ptr;
    }

    return ptr;
}

Board::Board()
{
}

Board::~Board()
{
}

void Board::fillSpacesVec() {
    // Adding every space on the board.
    // Each space has name, coordinates, neighbor spaces.
    spaces_.push_back(
        std::make_shared<Space>(
            "Tanger", 19, 3,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Algerien,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Algier,
                                                       WayToReach::SAILING),
                          std::pair<Spaces,WayToReach>(Spaces::Marokko,
                                                       WayToReach::FLYING),
                          std::pair<Spaces,WayToReach>(Spaces::Libyen,
                                                       WayToReach::FLYING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Algier", 24, 2,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Tanger,
                                                       WayToReach::SAILING),
                          std::pair<Spaces,WayToReach>(Spaces::Tunis,
                                                       WayToReach::SAILING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Tunis", 29, 2,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Algerien,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Libyen,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Algier,
                                                       WayToReach::SAILING),
                          std::pair<Spaces,WayToReach>(Spaces::Tripolis,
                                                       WayToReach::SAILING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Tripolis", 33, 4,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Tunis,
                                                       WayToReach::SAILING),
                          std::pair<Spaces,WayToReach>(Spaces::Kairo,
                                                       WayToReach::SAILING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Kairo", 43, 5,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Sahara,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Tripolis,
                                                       WayToReach::SAILING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Marokko", 16, 6,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Mali,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Mauretanien,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Kanarische_Inseln,
                                                       WayToReach::SAILING),
                          std::pair<Spaces,WayToReach>(Spaces::Tanger,
                                                       WayToReach::FLYING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Algerien", 23, 7,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Tanger,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Tunis,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Mali,
                                                       WayToReach::ONFOOT) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Libyen", 31, 7,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Tunis,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Sahara,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Tschadsee,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Tanger,
                                                       WayToReach::FLYING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Sahara", 37, 8,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Libyen,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Kairo,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Aegypten,
                                                       WayToReach::ONFOOT) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Aegypten", 44, 8,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Sahara,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Bur_Sudan,
                                                       WayToReach::SAILING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Kanarische Inseln", 5, 4,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Marokko,
                                                       WayToReach::SAILING),
                          std::pair<Spaces,WayToReach>(Spaces::St_Helena,
                                                       WayToReach::SAILING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Mauretanien", 16, 9,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Marokko,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Goldkueste,
                                                       WayToReach::ONFOOT) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Mali", 23, 10,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Algerien,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Marokko,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Tschadsee,
                                                       WayToReach::ONFOOT) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Tschadsee", 31, 10,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Mali,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Libyen,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Bangui,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Nigeria,
                                                       WayToReach::FLYING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Bur Sudan", 51, 9,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Aegypten,
                                                       WayToReach::SAILING),
                          std::pair<Spaces,WayToReach>(Spaces::Somalia,
                                                       WayToReach::SAILING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "St. Helena", 7, 19,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Kanarische_Inseln,
                                                       WayToReach::SAILING),
                          std::pair<Spaces,WayToReach>(Spaces::Republik_Kongo,
                                                       WayToReach::SAILING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Goldkueste", 17, 12,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Mauretanien,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Nigeria,
                                                       WayToReach::ONFOOT) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Nigeria", 25, 13,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Goldkueste,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Republik_Kongo,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Tschadsee,
                                                       WayToReach::FLYING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Bangui", 40, 18,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Tschadsee,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Sudan,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Kapstadt,
                                                       WayToReach::FLYING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Sudan", 44, 12,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Bangui,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Republik_Kongo,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Somalia,
                                                       WayToReach::ONFOOT) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Republik Kongo", 33, 17,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Nigeria,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Sudan,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Kapstadt,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::St_Helena,
                                                       WayToReach::SAILING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Somalia", 55, 12,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Sudan,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Mosambik,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Bur_Sudan,
                                                       WayToReach::SAILING) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Mosambik", 45, 20,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Somalia,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Kapstadt,
                                                       WayToReach::ONFOOT) }));

    spaces_.push_back(
        std::make_shared<Space>(
            "Kapstadt", 38, 26,
            neighborsVec{ std::pair<Spaces,WayToReach>(Spaces::Republik_Kongo,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Mosambik,
                                                       WayToReach::ONFOOT),
                          std::pair<Spaces,WayToReach>(Spaces::Bangui,
                                                       WayToReach::FLYING) }));
}

void Board::fillSpecialActions() {
    specialActions_.push_back(&Player::takeDiamond);
    specialActions_.push_back(&Player::takeTopaz);
    specialActions_.push_back(&Player::takeEmerald);
    specialActions_.push_back(&Player::takeRuby);
    specialActions_.push_back(&Player::fallToTrap);
    specialActions_.push_back(&Player::wasFascinatedByBeauty);
    specialActions_.push_back(&Player::wasCaughtBySlaveTrader);
    specialActions_.push_back(&Player::wasCaughtByHighwayman);
}

void Board::addPlayers() {
    print("\nWie viele Spieler werden an dem Spiel teilnehmen? (1-4)");

    // Topic: Umwandlung, static_cast<>()
    int amountOfPlayers = static_cast<int>(checkInput(std::cin, PascalString(""),
        dataTypeInput::INT, 1, 4));

    PascalString name;
    Types chosenType;
    Spaces chosenStart;
    int num; // to show a number before a type
    std::vector<PascalString> names;
    for (int i = 0; i != amountOfPlayers; ++i) {
        if (i != 0) // for beauty's sake
            println("");

        if (amountOfPlayers > 1)
            println("\nWie heisst der Spieler Nr. ", (i + 1), "?");
        else
            println("\nWie heisst du?");

        // Topic: grundlegende Kontrollstrukturen
        // Subroutinen
        name = checkInput(std::cin,
            PascalString("\nGebe bitte eine Zeichenkette (2 <= Laenge <= 20) ein:"),
            dataTypeInput::PASCALSTRING, 2, 20);
        // checking if the chosen name is already in use
        while (std::find(names.begin(), names.end(), name) != names.end()) {
            println("\nDieser Name wird bereits verwendet.");
            println("Nehme bitte einen neuen.");
            // waiting for 2 sec
            std::this_thread::sleep_for(std::chrono::seconds(2));
            name = checkInput(std::cin,
                PascalString("\nGebe bitte eine Zeichenkette (2 <= Laenge <= 20) ein:"),
                dataTypeInput::PASCALSTRING, 2, 20);
        }
        names.push_back(name);

        println("\n\nWelchen Abenteurertyp moechtest du spielen, ", name, "?");
        // Topic: haeufige Fehlerquelle,
        // Verwendung von Variablen, denen kein Wert zugewiesen wurde
        num = 1;
        // show all the descroptions to the user
        for (auto description : PlayerFactory::typesDescriptions) {
            println("\n", num, ". ", description.second);
            ++num;
        }
        num = static_cast<int>(checkInput(std::cin,
            PascalString("\nWaehle eine der vorgeschlagenen Zahlen aus:"),
            dataTypeInput::INT, 1, PlayerFactory::typesDescriptions.size()));
        --num;
        // Topic: haeufige Fehlerquelle,
        // illegale Typumwandlungen sind moeglich
        chosenType = static_cast<Types>(num);
    
        drawAfricaNoPlayers(); // map preview
        println("\n\nAuf welchem Spielfeld moechtest du das Spiel beginnen?");
        println("1. Tanger\n2. Kairo");
        num = static_cast<int>(checkInput(std::cin,
            PascalString("\nWaehle eine der vorgeschlagenen Zahlen aus:"),
            dataTypeInput::INT, 1, 2));
        if (num == 1)
            chosenStart = Spaces::Tanger;
        else
            chosenStart = Spaces::Kairo;

        // create a player by criteria
        players_.push_back(PlayerFactory::createType(name, chosenStart, chosenType));

        println("\nAlles klar!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Board::performAction() {
    // Topic: wichtige Algorithmen der C++-Standardbibliothek,
    // find

    // perform the action on the current space
    auto currentAction =
        spaceWithAction_.find(currentPlayer_->currentSpace());

    // if there is a special action token on a space
    if (currentAction != spaceWithAction_.end()) {
        println("\n! ===================");
        invokeViaPointer(currentPlayer_, currentAction->second);
        println("\n=====================");
        std::this_thread::sleep_for(std::chrono::seconds(6));
        // remove the action token from the space
        spaceWithAction_.erase(currentPlayer_->currentSpace());
    }
    // else do nothing
}

bool Board::checkIfSWAEmpty() {
    // Topic: haeufige Fehlerquelle,
    // operatorprioritaeten koennen falsch ausgelegt werden

    return (spaceWithAction_.size() == 0) || // there are no elements
           (spaceWithAction_.size() == 1 &&
            spaceWithAction_.begin()->second ==
                &Player::takeDiamond);       // or only takeDiamond()
}

void Board::shuffleSpaceWithAction() {
    // If the map is not clear before the shuffle.
    // According to the game logic the case cannot occur,
    // but it's better to check it.
    // It's possible that there is takeDiamond() in the map,
    // should not remove it.
    if (!checkIfSWAEmpty()) { // there is/are rest element(s)
                              // and not only takeDiamond()
        std::vector<Spaces> foundKeys;
        // if contains takeDiamond()
        if (searchByValue(foundKeys, spaceWithAction_, &Player::takeDiamond)) {
            // diamond can be only on one space,
            // this space is at the beginning of the array
            Spaces spaceWithDiamond = foundKeys.at(0);
            // remove all elements from the map
            spaceWithAction_.clear();
            // get the diamond back to its space
            spaceWithAction_.insert({ spaceWithDiamond, &Player::takeDiamond });
        }
        else {
            // just remove all the rest elements from the map
            spaceWithAction_.clear();
        }
    }

    int randomSpace; // for a random space (s. below)
    // two times the same special actions (but the diamond only once)
    for (int i = 0; i != 2; ++i) {
        // go through the vector with the iterator action
        auto action = specialActions_.begin();
        // a space for every special action
        while (action != specialActions_.end()) {
            do {
                // Topic: haeufige Fehlerquelle,
                // off by one (see spaces_.at(randomSpace))

                //  choose a random space on the board
                // (between 0 and number of spaces)
                randomSpace = std::rand() % spaces_.size();
            // cannot place an action token on one of these cities
            // and two tokens on the same space
            } while (spaces_.at(randomSpace)->name() == "Tanger"   ||
                     spaces_.at(randomSpace)->name() == "Kairo"    ||
                     spaces_.at(randomSpace)->name() == "Kapstadt" ||
                     spaceWithAction_.find(static_cast<Spaces>(randomSpace)) !=
                         spaceWithAction_.end());
            // a suitable space for the action token is found, can place it hier
            spaceWithAction_.insert({ static_cast<Spaces>(randomSpace), *action });

            // Diamond should be hidden only once when the game starts.
            // Morse-minigame only once too.
            if (*action == &Player::takeDiamond) {
                action = specialActions_.erase(action);
            }
            else if (*action == &Player::fallToTrap) {
                action = specialActions_.erase(action);
            }
            else {
                ++action;
            }
        }
    }
}

// == special actions ==
void Board::takeDiamondToKapstadt() {
    // Topic: wichtige Algorithmen der C++-Standardbibliothek,
    // for_each
    // Topic: fortgeschrittene Kontrollstrukturen,
    // Lambda Expression

    // set all the player back to the default state
    std::for_each(players_.begin(), players_.end(),
        [](std::shared_ptr<Player> player) { player->currentState(player->defaultState()); });

    // diamond to Kapstadt
    spaceWithAction_.insert({ Spaces::Kapstadt, &Player::takeDiamond });
}

void printGreeting() {
    // Topic: Idiom RAII
    class RAIIvector {
    public:
        std::vector<Line*> box;
        ~RAIIvector() {
            // Topic: Object Lifecycle, delete
            // Topic: haeufige Fehlerquelle, use after free
            for (auto line : box)
                delete line;
            box.clear();
        }
    };
    RAIIvector rv;

	// Topic: Value Types
	// Topic: Object Lifecycle
    AnsiConsole().clearScreen();
    // Topic: Entity Types
    // Topic: Object Lifecycle, new
    rv.box.push_back(new Line(14,3, 30,3, "=", Colors::GREEN));
    rv.box.push_back(new Line(14,4, 14,6, "||", Colors::GREEN));
    rv.box.push_back(new Line(14,7, 14,10, "||", Colors::BLUE));
    rv.box.push_back(new Line(29,4, 29,6, "||", Colors::GREEN));
    rv.box.push_back(new Line(29,7, 29,10, "||", Colors::BLUE));
    rv.box.push_back(new Line(14,11, 30,11, "=", Colors::BLUE));
    for (auto side : rv.box) {
        side->draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        println(""); // AnsiConsole components work disorderly on linux
        			 // with sleeping. To make it be printed sequentially,
        			 // not all at once, use print("")
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ansiConsole.printText(17,5, "Willkommen", Colors::CYAN);
    println("");
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    ansiConsole.printText(17,6, "  zum Spiel", Colors::CYAN);
    println("");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    ansiConsole.printText(17,8, "\"DER STERN", Colors::MAGENTA);
    ansiConsole.printText(17,9, "VON AFRIKA\"", Colors::MAGENTA);
    println("\n\n");
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void printResults(std::shared_ptr<Player> winner) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    AnsiConsole().clearScreen();
    
    if (winner->won()) {
        Line * finishLine = new Line(1,2, 68,2, "=", Colors::MAGENTA);
        finishLine->draw();
        println("\n                       \\\\\\|||///");
        println("\n                     Glueckwunsch!");
        println("\n                       ///|||\\\\\\");
        println("\n", winner->name(), " hat gewonnen!");
        println("\nDu hast es geschafft,\
\nden Diamanten gewinnbringend zu verkaufen und damit reich zu werden!");
        delete finishLine;
    }
    else {    // if all players have lost,
              // then winner (parameter) has lost too
        Line * blue = new Line(1,2, 71,2, "=", Colors::BLUE);
        blue->draw();
        println("\nLeider hat niemand den Stern des Suedens\
 in Tanger oder Kairo verkauft.");
        println("Beeilt ihr euch, wieder nach Afrika zurueckzukehren!");
        println("\nDer Diamant wartet!");
        
        delete blue;
    }

    std::this_thread::sleep_for(std::chrono::seconds(4));
    println("\n\nDas Spiel ist zu Ende gegangen.");
    println("Bis zum naechsten Mal, Abenteurer!");
    std::this_thread::sleep_for(std::chrono::seconds(4));
}

spacesVec & Board::spaces() {
    return spaces_;
}

std::vector<specialActionPtr_void_void> & Board::specialActions() {
    return specialActions_;
}

playersVec & Board::players() {
    return players_;
}

std::shared_ptr<Player> Board::currentPlayer() {
    return currentPlayer_;
}

void Board::currentPlayer(std::shared_ptr<Player> player) {
    currentPlayer_ = player;
}

bool Board::kapstadtWasVisited() {
    return kapstadtWasVisited_;
}

void Board::kapstadtWasVisited(bool wasVisited) {
    kapstadtWasVisited_ = wasVisited;
}


// == play-process methods ==
int rollDice() {
    // Topic optional: generate random numbers

    // rolling a dice (in the range 1 to 3)
    int rollRes = std::rand() % 3 + 1;

    return rollRes;
}

void printAddActions() {
    boardPtr board = Board::board();

    println("\nWas moechtest du tun?");
    println("1. Einen Blick auf Afrika werfen");
    println("2. Portemonnaie ueberpruefen");
    println("3. Wer bin ich?");
    println("4. Aus Afrika fliehen!");
    println("5. Spiel beenden");
    println("6. Zurueck");
    int num = static_cast<int>(checkInput(std::cin,
        PascalString("\nWaehle eine der vorgeschlagenen Zahlen aus."),
        dataTypeInput::INT, 1, 6));
    switch(num) {
        case 1:
            drawAfrica();
            break;
        case 2:
            if (board->currentPlayer()->budget() != 0) {
                println("\n/// Du hast ",
                    board->currentPlayer()->budget(), " in deinem Portemonnaie.");
            }
            else { // if the player is broke
                println("\n/// Du hast nichts in deinem Portemonnaie!");
            }

            std::this_thread::sleep_for(std::chrono::seconds(3));
            break;
        case 3:
            println("\n/// Dein Name ist „", board->currentPlayer()->name(), "“");
            println("/// und du bist vom Typ „", board->currentPlayer()->typeName(), "“");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            break;
        case 4:
            println("\n/// Bist du sicher?");
            num = static_cast<int>(checkInput(std::cin,
                PascalString("\n1 - Ja!\n2 - Abbrechen"),
                dataTypeInput::INT, 1, 2));            
            if (num == 1) {
                board->currentPlayer()->lost(true);
                println("\n/// Danke fuer das Spiel! Komme bald wieder!");
                std::this_thread::sleep_for(std::chrono::seconds(3));
                // Topic: Umwandlung,
                // dynamic_pointer_cast<>()
                // if the player has the diamond
                // and not all the players have lost
                if (dynamic_pointer_cast<WithDiamondState>(
                    board->currentPlayer()->currentState()) &&
                    !checkLost()) {
                    println("\n! ===================");
                    // diamond to Kapstadt
                    board->takeDiamondToKapstadt();
                    println("\nDer Diamant wurde nach Kapstadt gebracht.");
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    println("\n======================");
                }
            }
            break;
        case 5:
            println("\n/// Bist du sicher?");
            num = static_cast<int>(checkInput(std::cin,
                PascalString("\n1 - Ja!\n2 - Abbrechen"),
                dataTypeInput::INT, 1, 2));            
            if (num == 1) {
                // Topic: wichtige Algorithmen der C++-Standardbibliothek,
                // for_each
                // all the player lose
                std::for_each(board->players().begin(), board->players().end(),
                     [](std::shared_ptr<Player> player) { player->lost(true); });
                println("\n/// Danke fuer das Spiel!");
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            break;
    }
}

void printActions() {
    boardPtr board = Board::board();

    int num = 0;
    do {
        println("\nWas moechtest du tun, ", board->currentPlayer()->name(), "?");
        println("1. Wuerfeln\n2. Andere Moeglichkeiten");  // choice options are unambiguous
        num = static_cast<int>(checkInput(std::cin,
            PascalString("\nWaehle eine der vorgeschlagenen Zahlen aus."),
            dataTypeInput::INT, 1, 2));

        if (num == 2)
            printAddActions();
      // while the player doesn't want roll the dice and didn't give up
    } while ((num != 1) && !(board->currentPlayer()->lost()));

    if (!board->currentPlayer()->lost()) { // didn't give up, but rolled the dice
        int rollResult = rollDice();
        println("\n==========================");
        println("Du hast eine ", rollResult, " gewuerfelt!");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        println("Los geht's!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        board->currentPlayer()->makeTurn(rollResult);
    }
}

bool checkLost() {
    boardPtr board = Board::board();
    uint lostNum = 0;
    // counting the number of players with the lost-status true
    for (auto player : board->players()) {
        if (player->lost())
            ++lostNum;
    }

    return lostNum == board->players().size();
}

int howManyPlay() {
    boardPtr board = Board::board();
    uint lostNum = 0;
    // counting the number of players with the lost-status true
    for (auto player : board->players()) {
        if (player->lost())
            ++lostNum;
    }

    return board->players().size() - lostNum;
}

void play() {
    boardPtr board = Board::board();
    printGreeting();
    board->fillSpacesVec();
    board->fillSpecialActions();
    board->addPlayers();

    do {
        // if there is no special action token on the spaces anymore
        // then shuffle the spaceWithAction_ (only takeDiamond() can be in)
        if (board->checkIfSWAEmpty()) {
            board->shuffleSpaceWithAction();
        }

        // iterates the players array,
        // this is the game sequence
        for (auto player : board->players()) {
            if (!player->lost()) {
                println("\n\n///===================");
                println(player->name(), ", du bist am Zug!");
                std::this_thread::sleep_for(std::chrono::seconds(2));
                board->currentPlayer(player); // set the new current player
                printActions();
            }

            // !!! break the loop if a player wins
            if (player->won())
                break;
        }
    // if the current player has won during the turn
    // or all the player have lost (stuck)
    } while (!(board->currentPlayer()->won()) && !checkLost());

    // this is the end
    printResults(board->currentPlayer());
}


/** draws the Cartesian coordinate system
void coordinateSystem() {
    int iter = 1;
    // 20 * 2 - 1 for 2 in 20 and 20*2 for 0 in 20
    for (int i = 1; i != 61; i += 2) {
        ansiConsole.printText(i, 1, std::to_string(iter), Colors::GREEN);
        ++iter;
    }
    for (int i = 2; i != 40; ++i) {
        ansiConsole.printText(1, i, std::to_string(i), Colors::WHITE);
        for (int j = 3; j < 60; ++j)
            ansiConsole.printText(j, i, "o", Colors::WHITE);
    }
}
*/

// === Drawing Africa ===
void drawEdging() {

    // Topic: Idiom RAII
    class RAIIvector {
    public:
        std::vector<ColoredShape*> edging;
        ~RAIIvector() {
            for (auto line : edging)
                delete line;
            edging.clear();
        }
    };
    RAIIvector rv;

    // 

    // -- LEFT SIDE --
    // left top side: top
    rv.edging.push_back(new Line(28, 1, 18, 1, "=", Colors::GREEN));
    rv.edging.push_back(new Line(17, 1, 9, 7, "//", Colors::GREEN));
    // left top side: middle
    rv.edging.push_back(new Line(9, 7, 9, 10, "||", Colors::GREEN));
    rv.edging.push_back(new Line(9, 11, 16, 14, "\\\\", Colors::GREEN));
    // left top side: bottom
    rv.edging.push_back(new Line(16, 15, 25, 16, "\\\\", Colors::GREEN));
    // left bottom side
    rv.edging.push_back(new Line(26, 16, 35, 29, "\\\\", Colors::GREEN));

    // -- RIGHT SIDE --
    // right top side: top
    rv.edging.push_back(new Line(29, 1, 31, 2, "\\\\", Colors::GREEN));
    rv.edging.push_back(new Line(32, 3, 43, 3, "=", Colors::GREEN));
    // right top side: middle
    rv.edging.push_back(new Line(44, 3, 57, 11, "\\\\", Colors::GREEN));
    rv.edging.push_back(new Line(57, 11, 61, 10, "=", Colors::GREEN));
    rv.edging.push_back(new Line(60, 11, 54, 15, "//", Colors::GREEN));
    // right bottom side
    rv.edging.push_back(new Line(54, 16, 45, 25, "//", Colors::GREEN));
    rv.edging.push_back(new Line(44, 26, 37, 29, "//", Colors::GREEN));

    // Topic: spaete Bindung, virtual method
    // drawing
    for (auto line : rv.edging)
        line->draw();
}

void drawRoutes() {
    // Topic: Idiom RAII
    class RAIIvector {
    public:
        std::vector<ColoredShape*> routes;
        ~RAIIvector() {
            for (auto line : routes)
                delete line;
            routes.clear();
        }
    };
    RAIIvector rv;

    // define routes
    boardPtr board = Board::board();
    int currentX;
    int currentY;
    int neighborX;
    int neighborY;
    for (auto space : board->spaces()) {
        currentX = space->position().x(); // x of the current space
        currentY = space->position().y(); // y of the current space
        for (auto neighbor : space->neighbors()) {
            // Topic: wichtige Algorithmen der C++-Standardbibliothek
            // find

            // To check if we have already drawn a route to the neighbor
            // we need the index of the element space in space_ array.
            // If this index bigger than the index of neighbor
            // the route is already on the map (it was drawn by the neighbor).
            auto it = std::find(board->spaces().begin(),
                                board->spaces().end(), space);
            // is for sure inside
            int index = static_cast<int>(it - board->spaces().begin());

            if (index < static_cast<int>(neighbor.first)) {
                // x of the neighbor space
                neighborX = board->spaces().at(static_cast<int>(neighbor.first))->position().x();
                // y of the neighbor space
                neighborY = board->spaces().at(static_cast<int>(neighbor.first))->position().y();
                switch (neighbor.second) {
                case WayToReach::ONFOOT:
                    rv.routes.push_back(new Line(currentX, currentY,
                                                 neighborX, neighborY,
                                                 ".", Colors::WHITE));
                    break;
                case WayToReach::SAILING:
                    rv.routes.push_back(new Line(currentX, currentY,
                                                 neighborX, neighborY,
                                                 "~", Colors::BLUE));
                    break;
                case WayToReach::FLYING:
                    rv.routes.push_back(new Line(currentX, currentY,
                                                 neighborX, neighborY,
                                                 ".", Colors::RED));
                    break;
                default:
                    break; // just doesn't draw
                }
            } // else will not draw
        }
    }

    // Topic: spaete Bindung, virtual method
    // drawing
    for (auto line : rv.routes)
        line->draw();
}

void drawSpaces() {
    boardPtr board = Board::board();
    int radius = 3; // radius of the circle, that marks important spaces

    ansiConsole.printText(2, 22, "Legend:", Colors::WHITE);

    // Tanger
    int x = board->spaces().at(static_cast<int>(Spaces::Tanger))->position().x();
    int y = board->spaces().at(static_cast<int>(Spaces::Tanger))->position().y();
    Circle * circle = new Circle(x, y, radius, Colors::MAGENTA);
    circle->draw();
    ansiConsole.printText(x-1, y-1, "1", Colors::WHITE);
    ansiConsole.printText(2, 24, "1.Tanger,", Colors::WHITE);
    delete circle;
    
    // Kairo
    x = board->spaces().at(static_cast<int>(Spaces::Kairo))->position().x();
    y = board->spaces().at(static_cast<int>(Spaces::Kairo))->position().y();
    circle = new Circle(x, y, radius, Colors::MAGENTA);
    circle->draw();
    ansiConsole.printText(x-1, y-1, "2", Colors::WHITE);
    ansiConsole.printText(12, 24, "2.Kairo,", Colors::WHITE);
    delete circle;

    // Kapstadt
    x = board->spaces().at(static_cast<int>(Spaces::Kapstadt))->position().x();
    y = board->spaces().at(static_cast<int>(Spaces::Kapstadt))->position().y();
    circle = new Circle(x, y, radius, Colors::CYAN);
    circle->draw();
    ansiConsole.printText(x-1, y-1, "3", Colors::WHITE);
    ansiConsole.printText(21, 24, "3.Kapstadt,", Colors::WHITE);
    delete circle;

    int legendNum = 4; // number to mark a space at the map
    int rememberLength = 8; // length of the name of the previous space,
                            // 8 for Kapstadt
    int legendX = 21;
    int legendY = 24; // coordinates of other spaces
    for (auto space : board->spaces()) {
        if (space->name() != "Tanger" &&
            space->name() != "Kairo"  &&
            space->name() != "Kapstadt") {
            ansiConsole.printText(space->position().x(), space->position().y(),
                "O", Colors::YELLOW);
            
            ansiConsole.printText(space->position().x()+1, space->position().y()+1,
                to_string(legendNum), Colors::WHITE);

            // every firth falls to the new line
            if ((legendNum % 3 != 1) && (space->name().length() < 11)) {
                legendX += rememberLength + 4; // 4 = number + . + , + _
            }
            else { // changing the line
                legendX = 2;
                ++legendY;
            }

            ansiConsole.printText(legendX, legendY,
                to_string(legendNum)+"."+space->name()+",", Colors::WHITE);

            rememberLength = space->name().length();
            ++legendNum;
        }
    }

    // print a dot at the end of the last printed space
    legendX += rememberLength + 3; // no comma
    ansiConsole.printText(legendX, legendY, ".", Colors::WHITE);
}

void drawPlayers() {
    boardPtr board = Board::board();
    
    if (howManyPlay() != 1) { // if there are other players playing
        // Topic: Value Types
        // names of the players with space numbers will be written from this position,
        // to know who is who if several players are at play
        Position startPosition(50, 28);
        ansiConsole.printText(startPosition.x(), startPosition.y(),
            "Standort:", Colors::WHITE);
        // next line
        startPosition.y(startPosition.y() + 1);
        for (auto player : board->players()) {
            if (!player->lost()) { // there is no place for losers in the legend
                // get position of the player througth his/her current position
                Position position =
                    board->spaces().at(static_cast<int>(player->currentSpace()))->position();
                auto currentState = player->currentState().get();
                auto withDiamondState = player->withDiamondState().get();
                // Topic optional: typeid
                if (typeid(*(currentState)) ==
                    typeid(*(withDiamondState))) { // player has the diamond
                    ansiConsole.printText(position.x(), position.y(), "X", Colors::CYAN);
                    // to the legend
                    ansiConsole.printText(50, 26, "Diamanttraeger=", Colors::WHITE);
                    ansiConsole.printText(65, 26, "X", Colors::CYAN);
                }
                else { // just another player
                    ansiConsole.printText(position.x(), position.y(), "X", Colors::MAGENTA);
                }

                // the player's name with its space number
                ansiConsole.printText(startPosition.x(), startPosition.y(),
                    as_string(player->name()) + ", "
                    + as_string(board->spaces().at(
                    static_cast<int>(player->currentSpace()))->name()), Colors::WHITE);
                // next line
                startPosition.y(startPosition.y() + 1);
            }
        }
        
        // mark the another players
        ansiConsole.printText(50, 25, "andere Spieler=", Colors::WHITE);
        ansiConsole.printText(65, 25, "X", Colors::MAGENTA);
    }
    
    // mark the current player
    Position currPlayerPosition = board->spaces().at(
        static_cast<int>(board->currentPlayer()->currentSpace()))->position();
    ansiConsole.printText(currPlayerPosition.x(), currPlayerPosition.y(),
        "X", Colors::RED);

    // to the legend
    ansiConsole.printText(50,24, "aktuel.Spieler=", Colors::WHITE);
    ansiConsole.printText(65,24, "X", Colors::RED);
}

void drawAfricaNoPlayers() {
    AnsiConsole().clearScreen();
//  coordinateSystem();
    drawEdging();
    drawRoutes();
    drawSpaces();
}

void drawAfrica() {
    drawAfricaNoPlayers();
    drawPlayers();
    // to push the next input line (cursor) forwards
    ansiConsole.printText(1, 33, "");
}
