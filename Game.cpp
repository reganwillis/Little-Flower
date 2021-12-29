#include "Game.h"

void Game::initVariables() {
    // init window as null
    this->window = nullptr;

    // game logic
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
}

void Game::initWindow() {
    // window size (TODO: make window size dynamic to monitor size)
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Little Flower", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

// create an enemy and set its qualities
void Game::initEnemies() {
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(3.f);
}

// constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

// deconstructor
Game::~Game() {
    delete this->window;
}

// return if game loop is running (window is open)
const bool Game::running() const {
    return this->window->isOpen();
}

// spawn enemy and add to list of enemies
void Game::spawnEnemy() {
    // set random enemy position within window, take size into account
    this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f);

    this->enemies.push_back(this->enemy);
}

// event polling (get user input)
void Game::pollEvents() {
    while(this->window->pollEvent(this->ev)) {

        switch(this->ev.type) {
            // close game if x is clicked
            case sf::Event::Closed:
                this->window->close();
                break;
            // close game if ESC key is pressed
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::updateMousePositions() {
    // mouse position relative to window
    //std::cout << "mouse position: " << sf::Mouse::getPosition(*this->window).x << ", " << sf::Mouse::getPosition(*this->window).y << "\n";
    this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

// update enemy spawn timer and calls spawnEnemy
void Game::updateEnemies() {
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= enemySpawnTimerMax) {
            // spawn a new enemy
            this->spawnEnemy();
            // reset enemySpawnTimer if it hits max
            this->enemySpawnTimer = 0.f;
        }
        else {
            // increase enemySpawnTimer by one in each game loop
            this->enemySpawnTimer += 1.f;
        }
    }

    for (size_t i = 0; i < this->enemies.size(); i++) {
        bool deleted = false;

        // move the enemies
        this->enemies[i].move(0.f, 3.f);

        // if enemy is clicked on, erase enemy and gain points
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (this->enemies[i].getGlobalBounds().contains(this->mousePosition)) {
                deleted = true;
                this->points += 10.f;
            }
        }

        // if enemy reaches bottom of screen, erase
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            deleted = true;
        }

        if (deleted)
            this->enemies.erase(this->enemies.begin() + i);
    }
}

void Game::update() {
    this->pollEvents();
    this->updateMousePositions();
    this->updateEnemies();
}

void Game::renderEnemies() {
    for (auto &e : this->enemies) {
        this->window->draw(e);
    }
}

// renders game objects
void Game::render() {
    // clear window
    this->window->clear();

    // draw objects
    this->renderEnemies();

    this->window->display();
}