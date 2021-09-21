#!/bin/bash
#Topic: Best Practice 2 "always use tools to support the building process" (this build.sh file)

CPP_SRC_PATH=${CPP_SRC_PATH:-src/}
CPP_INC_PATH=${CPP_INC_PATH:-include/}
#Topic: Fehler und Warnings
#Topic: Best Practice 1 "always compile with high warning level, and treat warnings as errors"
CPPFLAGS="-Wall -Wextra -Wpedantic -Werror -O0 -std=c++17 -Wno-unused-variable"
echo "Compiling cpp-files..."
# Alle cpp-Dateien wurden zusammen uebersetzt.
# Dabei werden alle notwendigen Schritte
# (Quelltext -Praeprozessor-> .ii -Compiler-> Assembly, .s
# -Assembler-> Maschinencode, .o -Linker-> ausfuehrbare Datei, .out)
# vom Compiler uebernommen.
# Es ist natuerlich moeglich, alle Dateien einzeln auch zu uebersetzen.
# Um die Uebersichtlichkeit und Einfachheit der build-Datei zu behalten,
# wurde die oben erwaehnte Entscheidung getroffen.
# Topic: Komponenten
# Topic: getrennte Uebersetzung
clang++ ${CPPFLAGS} -o DerSternVonAfrika.out ${CPP_SRC_PATH}main.cpp ${CPP_SRC_PATH}AnsiConsole.cpp ${CPP_SRC_PATH}Bank.cpp ${CPP_SRC_PATH}Banknote.cpp ${CPP_SRC_PATH}Board.cpp ${CPP_SRC_PATH}CheckInput.cpp ${CPP_SRC_PATH}Circle.cpp ${CPP_SRC_PATH}ColoredShape.cpp ${CPP_SRC_PATH}DefaultState.cpp ${CPP_SRC_PATH}Line.cpp ${CPP_SRC_PATH}MorseCodeParser.cpp ${CPP_SRC_PATH}PascalString.cpp ${CPP_SRC_PATH}Player.cpp ${CPP_SRC_PATH}PlayerFactory.cpp ${CPP_SRC_PATH}RichMan.cpp ${CPP_SRC_PATH}RichManDefaultState.cpp ${CPP_SRC_PATH}RobberState.cpp ${CPP_SRC_PATH}Sailor.cpp ${CPP_SRC_PATH}Space.cpp ${CPP_SRC_PATH}Sportsman.cpp ${CPP_SRC_PATH}WithDiamondState.cpp

#Topic: Best Practice 24 "make sure headers compile by itself"
echo "Compiling hpp-files..."
clang++ -c ${CPP_INC_PATH}AnsiConsole.hpp
clang++ -c ${CPP_INC_PATH}Bank.hpp
clang++ -c ${CPP_INC_PATH}Banknote.hpp
clang++ -c ${CPP_INC_PATH}Board.hpp
clang++ -c ${CPP_INC_PATH}CheckInput.hpp
clang++ -c ${CPP_INC_PATH}Circle.hpp
clang++ -c ${CPP_INC_PATH}ColoredShape.hpp
clang++ -c ${CPP_INC_PATH}DefaultState.hpp
clang++ -c ${CPP_INC_PATH}Line.hpp
clang++ -c ${CPP_INC_PATH}MorseCodeParser.hpp
clang++ -c ${CPP_INC_PATH}PascalString.hpp
clang++ -c ${CPP_INC_PATH}Player.hpp
clang++ -c ${CPP_INC_PATH}PlayerFactory.hpp
clang++ -c ${CPP_INC_PATH}Position.hpp
echo "Almost done..."
clang++ -c ${CPP_INC_PATH}println.hpp
clang++ -c ${CPP_INC_PATH}RichMan.hpp
clang++ -c ${CPP_INC_PATH}RichManDefaultState.hpp
clang++ -c ${CPP_INC_PATH}RobberState.hpp
clang++ -c ${CPP_INC_PATH}Sailor.hpp
clang++ -c ${CPP_INC_PATH}Space.hpp
clang++ -c ${CPP_INC_PATH}Sportsman.hpp
clang++ -c ${CPP_INC_PATH}State.hpp
clang++ -c ${CPP_INC_PATH}WithDiamondState.hpp

# removing gch-files to make a new build possible
rm ${CPP_INC_PATH}AnsiConsole.hpp.gch
rm ${CPP_INC_PATH}Bank.hpp.gch
rm ${CPP_INC_PATH}Banknote.hpp.gch
rm ${CPP_INC_PATH}Board.hpp.gch
rm ${CPP_INC_PATH}CheckInput.hpp.gch
rm ${CPP_INC_PATH}Circle.hpp.gch
rm ${CPP_INC_PATH}ColoredShape.hpp.gch
rm ${CPP_INC_PATH}DefaultState.hpp.gch
rm ${CPP_INC_PATH}Line.hpp.gch
rm ${CPP_INC_PATH}MorseCodeParser.hpp.gch
rm ${CPP_INC_PATH}PascalString.hpp.gch
rm ${CPP_INC_PATH}Player.hpp.gch
rm ${CPP_INC_PATH}PlayerFactory.hpp.gch
rm ${CPP_INC_PATH}Position.hpp.gch
rm ${CPP_INC_PATH}println.hpp.gch
rm ${CPP_INC_PATH}RichMan.hpp.gch
rm ${CPP_INC_PATH}RichManDefaultState.hpp.gch
rm ${CPP_INC_PATH}RobberState.hpp.gch
rm ${CPP_INC_PATH}Sailor.hpp.gch
rm ${CPP_INC_PATH}Space.hpp.gch
rm ${CPP_INC_PATH}Sportsman.hpp.gch
rm ${CPP_INC_PATH}State.hpp.gch
rm ${CPP_INC_PATH}WithDiamondState.hpp.gch
echo "Ready!"
