#include "Puzzles.h"
#include <iostream>

void Puzzles::initPuzzles() {
    // start at the first puzzle
    this->state = 0;
}

void Puzzles::initSpots() {
    this->spot_texture.loadFromFile("Images/spot.png");

    for (int i = 0; i < getNumSpots(); ++i) {
        sf::Sprite spot;
        spot.setTexture(this->spot_texture);
        // TODO: center on screen
        spot.setPosition(i * (spot.getGlobalBounds().width + spot.getGlobalBounds().width), 0.f);
        this->spots.push_back(spot);
    }
}

Puzzles::Puzzles() {
    this->initPuzzles();
    this->initSpots();
}

Puzzles::~Puzzles() {}

//void Puzzles::changeState() {}

// TODO
bool Puzzles::checkEquality() {
    // if correct number of shapes are entered, check equality
    if (this->shapes.size() == this->getNumShapes()) {
        
        int prev = -1;
        for (int i = 0; i < this->getNumShapes(); ++i) {
            
            if (prev != -1) {
                if (prev != this->shapes[i].type)
                    return false;
            }
            prev = this->shapes[i].type;
        }

        return true;
    }
    return false;
}

int Puzzles::getState() {
    return this->state;
}

// get number of matching shapes needed to pass
int Puzzles::getNumSpots() {

    if (this->state == 0)
        return this->spots_1;
    else if (this->state == 1)
        return this->spots_2;
    else if (this->state == 2)
        return this->spots_3;
    
    std::cout << "ERROR: Puzzle state not within bounds (" << this->state <<
    "). Returning -1 for Puzzles::getSpots()" << std::endl;
    return -1;
}

// get number of shapes dropped at any state
int Puzzles::getNumShapes() {

    if (this->state == 0)
        return this->puzzle_1;
    else if (this->state == 1)
        return this->puzzle_2;
    else if (this->state == 2)
        return this->puzzle_3;
    else

    std::cout << "ERROR: Puzzle state not within bounds (" << this->state <<
    "). Returning -1 for Puzzles::getNumShapes()" << std::endl;
    return -1;
}

sf::Texture& Puzzles::getSpotTexture() {
    return this->spot_texture;
}

std::vector<sf::Sprite>& Puzzles::getSpots() {
    return this->spots;
}

void Puzzles::setState(int s) {

    if (s >= 0 && s <= 2) {
        this->state = s;
        //changeState();
        initSpots();
    }
    else if (s == 3) {
        // TODO: game over code
        std::cout << "game over" << std::endl;
    }
    else
        std::cout << "ERROR: attempting to set invalid puzzle state (" <<
        s << ")." << std::endl;
}