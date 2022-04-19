# Little Flower
Little Flower Video Game for Windows PC written in C++. Grow a randomly generated flower and mint it on the Tezos blockchain.

## Included Repositories
* [Create-Flower](https://github.com/reganwillis/Create-Flower/tree/v1.0.0)
* [Create-Tezos-NFT](https://github.com/reganwillis/Create-Tezos-NFT/tree/v1.0.0)

## Libraries
* [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)

## Usage
To play the game, download the installer from the [game website](https://reganwillis.github.io/Little-Flower/).

### Development
For developers, clone this repository and navigate into the top level directory. Update the submodules with `git submodule update --init --recursive`. Use the batch script instructions below to create and run the EXE. All libraries will need to be downloaded and all .dll files from SFML/bin need to be added to the project folder.

#### Batch Script
Use the command `run` in the windows command line to run the batch script. This will run the commands to compile files, link them, and run the EXE as shown in the example below:

compile the program:
`g++ -Wall -c src\main.cpp -o src\main.o -IC:\SFML-gcc\SFML-2.5.1\include`
creates: `src\main.o`

link the compiled file to the SFML libraries
`g++ src\main.o -o little-flower -LC:\SFML-gcc\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system`
creates: `little-flower.exe`

run new app:
`little-flower.exe`