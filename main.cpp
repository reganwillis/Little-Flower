#include "CreateFlower.h"
#include "Game.h"
#include <random>

int main()
{
    // random
    // https://docs.microsoft.com/en-us/cpp/standard-library/random-device-class?redirectedfrom=MSDN&view=msvc-170
    std::random_device gen;
    std::srand(gen());

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