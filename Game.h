#ifndef GAME_H
#define GAME_H

#include "Environment.h"
#include "LittleFlower.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/* game engine class */
class Game {
    private:
        // game logic vars
        bool endGame;
        bool mouseHeld;

        // window variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;

        // text
        sf::Font font;
        sf::Text littleFlowerText;

        // sprites
        sf::Sprite flower;

        // event to capture user input
        sf::Event ev;

        // mouse positions in view
        sf::Vector2f mousePosition;

        // little flower (state)
        LittleFlower little_flower;

        // functions
        void initVariables();
        void initWindow();
        void initFonts();
        void initText();
        void initSprites();
    public:
        // constructors and deconstructors
        Game();
        virtual ~Game();

        // getters
        const bool running() const;
        const bool getEndGame() const;

        //functions
        void pollEvents();
        void updateMousePositions();
        void mouseClicks();
        void updateText();
        void updateSprites();
        void updateLittleFlower();
        void update();
        void renderText(sf::RenderTarget& target);
        void renderSprites(sf::RenderTarget& target);
        void render();
};

#endif