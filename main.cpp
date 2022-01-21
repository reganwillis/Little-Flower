#include "CreateFlower.h"
#include "Game.h"

int main()
{
    // random
    srand(static_cast<unsigned>(time(NULL)));

    // get random flower (rarity & colors)
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