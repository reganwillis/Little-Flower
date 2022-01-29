#include "Game.h"
#include "Environment.h"
#include "LittleFlower.h"
#include "Shapes.h"

// initialize game logic variables
void Game::initVariables() {
    this->endGame = false;
    this->mouseHeld = false;
    this->shapeHeld = false;
    this->shapeGrabbed = -1;
}

// initialize game window
void Game::initWindow() {
    // 16:9 Ratio = 1920 x 1080 pixels
    // 720p = 1280 x 720
    // 16:9 aspect ratio resolutions: 1024×576, 1152×648, 1280×720, 1366×768, 1600×900, 1920×1080, 2560×1440 and 3840×2160.
    // 320x180, 640x360
    // window size (TODO: make window size dynamic to monitor size)
    // TODO: make content iPhone size and sides black
    this->videoMode.height = 640;
    this->videoMode.width = 360;

    this->window = new sf::RenderWindow(this->videoMode, "Little Flower", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFonts() {
    this->font.loadFromFile("Fonts/37456_TERMINAL.ttf");
}

void Game::initText() {
    //this->littleFlowerText.setFont(this->font);
    //this->littleFlowerText.setCharacterSize(24);
    //this->littleFlowerText.setFillColor(sf::Color::Black);  // default
    //this->littleFlowerText.setString("text failed to render");

    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(12);
    this->uiText.setFillColor(sf::Color::Black);  // default
    //this->uiText.setPosition(this->window->getSize().x / 2) - (this->uiText.getPosition().x / 2), this->window->getSize().y - this->uiText.getPosition().y)
    this->uiText.setPosition(0, 40);
    this->uiText.setString("text failed to render");
}

// initialize sprites - assign texture and set position
void Game::initSprites() {
    this->flower.setTexture(this->little_flower.getTexture());
    this->about.setTexture(this->ui.getAboutTexture());
    this->reset.setTexture(this->ui.getResetTexture());
    this->mint.setTexture(this->ui.getMintTexture());

    this->flower.setPosition(
        (this->window->getSize().x / 2) - (this->flower.getGlobalBounds().width / 2),
        this->window->getSize().y - (this->flower.getGlobalBounds().height + this->about.getGlobalBounds().height)
    );

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

    this->bounds_x = this->window->getSize().x;
    this->bounds_y = this->window->getSize().y - this->reset.getGlobalBounds().height;
    this->shapes.setBounds(this->bounds_x, this->bounds_y);
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

            // display UI text depending on button clicked
            if(this->about.getGlobalBounds().contains(this->mousePosition)) {
                this->ui.setButton(1);
            }
            if(this->reset.getGlobalBounds().contains(this->mousePosition)) {
                this->ui.setButton(2);
            }
            if(this->mint.getGlobalBounds().contains(this->mousePosition)) {
                this->ui.setButton(3);
            }
        }

        float spot_x_center;
        float spot_y_center;

        // drag shapes around
        for (size_t i = 0; i < this->shapes.getShapes().size(); ++i) {
            
            // left mouse button is pressed while in shape
            if (this->shapeHeld == false && shapeGrabbed == -1) {
                if (this->shapes.getShapes()[i].sprite.getGlobalBounds().contains(this->mousePosition) && this->shapes.getShapes()[i].selected != -1) {
                    this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, 64.f); // move shape down past spot
                    this->shapes.getShapes()[i].selected = -1;
                    //this->shapeHeld = false;
                    //shapeGrabbed = -1;
                }
                if (this->shapes.getShapes()[i].sprite.getGlobalBounds().contains(this->mousePosition)) {
                    //this->shapes.getShapes()[i].selected = false;
                    this->shapeHeld = true;
                    this->shapeGrabbed = i;
                }
            }

            if (this->shapeHeld == true) {

                // calculate shape center
                float x_center = this->shapes.getShapes()[i].sprite.getPosition().x + (this->shapes.getShapes()[i].sprite.getGlobalBounds().width / 2);
                float y_center = this->shapes.getShapes()[i].sprite.getPosition().y + (this->shapes.getShapes()[i].sprite.getGlobalBounds().height / 2);


                // TODO: replace shapeHeld with shapeGrabbed

                // only move the shape being held
                if (i == this->shapeGrabbed) {
                    int tmp = 0;
                    // if shape grabbed is already selected, unselect it and grab it
                    if (this->shapes.getShapes()[i].selected != -1) {
                        tmp++;
                        //this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, 64.f); // move shape down past spot
                        //this->shapes.getShapes()[i].selected = -1;
                        //this->shapeHeld = false;
                        //shapeGrabbed = -1;
                    }
                    //else {
                    //    this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, 1.f);
                    //}
                    // place shape on spot
                    for (size_t j = 0; j < this->puzzles.getSpots().size(); ++j) {
                        if (this->puzzles.getSpots()[j].getGlobalBounds().intersects(this->shapes.getShapes()[i].sprite.getGlobalBounds())) {

                            // if there is already a shape in the spot drop it
                            // TODO: more efficient way to drop
                            for (size_t k = 0; k < this->shapes.getShapes().size(); ++k) {
                                if (this->shapes.getShapes()[k].selected == j) {
                                    this->shapes.getShapes()[k].selected = -1;
                                }
                            }
                            this->shapes.getShapes()[i].selected = j;
                        }
                    }
                    if (this->shapes.getShapes()[i].selected != -1) {
                        
                        // if shape was selected move into the spot
                        if (this->puzzles.getSpots()[this->shapes.getShapes()[i].selected].getGlobalBounds().intersects(this->shapes.getShapes()[i].sprite.getGlobalBounds())) {
                            //std::cout << "shape selected" << std::endl;

                            // calculate spot center
                            spot_x_center = this->puzzles.getSpots()[this->shapes.getShapes()[i].selected].getPosition().x + (this->puzzles.getSpots()[this->shapes.getShapes()[i].selected].getGlobalBounds().width / 2);
                            spot_y_center = this->puzzles.getSpots()[this->shapes.getShapes()[i].selected].getPosition().y + (this->puzzles.getSpots()[this->shapes.getShapes()[i].selected].getGlobalBounds().height / 2);

                            if (spot_x_center > x_center)
                                this->shapes.moveShape(this->shapes.getShapes()[i], spot_x_center - x_center, 0.f);
                            if (spot_x_center < x_center)
                                this->shapes.moveShape(this->shapes.getShapes()[i], spot_x_center - x_center, 0.f);
                            if (spot_y_center > y_center)
                                this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, spot_y_center - y_center);
                            if (spot_y_center < y_center)
                                this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, spot_y_center - y_center);
                            //shapeHeld = false;
                            //shapeGrabbed = -1;
                            //this->shapes.getShapes()[i].selected = true;
                        }
                    }
                    else {
                        //this->shapes.getShapes()[i].selected = false;

                        // shape follows mouse position if mouse is still in bounds
                        if (mousePosition.x > (0 + (this->shapes.getShapes()[i].sprite.getGlobalBounds().width / 2)) && 
                            mousePosition.x < (this->bounds_x - (this->shapes.getShapes()[i].sprite.getGlobalBounds().width / 2)) && 
                            mousePosition.y > (0 + (this->shapes.getShapes()[i].sprite.getGlobalBounds().height / 2)) && 
                            mousePosition.y < (this->bounds_y - (this->shapes.getShapes()[i].sprite.getGlobalBounds().height / 2))) {
                            if (x_center > mousePosition.x)
                                this->shapes.moveShape(this->shapes.getShapes()[i], mousePosition.x - x_center, 0.f);
                            if (x_center < mousePosition.x)
                                this->shapes.moveShape(this->shapes.getShapes()[i], mousePosition.x - x_center, 0.f);
                            if (y_center > mousePosition.y)
                                this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, mousePosition.y - y_center);
                            if (y_center < mousePosition.y)
                                this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, mousePosition.y - y_center);
                        }
                        else {
                            shapeHeld = false;
                            shapeGrabbed = -1;
                        }
                    }
                }
                else {
                    if (this->shapes.getShapes()[i].selected == -1)
                        this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, 1.f);
                }
            }
            else {
                this->shapeGrabbed = -1;
                if (this->shapes.getShapes()[i].selected == -1)
                    this->shapes.moveShape(this->shapes.getShapes()[i], 0.f, 1.f);
            }
        }
    }
    else {
        this->mouseHeld = false;
        this->shapeHeld = false;

        // controls shape downward movement is left button is not pressed
        for (auto &s : this->shapes.getShapes()) {
            if (s.selected == -1)
                this->shapes.moveShape(s, 0.f, 1.f);
        }
    }
}

void Game::updateText() {
    //std::stringstream stream;
    //stream << this->little_flower.getTextString();
    //this->littleFlowerText.setString(stream.str());

    std::stringstream uiStream;
    uiStream << this->ui.getTextString();
    this->uiText.setString(uiStream.str());
}

void Game::updateSprites() {
    this->flower.setTexture(this->little_flower.getTexture());
}

// update little flower object by calling little flower update methods
void Game::updateLittleFlower() {
    this->little_flower.updateTexture();
    this->little_flower.updateTextString();
}

void Game::updateUI() {
    if (this->little_flower.getState() == 3) {
        this->ui.setMintingEnabled(true);
    }
    else {
        this->ui.setMintingEnabled(false);
    }
    this->ui.updateUI();
}

void Game::updateShapes() {
    // TODO: ajust bounds when button bar is put in
    float bounds = this->bounds_y;

    if (this->shapes.updateShapes(bounds))
        this->shapes.addShape();


    // TODO: put in its own function
    //if (this->puzzles.checkEquality()) {
    //    this->puzzles.setState(this->puzzles.getState() + 1);
    //}

}

void Game::update() {
    this->pollEvents();

    if (!this->endGame) {
        this->updateMousePositions();
        this->mouseClicks();
        this->updateText();
        this->updateSprites();
        this->updateLittleFlower();
        this->updateUI();
        this->updateShapes();
    }
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->littleFlowerText);
    target.draw(this->uiText);
}

void Game::renderSprites(sf::RenderTarget& target) {
    target.draw(this->flower);

    for (auto &s : this->puzzles.getSpots())
        target.draw(s);

    for (auto &s : this->shapes.getShapes())
        target.draw(s.sprite);
    target.draw(this->about);
    target.draw(this->reset);
    target.draw(this->mint);
}

// renders game objects
void Game::render() {
    // clear window and draw background
    this->window->clear(sf::Color::White);

    // draw objects
    this->renderText(*this->window);
    this->renderSprites(*this->window);

    this->window->display();
}