#include "Game.h"
#include <random>

int main()
{
    // random
    std::random_device gen;
    std::srand(gen());

    // game engine class object
    Game game;

    // game loop
    while (game.running() && !game.getEndGame()) {

        // update
        game.update();

        // render
        game.render();
    }
    return 0;
}