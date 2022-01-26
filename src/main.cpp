#include "..\Create-Flower\src\CreateFlower.h"
#include "Game.h"
#include <random>

int main()
{
    // copied from ../Create-Flower/src/main.cpp
    std::random_device gen;
    std::srand(gen());
    CreateFlower createFlower;

    // game engine class object
    Game game;

    // TODO: loading screen
    // game loop
    while (game.running() && !game.getEndGame()) {

        // update
        game.update();

        // render
        game.render();
    }
    return 0;
}