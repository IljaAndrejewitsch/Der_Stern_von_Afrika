/**
*   \file	PlayerFactory.cpp
*   \author Ilia Budnikov
*/

#include "../include/PlayerFactory.hpp"

PlayerFactory::PlayerFactory()
{
}

PlayerFactory::~PlayerFactory()
{
}

// Topic: Best Practice 14 "do not inline stuff in the class definition"
std::map<Types, PascalString> PlayerFactory::typesDescriptions =
{
    // 3 space bars because of a number before the type name
    // in the place where it will be printed
    {Types::DEFAULT,   PascalString("Standardtyp\n   Startgeld: 300\n   Keine Besonderheiten")},
    {Types::SPORTSMAN, PascalString("Sportler\n   Startgeld: 0\n   +1 Schritt bei jedem Wuerfeln")},
    {Types::SAILOR,    PascalString("Seemann\n   Startgeld: 100\n   Schiffahrten sind kostenlos")},
    {Types::RICHMAN,   PascalString("Reiche\n   Startgeld: 800\n   -1 Schritt bei jedem Wuerfeln")}
};

// factory method
std::shared_ptr<Player> PlayerFactory::createType(PascalString name, Spaces start, Types type) {
    bankPtr bank = Bank::bank(); // to give players a start budget
    banknotesVec banknotes;
    int extraSteps = 0;

    switch (type) {
    case Types::SAILOR:
        banknotes.push_back(bank->giveBanknote(100));
        return std::make_shared<Sailor>(name, banknotes, start);
    case Types::SPORTSMAN:
        extraSteps = 1;
        return std::make_shared<Sportsman>(name, banknotes, extraSteps, start);
    case Types::RICHMAN:
        banknotes.push_back(bank->giveBanknote(500));
        for (int i = 0; i != 3; ++i) // 500 + 300
            banknotes.push_back(bank->giveBanknote(100));
        extraSteps = -1;
        return std::make_shared<RichMan>(name, banknotes, extraSteps, start);
    default:
        // just return the default type in each case different from the above сases,
        // not to interrupt the game due to mismatch (but now the mismatch is impossible)
        for (int i = 0; i != 3; ++i) // 300
            banknotes.push_back(bank->giveBanknote(100));
        return std::make_shared<Player>(name, banknotes, start);
    }
}
