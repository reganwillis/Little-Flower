#include "Game.h"
#include "Environment.h"
#include "LittleFlower.h"


void Game::initVariables() {
    // TODO: is a whole function necessary for this
    // game logic
    this->endGame = false;
    this->mouseHeld = false;
}

void Game::initWindow() {
    // window size (TODO: make window size dynamic to monitor size)
    // TODO: make content iPhone size and sides black
    this->videoMode.height = 800;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Little Flower", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initTextures() {
    this->sunBackgroundImg.loadFromFile("Images/background.jpg");
    this->rainBackgroundImg.loadFromFile("Images/stormy-background.jpg");
    // TODO: remove and handle through little flower class
    //this->littleFlowerImg.loadFromFile("Images/little-flower-stage-3.png");
}

void Game::initFonts() {
    this->font.loadFromFile("Fonts/Painterz.ttf");
}

void Game::initText() {
    //this->uiText.setFont(this->font);
    //this->uiText.setCharacterSize(24);
    //this->uiText.setFillColor(sf::Color::White);  // default
    //this->uiText.setString("text failed to render");

    this->littleFlowerText.setFont(this->font);
    this->littleFlowerText.setCharacterSize(24);
    this->littleFlowerText.setFillColor(sf::Color::White);  // default
    this->littleFlowerText.setString("text failed to render");
}

// TODO: rename
// initialize flower sprite - assign texture and set position
void Game::initFlower() {
    //this->flower.setTexture(this->littleFlowerImg);
    this->flower.setTexture(this->little_flower.getTexture());
    //this->flower.setTexture(this->little_flower.getTexture());
    //sf::Texture t;
    //t.loadFromFile("Images/little-flower-stage-3.png");
    //this->flower.setTexture(t);
    //this->flower.setSize(sf::Vector2f(50.f, 50.f));
    //this->flower.setFillColor(sf::Color::Yellow);
    /*this->flower.setPosition(
        (this->window->getSize().x / 2) - (this->flower.getSize().x / 2),
        this->window->getSize().y - this->flower.getSize().y
    );*/
    //this->flower.setPosition(sf::Vector2f(100, 100));
    //this->flower.scale(sf::Vector2f(1, 1.5));
    this->flower.setPosition(
        (this->window->getSize().x / 2) - (this->flower.getGlobalBounds().width / 2),
        this->window->getSize().y - this->flower.getGlobalBounds().height
    );
}




// constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initTextures();
    this->initFonts();
    this->initText();
    this->initFlower();
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
    // TODO: split this function up
        // checking for mouse hold might not be relevant anymore 
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (this->mouseHeld == false) {
            this->mouseHeld = true;

            // grow flower
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

// TODO: rename to track little flower state
    // update little flower?
void Game::trackProgress() {
    // TODO: reorganize, move more into little flower class
    /*
    std::array<int, 4> possible_states = little_flower.getPossibleStates();

    //for (int i = 0; i < possible_states.size() ++i) {}
    if (this->little_flower.getState() == possible_states[0]) {
        std::cout << "STATE: 0\n";
    }
    else if (this->little_flower.getState() == possible_states[1]) {
        std::cout << "STATE: 1\n";
    }
    else if (this->little_flower.getState() == possible_states[2]) {
        std::cout << "STATE: 2\n";
    }
    else if (this->little_flower.getState() == possible_states[3]) {
        std::cout << "STATE: 3 -- GAME COMPLETE\n";
    }
    else {
        std::cout << "ERROR: state logic failure.\n";
    }*/
}

// TODO: rename to be UI specific?
void Game::updateText() {
    //std::stringstream stream;
    //stream << "test";
    //this->uiText.setString(stream.str());

    std::stringstream stream;
    stream << this->little_flower.getTextString();
    this->littleFlowerText.setString(stream.str());
}

// TODO: delete
void Game::updateEnv() {
    if (this->env.getSun()) {
        this->background.setTexture(this->sunBackgroundImg);
    } else {
        this->background.setTexture(this->rainBackgroundImg);
    }
}

void Game::updateFlower() {
    this->little_flower.updateTexture();
    this->little_flower.updateTextString();

    // reflect updates in sprite
    this->flower.setTexture(this->little_flower.getTexture());

    // TODO: end game if flower is fully grown
    //if (this->growth >= 100)
        //this->endGame = true;

    // destroy flower (with enemies)
    /*for (size_t i = 0; i < this->enemies.size(); i++) {
        if (this->enemies[i].getGlobalBounds().intersects(this->flower.getGlobalBounds())) {
            this->enemies.erase(this->enemies.begin() + i);
            this->growth -= 5;
            //this->flower.setSize(sf::Vector2f(this->flower.getSize().x, this->flower.getSize().y - 5));
            this->flower.setPosition(this->flower.getPosition().x, this->flower.getPosition().y + 5);
        }
    }*/
}

void Game::update() {
    this->pollEvents();

    if (!this->endGame) {
        this->updateMousePositions();
        this->mouseClicks();
        this->trackProgress();
        this->updateText();
        this->updateEnv();
        this->updateFlower();
    }
}




void Game::renderText(sf::RenderTarget& target) {
    //target.draw(this->uiText);
    target.draw(this->littleFlowerText);
}

void Game::renderEnv(sf::RenderTarget& target) {
    target.draw(this->background);
}

void Game::renderFlower(sf::RenderTarget& target) {
    target.draw(this->flower);
}

// renders game objects
void Game::render() {
    // clear window and draw background
    this->window->clear();

    // draw objects
    this->renderEnv(*this->window);
    this->renderText(*this->window);
    this->renderFlower(*this->window);

    this->window->display();
}