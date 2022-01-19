#include "Game.h"
#include "Environment.h"
#include "LittleFlower.h"

// initialize game logic variables
void Game::initVariables() {
    this->endGame = false;
    this->mouseHeld = false;
}

// initialize game window
void Game::initWindow() {
    // window size (TODO: make window size dynamic to monitor size)
    // TODO: make content iPhone size and sides black
    this->videoMode.height = 800;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Little Flower", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFonts() {
    this->font.loadFromFile("Fonts/Painterz.ttf");
}

void Game::initText() {
    this->littleFlowerText.setFont(this->font);
    this->littleFlowerText.setCharacterSize(24);
    this->littleFlowerText.setFillColor(sf::Color::White);  // default
    this->littleFlowerText.setString("text failed to render");
}

// initialize sprites - assign texture and set position
void Game::initSprites() {
    this->flower.setTexture(this->little_flower.getTexture());
    this->flower.setPosition(
        (this->window->getSize().x / 2) - (this->flower.getGlobalBounds().width / 2),
        this->window->getSize().y - this->flower.getGlobalBounds().height
    );
}

// constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initSprites();
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

// event polling for game exit
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

            // grow flower if it is clicked on
            if(this->flower.getGlobalBounds().contains(this->mousePosition)) {
                int curr_state = this->little_flower.getState();

                if (curr_state <= 2)
                    this->little_flower.setState(curr_state + 1);
            }
        }
    }
    else {
        this->mouseHeld = false;
    }
}

void Game::updateText() {
    std::stringstream stream;
    stream << this->little_flower.getTextString();
    this->littleFlowerText.setString(stream.str());
}

void Game::updateSprites() {
    this->flower.setTexture(this->little_flower.getTexture());
}

// update little flower object by calling little flower update methods
void Game::updateLittleFlower() {
    this->little_flower.updateTexture();
    this->little_flower.updateTextString();
}

void Game::update() {
    this->pollEvents();

    if (!this->endGame) {
        this->updateMousePositions();
        this->mouseClicks();
        this->updateText();
        this->updateSprites();
        this->updateLittleFlower();
    }
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->littleFlowerText);
}

void Game::renderSprites(sf::RenderTarget& target) {
    target.draw(this->flower);
}

// renders game objects
void Game::render() {
    // clear window and draw background
    this->window->clear();

    // draw objects
    this->renderText(*this->window);
    this->renderSprites(*this->window);

    this->window->display();
}