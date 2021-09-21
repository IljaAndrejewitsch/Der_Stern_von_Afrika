/**
*   \file   CheckInput.cpp
*   \author Ilia Budnikov
*/

#include "../include/CheckInput.hpp"

PascalString checkInput(std::istream & in, const PascalString & inputMessage,
    dataTypeInput dataType, int leftLimit, int rightLimit) {
    println(inputMessage);
    PascalString pString;
    switch (dataType) {
    case dataTypeInput::INT:
        int input;
        // loop continues until the user enters the correct value
        while (true) {
            in >> input;

            // if the previous input was unsuccessful
            if (in.fail()) {
                in.clear(); // return input stream to 'normal' mode.
                in.ignore(numeric_limits<streamsize>::max(), '\n'); // and delete the previous input from the input buffer.
                println("\nHoppla, diese Eingabe ist ungueltig.");
                std::this_thread::sleep_for(std::chrono::seconds(2));
                println("Bitte versuche es erneut:");
            }
            else if ((input < leftLimit) || (input > rightLimit)) {
                in.ignore(numeric_limits<streamsize>::max(), '\n'); // discard unnecessary values
                println("\nHoppla, diese Zahl liegt ausserhalb der akzeptablen Grenzen.");
                std::this_thread::sleep_for(std::chrono::seconds(2));
                println("Bitte versuche eine andere Zahl einzugeben:");
            }
            else { // finally correct
                in.ignore(numeric_limits<streamsize>::max(), '\n'); // clean the buffer

                return PascalString(to_string(input));
            }
        }

        break;
    case dataTypeInput::PASCALSTRING:
        char toRead[256];
        in.getline(toRead, 256); // get all, with whitespaces
        pString.length(strlen(toRead));
        pString.characters(toRead);

        while ((pString.length() < leftLimit) || (pString.length() > rightLimit)) {
            println("\nDie Laenge der Zeichenkette passt leider nicht.");
            std::this_thread::sleep_for(std::chrono::seconds(2));
            println("Bitte versuche eine andere Zeichenkette einzugeben:");
            in >> pString; // overloaded operator >> checks if an input has > 256 symbols
        }

        return pString;

        break;
    case dataTypeInput::MORSE:
        // loop continues until the user enters the correct value
        while (true) {
            char toRead[256];
            in.getline(toRead, 256); // get all, with whitespaces
            pString.length(strlen(toRead));
            pString.characters(toRead);

            // remove all spaces
            PascalString withoutSpaces;
            int length = 0;
            for (int i = 0; i != pString.length(); ++i) {
                if (pString.characters()[i] != ' ') {
                    withoutSpaces.setByIndex(length, pString.characters()[i]);
                    ++length;
                }
            }
            withoutSpaces.length(length);

            // if there was anything other than spaces
            if (withoutSpaces.length() != 0) {
                // searching an incorrect symbol in the input
                int i = 0;
                while (i != withoutSpaces.length() &&
                     ((withoutSpaces.characters()[i] == '.') || (withoutSpaces.characters()[i] == '_'))) {
                    ++i;
                }

                // all the characters were correct
                if (i == withoutSpaces.length()) {
                    return pString;
                }
                else {
                    println("\nHoppla, diese Eingabe ist ungueltig.");
                    println("Ein der falschen Zeichen ist \"", withoutSpaces.characters()[i], "\".");
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    println("Bitte vegiss nicht, die Tabelle zu verwenden,\nund versuche es erneuet:");
                }
            }
            else {
                println("\nDie eingegebene Zeichenkette beinhaltet keine Morsezeichen.");
                std::this_thread::sleep_for(std::chrono::seconds(2));
                println("Versuche es bitte erneut:");
            }
        }
    }

    // as a default return
    return PascalString("");
}
