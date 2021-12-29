#include "Game.h"

int main()
{
    // random
    srand(static_cast<unsigned>(time(NULL)));

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