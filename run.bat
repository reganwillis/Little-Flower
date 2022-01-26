@ECHO off
:: Compiling Little Flower

:: Compile modules individually
:: -Wall - turn on most warnings
:: -c - output an object file
:: -I<include path> - specify an include directory
CALL g++ -Wall -c main.cpp -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c UI.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c UI.cpp -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c CreateFlower.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c CreateFlower.cpp -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c LittleFlower.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c LittleFlower.cpp -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c Environment.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c Environment.cpp -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c Game.h -IC:\SFML-gcc\SFML-2.5.1\include
CALL g++ -Wall -c Game.cpp -IC:\SFML-gcc\SFML-2.5.1\include

:: Link modules into single executable
:: -L<library path> - specify a lib directory
CALL g++ -Wall main.o UI.o CreateFlower.o LittleFlower.o Environment.o Game.o -o little-flower -LC:\SFML-gcc\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

:: Run executable
CALL little-flower.exe