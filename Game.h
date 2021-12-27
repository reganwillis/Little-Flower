#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>
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

        // mouse positions
        sf::Vector2i mousePosition;

        // game logic
        int points;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        unsigned int maxEnemies;

        // game objects
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        void initVariables();
        void initWindow();
        void initEnemies();
    public:
        // constructors and deconstructors
        Game();
        virtual ~Game();

        // getters
        const bool running() const;

        //functions
        void spawnEnemy();
        void pollEvents();
        void updateMousePositions();
        void updateEnemies();
        void update();
        void renderEnemies();
        void render();
};

#endif