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
        // window variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;

        // event to capture user input
        sf::Event ev;

        // mouse positions in view
        sf::Vector2f mousePosition;

        // assets
        sf::Font font;

        // UI
        sf::Text uiText;

        // little flower (state)
        LittleFlower little_flower;

        // environment
        Environment env;

        //progress vars
        /*struct Growth {
            bool one;
            bool two;
            bool three;
            bool four;
        } growth;
        struct Puzzle {
            bool one;
            bool two;
            bool three;
        } puzzle;*/

        // game logic
        bool endGame;
        //int growth;
        unsigned points;
        int health;
        bool mouseHeld;

        // game objects
        //sf::RectangleShape flower;
        sf::Texture sunBackgroundImg;
        sf::Texture rainBackgroundImg;
        sf::Sprite background;
        sf::Texture littleFlowerImg;
        sf::Sprite flower;

        // functions
        void initVariables();
        void initWindow();
        void initTextures();
        void initFonts();
        void initText();
        void initFlower();
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
        void trackProgress();
        void updateText();
        void updateEnv();
        void updateFlower();
        void update();
        void renderText(sf::RenderTarget& target);
        void renderEnv(sf::RenderTarget& target);
        void renderFlower(sf::RenderTarget& target);
        void render();
};

#endif