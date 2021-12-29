#include "Game.h"

void Game::initVariables() {
    // init window as null
    this->window = nullptr;

    // game logic
    this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
}

void Game::initWindow() {
    // window size (TODO: make window size dynamic to monitor size)
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Little Flower", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFonts() {
    this->font.loadFromFile("Fonts/Painterz.ttf");
}

void Game::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);  // default
    this->uiText.setString("no text to display");
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
    this->initFonts();
    this->initText();
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

// return if game has ended
const bool Game::getEndGame() const {
    return this->endGame;
}

// spawn enemy and add it to list of enemies
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
    // mouse position relative to view
    this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Game::updateText() {
    std::stringstream stream;
    stream << "Points: " << this->points << "\n" << "Health: " << this->health;
    this->uiText.setString(stream.str());
}

// update enemy spawn timer, calls spawnEnemy, moves enemies, removes enemies
void Game::updateEnemies() {
    // spawn enemies according to timer
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

    // moving and updating enemies
    for (size_t i = 0; i < this->enemies.size(); i++) {
        //bool deleted = false;

        // move the enemies
        this->enemies[i].move(0.f, 2.f);

        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }
    }

    // if enemy is clicked on, erase enemy and gain points
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (this->mouseHeld == false) {
            this->mouseHeld = true;
            bool deleted = false;

            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosition)) {
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                    this->points += 1;
                    std::cout << this->points << "\n";
                }
            }
        }
    }
    else {
        this->mouseHeld = false;
    }
}

void Game::update() {
    this->pollEvents();

    if (!this->endGame) {
        this->updateMousePositions();
        this->updateText();
        this->updateEnemies();
    }

    // end game if health is 0
    if (this->health <= 0) {
        this->endGame = true;
    }
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target) {
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}

// renders game objects
void Game::render() {
    // clear window
    this->window->clear();

    // draw objects
    this->renderText(*this->window);
    this->renderEnemies(*this->window);

    this->window->display();
}