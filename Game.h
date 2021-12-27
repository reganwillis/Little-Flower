#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/* game engine class */
class Game {
    private:
        // window variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;

        // event to capture user input
        sf::Event ev;

        void initVariables();
        void initWindow();
    public:
        // constructors and deconstructors
        Game();
        virtual ~Game();

        // getters
        const bool running() const;

        //functions
        void pollEvents();
        void update();
        void render();
};

#endif