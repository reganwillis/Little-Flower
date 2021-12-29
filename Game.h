#ifndef GAME_H
#define GAME_H

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

        // game logic
        bool endGame;
        unsigned points;
        int health;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        unsigned int maxEnemies;
        bool mouseHeld;

        // game objects
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        void initVariables();
        void initWindow();
        void initFonts();
        void initText();
        void initEnemies();
    public:
        // constructors and deconstructors
        Game();
        virtual ~Game();

        // getters
        const bool running() const;
        const bool getEndGame() const;

        //functions
        void spawnEnemy();
        void pollEvents();
        void updateMousePositions();
        void updateText();
        void updateEnemies();
        void update();
        void renderText(sf::RenderTarget& target);
        void renderEnemies(sf::RenderTarget& target);
        void render();
};

#endif