#include "Game.h"
#include <windows.h>
#include <shellapi.h>

// initialize game logic variables
void Game::initVariables() {
    this->endGame = false;
    this->mouseHeld = false;
    this->shapeGrabbed = -1;
}

// initialize game window
void Game::initWindow() {
    this->videoMode.height = 640;
    this->videoMode.width = 360;

    this->window = new sf::RenderWindow(this->videoMode, "Little Flower", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFonts() {
    this->font.loadFromFile("Fonts/37456_TERMINAL.ttf");
}

void Game::initText() {}

// initialize sprites - assign texture and set position
void Game::initSprites() {
    // background
    this->background.loadFromFile("Images/background.png");
    this->background_sprite.setTexture(this->background);

    this->flower.setTexture(this->little_flower.getTexture());
    this->menu_background.setTexture(this->ui.getBackgroundTexture());
    this->about.setTexture(this->ui.getAboutTexture());
    this->reset.setTexture(this->ui.getResetTexture());
    this->mint.setTexture(this->ui.getMintTexture());

    this->flower.setPosition(
        (this->window->getSize().x / 2) - (this->flower.getGlobalBounds().width / 2),
        this->window->getSize().y - (this->flower.getGlobalBounds().height + this->about.getGlobalBounds().height)
    );

    this->menu_background.setPosition(0, this->window->getSize().y - this->about.getGlobalBounds().height);

    this->about.setPosition(
        (this->window->getSize().x * 0.25) - (this->about.getGlobalBounds().width / 2),
        this->window->getSize().y - this->about.getGlobalBounds().height
    );

    this->reset.setPosition(
        (this->window->getSize().x * 0.5) - (this->reset.getGlobalBounds().width / 2),
        this->window->getSize().y - this->reset.getGlobalBounds().height
    );

    this->mint.setPosition(
        (this->window->getSize().x * 0.75) - (this->mint.getGlobalBounds().width / 2),
        this->window->getSize().y - this->mint.getGlobalBounds().height
    );

    // send window bounds to other classes
    this->bounds_x = this->window->getSize().x;
    this->bounds_y = this->window->getSize().y - this->reset.getGlobalBounds().height;
    this->shapes.setBounds(this->bounds_x, this->bounds_y);
    this->puzzles.setWindowBounds(this->bounds_x, this->bounds_y);
}

/*
This function gets the center of a given sprite.
- sf::Sprite s: sprite to get the center of.
Returns: sf::Vector2f of sprite center along x and y axis.
*/
sf::Vector2f Game::getSpriteCenter(sf::Sprite s) {

    return sf::Vector2f(s.getPosition().x + (s.getGlobalBounds().width / 2), s.getPosition().y + (s.getGlobalBounds().height / 2));
}

void Game::newGame() {
    createFlower = CreateFlower();
    little_flower = LittleFlower();
    this->puzzles.setState(0);
    this->shapes.changeState(this->puzzles.getState());
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

            // display UI text depending on button clicked
            if (this->about.getGlobalBounds().contains(this->mousePosition)) {
                this->ui.setButton(1);
            }
            if (this->reset.getGlobalBounds().contains(this->mousePosition)) {
                this->ui.setButton(2);
            }
            if (this->mint.getGlobalBounds().contains(this->mousePosition)) {
                this->ui.setButton(3);
            }

            if( this->msg_box->isShowing()) {
                if (this->msg_box->getSprites().at(1).getGlobalBounds().contains(this->mousePosition)) {
                    this->ui.setButton(0);
                    this->msg_box->clear();
                }

                if (this->msg_box->getSprites().size() > 2) {  // if there is a second button

                    if (this->msg_box->getSprites().at(2).getGlobalBounds().contains(this->mousePosition)) {  // if 2nd button is clicked

                        if (this->ui.getButton() == 2) {
                            // reset action
                            std::cout << "...resetting";
                            // reset flower and states
                            if (this->ui.resetFlower())
                                this->newGame();
                            this->msg_box->clear();
                            this->ui.setButton(0);
                        }

                        if (this->ui.getButton() == 3 && this->ui.getMintingEnabled()) {
                            // mint action
                            std::cout << "...minting";
                            // open dapp
                            ShellExecute(0, 0, "http://localhost:9000/", 0, 0, SW_SHOW);
                            this->msg_box->clear();
                            this->ui.setButton(0);
                        }
                    }
                }
            }
        }

        // drag shapes around
        for (size_t i = 0; i < this->shapes.getShapes().size(); ++i) {
            
            // no shapes are grabbed
            if (shapeGrabbed == -1) {

                // grab shape with mouse
                if (this->shapes.getShapes()[i].sprite.getGlobalBounds().contains(this->mousePosition)) {
                    // if shape grabbed is already selected, unselect it and let it fall
                    if (this->shapes.getShapes()[i].selected != -1) {
                        // move shape down past spot
                        this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, this->shapes.getShapes()[i].sprite.getGlobalBounds().height);
                        this->shapes.getShapes()[i].selected = -1;
                    }
                    else
                        this->shapeGrabbed = i;
                }
                                
                // move all unselected shapes down (left mouse button pressed)
                if (this->shapes.getShapes()[i].selected == -1)
                    this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, 1.f);
            }

            // shapes are grabbed
            if (this->shapeGrabbed != -1) {

                // only move the shape being held
                if (i == this->shapeGrabbed) {
                    sf::Vector2f grabbed_shape_center = this->getSpriteCenter(this->shapes.getShapes()[i].sprite);

                    for (size_t j = 0; j < this->puzzles.getSpots().size(); ++j) {

                        if (this->puzzles.getSpots()[j].getGlobalBounds().intersects(this->shapes.getShapes()[i].sprite.getGlobalBounds()))
                            this->shapes.getShapes()[i].selected = j;  // place shape on spot
                    }

                    if (this->shapes.getShapes()[i].selected != -1) {
                        
                        // if shape was selected move into the spot
                        if (this->puzzles.getSpots()[this->shapes.getShapes()[i].selected].getGlobalBounds().intersects(this->shapes.getShapes()[i].sprite.getGlobalBounds())) {

                            sf::Vector2f selected_spot_center = this->getSpriteCenter(this->puzzles.getSpots()[this->shapes.getShapes()[i].selected]);
                            this->shapes.alignShape(this->shapes.getShapes()[i], selected_spot_center.x, grabbed_shape_center.x, selected_spot_center.y, grabbed_shape_center.y);
                        }
                    }
                    else {
                        // shape follows mouse position
                        if (!(this->shapes.alignShape(this->shapes.getShapes()[i], mousePosition.x, grabbed_shape_center.x, mousePosition.y, grabbed_shape_center.y, true)))
                            shapeGrabbed = -1;
                    }
                }
                else {
                    // move all unselected and ungrabbed shapes down
                    if (this->shapes.getShapes()[i].selected == -1)
                        this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, 1.f);
                }
            }

            // if there is already a shape in the spot (not of the same type) - drop it
            for (size_t j = 0; j < this->shapes.getShapes().size(); ++j) {
                if (this->shapes.getShapes()[j].selected != -1 && this->shapes.getShapes()[i].selected == this->shapes.getShapes()[j].selected && i != j) {
                    // drop current shape
                    int selected_space = this->shapes.getShapes()[j].selected;
                    this->shapes.getShapes()[j].selected = -1;
                    this->shapes.moveShape(this->shapes.getShapes()[j], 0.f, this->shapes.getShapes()[j].sprite.getGlobalBounds().height + 25.f); // move shape down past spot
                    sf::Vector2f dropped_shape_center = this->getSpriteCenter(this->shapes.getShapes()[j].sprite);
                    sf::Mouse::setPosition(sf::Vector2i(dropped_shape_center.x, dropped_shape_center.y), *this->window);
                    shapeGrabbed = j;

                    // select new shape
                    this->shapes.getShapes()[i].selected = selected_space;

                    i = j;  // reset for loop
                }
            }

        }
    }
    else {
        // left mouse button is not pressed
        this->mouseHeld = false;
        this->shapeGrabbed = -1;

        // move all unselected shapes down
        for (auto &s : this->shapes.getShapes()) {
            if (s.selected == -1)
                this->shapes.moveShape(s, 0.f, 1.f);
        }
    }
}

void Game::updateText() {}

void Game::updateSprites() {
    this->flower.setTexture(this->little_flower.getTexture());

    if (this->shapes.updateShapes())
        this->shapes.addShape();
}

// update little flower object by calling little flower update methods
void Game::updateLittleFlower() {
    this->little_flower.updateTexture();
    this->little_flower.updateTextString();
}

void Game::updateUI() {

    if (this->little_flower.getState() == 3)
        this->ui.setMintingEnabled(true);
    else
        this->ui.setMintingEnabled(false);

    this->ui.updateUI();
    if (this->ui.getButton() != 0)
        this->msg_box = this->ui.getMsgBox();
}

void Game::updateState() {
    if (this->puzzles.checkEquality(this->shapes.getShapes())) {
        // pause before switching states
        if (!this->resume) {
            this->paused = true;
            clock.restart();
        }
        if (!this->paused) {

            if (this->puzzles.getState() <= 2)
                this->puzzles.setState(this->puzzles.getState() + 1);
            if (this->puzzles.getState() == 3) {
                // TODO: game over code
                std::cout << "game over" << std::endl;
            }

            // change state in shapes class
            this->shapes.changeState(this->puzzles.getState());

            // grow flower
            int curr_state = this->little_flower.getState();

            if (curr_state <= 2)
                this->little_flower.setState(curr_state + 1);

            this->resume = false;
        }
    }
}

void Game::update() {
    this->pollEvents();

    if (this->paused) {
        if (this->clock.getElapsedTime() >= sf::seconds(1.f)) {
            this->paused = false;
            this->resume = true;
        }
    }

    if (!this->endGame && !this->paused) {
        this->updateMousePositions();
        this->mouseClicks();
        this->updateText();
        this->updateSprites();
        this->updateLittleFlower();
        this->updateUI();
        this->updateState();
    }
}

void Game::renderText(sf::RenderTarget& target) {}

void Game::renderSprites(sf::RenderTarget& target) {
    target.draw(this->background_sprite);
    target.draw(this->flower);

    for (auto &s : this->puzzles.getSpots())
        target.draw(s);

    if (this->paused) {
        for (auto &s : this->shapes.getShapes()) {
            if (s.selected != -1)
                target.draw(s.sprite);
        }
    }
    else {
        for (auto &s : this->shapes.getShapes())
            target.draw(s.sprite);
    }
    target.draw(this->menu_background);
    target.draw(this->about);
    target.draw(this->reset);
    target.draw(this->mint);

    if (this->msg_box->isShowing()) {
        for (auto &s : this->msg_box->getSprites()) {
            target.draw(s);
        }
    }
}

// renders game objects
void Game::render() {
    // clear window and draw background
    this->window->clear(sf::Color::White);

    // draw objects
    this->renderSprites(*this->window);
    this->renderText(*this->window);

    this->window->display();
}