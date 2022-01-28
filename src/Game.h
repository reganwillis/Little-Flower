#ifndef GAME_H
#define GAME_H

#include "Environment.h"
#include "LittleFlower.h"
#include "UI.h"
#include "Shapes.h"
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
        bool shapeHeld;
        size_t shapeGrabbed;
        float bounds_x;
        float bounds_y;

        // window variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;

        // text
        sf::Font font;
        sf::Text littleFlowerText;
        sf::Text uiText;

        // sprites
        sf::Sprite flower;
        sf::Sprite shape;
        sf::Sprite about;
        sf::Sprite reset;
        sf::Sprite mint;

        // event to capture user input
        sf::Event ev;

        // mouse positions in view
        sf::Vector2f mousePosition;

        // little flower (state)
        LittleFlower little_flower;

        // UI
        UI ui;

        // Shapes
        Shapes shapes;

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
        void updateUI();
        void updateShapes();
        void update();
        void renderText(sf::RenderTarget& target);
        void renderSprites(sf::RenderTarget& target);
        void render();
};

#endif