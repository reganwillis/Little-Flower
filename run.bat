@ECHO off
:: Compiling Little Flower

CALL g++ -c main.cpp -IC:\SFML-gcc\SFML-2.5.1\include

CALL g++ main.o -o little-flower -LC:\SFML-gcc\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

CALL little-flower.exe