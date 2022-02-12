#ifndef GAME_H
#define GAME_H

#include "..\Create-Flower\src\CreateFlower.h"
#include "LittleFlower.h"
#include "UI.h"
#include "Shapes.h"
#include "Puzzles.h"
#include "MessageBox.h"
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
        sf::Clock clock;
        bool paused = false;
        bool resume = false;

        // window variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;

        // text
        sf::Font font;
        sf::Text littleFlowerText;
        sf::Text uiText;

        // sprites
        sf::Texture background;
        sf::Sprite background_sprite;
        sf::Sprite flower;
        sf::Sprite menu_background;
        sf::Sprite about;
        sf::Sprite reset;
        sf::Sprite mint;

        // event to capture user input
        sf::Event ev;

        // mouse positions in view
        sf::Vector2f mousePosition;

        // create flower
        CreateFlower createFlower;

        // little flower (state)
        LittleFlower little_flower;

        // UI
        UI ui;
        MessageBox* msg_box = new MessageBox();

        // Shapes
        Shapes shapes;
        Shapes::shape shape;

        // puzzles
        Puzzles puzzles;

        // functions
        void initVariables();
        void initWindow();
        void initFonts();
        void initText();
        void initSprites();
        sf::Vector2f getSpriteCenter(sf::Sprite s);
        void newGame();
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
        void updateState();
        void update();
        void renderText(sf::RenderTarget& target);
        void renderSprites(sf::RenderTarget& target);
        void render();
};

#endif