#include "Game.h"

/*
TODO:
* update and rendering
* create shapes
* move shapes
* positions
* getting mouse positions and inputs
* getting keyboard inputs
* removing shapes
*/

int main()
{
    // game engine class object
    Game game;

    // game loop
    while (game.running()) {

        // update
        game.update();

        // render
        game.render();
    }
    return 0;
}