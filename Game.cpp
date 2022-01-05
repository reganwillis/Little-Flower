#include "Game.h"
#include "Environment.h"

void Game::initVariables() {
    // game logic
    this->endGame = false;
    this->growth = 50;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
}

void Game::initWindow() {
    // window size (TODO: make window size dynamic to monitor size)
    this->videoMode.height = 800;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Little Flower", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initTextures() {
    this->sunBackgroundImg.loadFromFile("Images/background.jpg");
    this->rainBackgroundImg.loadFromFile("Images/stormy-background.jpg");
}

void Game::initFonts() {
    this->font.loadFromFile("Fonts/Painterz.ttf");
}

void Game::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);  // default
    this->uiText.setString("text failed to render");
}

void Game::initFlower() {
    this->flower.setSize(sf::Vector2f(50.f, 50.f));
    this->flower.setFillColor(sf::Color::Yellow);
    this->flower.setPosition(
        (this->window->getSize().x / 2) - (this->flower.getSize().x / 2),
        this->window->getSize().y - this->flower.getSize().y
    );
}

// create an enemy and set its default qualities
void Game::initEnemies() {
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Black);
}

// constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initTextures();
    this->initFonts();
    this->initText();
    this->initFlower();
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

    // randomize enemy type
    int type = rand() % 5;

    switch(type) {
    case 0:
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Green);
        break;
    default:
        break;
    }

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

// mouse position relative to view
void Game::updateMousePositions() {
    this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Game::mouseClicks() {
    // check left mouse button is not held
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (this->mouseHeld == false) {
            this->mouseHeld = true;

            // grow flower
            if(this->flower.getGlobalBounds().contains(this->mousePosition)) {
                this->growth += 10;
                this->flower.setSize(sf::Vector2f(this->flower.getSize().x, this->flower.getSize().y + 10));
                this->flower.setPosition(this->flower.getPosition().x, this->flower.getPosition().y - 10);
            }

            // delete enemies
            bool deleted = false;

            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosition)) {
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        
        }
    }
    else {
        this->mouseHeld = false;
    }
}

void Game::updateText() {
    std::stringstream stream;
    stream << "Growth: " << this->growth;
    this->uiText.setString(stream.str());
}

void Game::updateEnv() {
    if (this->env.getSun()) {
        this->background.setTexture(this->sunBackgroundImg);
    } else {
        this->background.setTexture(this->rainBackgroundImg);
    }
}

void Game::updateFlower() {
    // TODO: end game if flower is fully grown
    //if (this->growth >= 100)
        //this->endGame = true;

    // destroy flower (with enemies)
    for (size_t i = 0; i < this->enemies.size(); i++) {
        if (this->enemies[i].getGlobalBounds().intersects(this->flower.getGlobalBounds())) {
            this->enemies.erase(this->enemies.begin() + i);
            this->growth -= 5;
            this->flower.setSize(sf::Vector2f(this->flower.getSize().x, this->flower.getSize().y - 5));
            this->flower.setPosition(this->flower.getPosition().x, this->flower.getPosition().y + 5);
        }
    }
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

        // move the enemies
        this->enemies[i].move(0.f, 2.f);

        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
        }
    }
}

void Game::update() {
    this->pollEvents();

    if (!this->endGame) {
        this->updateMousePositions();
        this->mouseClicks();
        this->updateText();
        this->updateEnv();
        this->updateFlower();
        this->updateEnemies();
    }
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Game::renderEnv(sf::RenderTarget& target) {
    target.draw(this->background);
}

void Game::renderFlower(sf::RenderTarget& target) {
    target.draw(this->flower);
}

void Game::renderEnemies(sf::RenderTarget& target) {
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}

// renders game objects
void Game::render() {
    // clear window and draw background
    this->window->clear();

    // draw objects
    this->renderEnv(*this->window);
    this->renderText(*this->window);
    this->renderFlower(*this->window);
    this->renderEnemies(*this->window);

    this->window->display();
}