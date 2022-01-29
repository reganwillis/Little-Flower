@ECHO off
:: Compiling Little Flower

:: Compile modules individually
:: -Wall - turn on most warnings
:: -c - output an object file
:: -I<include path> - specify an include directory
CALL g++ -Wall -c src\Shapes.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c src\Shapes.cpp -o src\Shapes.o -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c src\Game.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c src\Game.cpp -o src\Game.o -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c src\main.cpp -o src\main.o -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c src\UI.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c src\UI.cpp -o src\UI.o -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c Create-Flower\src\CreateFlower.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c Create-Flower\src\CreateFlower.cpp -o Create-Flower\src\CreateFlower.o -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c src\LittleFlower.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c src\LittleFlower.cpp -o src\LittleFlower.o -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c src\Environment.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c src\Environment.cpp -o src\Environment.o -IC:\SFML-gcc\SFML-2.5.1\include

:: Link modules into single executable
:: -L<library path> - specify a lib directory
CALL g++ -Wall src\main.o src\Shapes.o src\UI.o Create-Flower\src\CreateFlower.o src\LittleFlower.o src\Environment.o src\Game.o -o little-flower -LC:\SFML-gcc\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

:: Run executable
CALL little-flower.exe