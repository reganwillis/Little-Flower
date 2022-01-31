#include "Puzzles.h"
#include "Shapes.h"
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

// TODO: rewrite simpler
bool Puzzles::checkEquality(std::vector<Shapes::shape_type>& vec) {
    //for (size_t i = 0; i < this->shapes.getShapes().size(); ++i) {}
    //std::cout << "checking equality" << std::endl;
    std::vector<int> selected_types;
    //std::cout << vec.size() << std::endl;

    for (size_t i = 0; i < vec.size(); ++i) {

        //std::cout << vec[i].selected << " ";

        if (vec[i].selected != -1) {
            //std::cout << vec[i].type << std::endl;
            selected_types.push_back(vec[i].type);
            //if (prev != this->shapes.getShapes()[i].type)
            //    return false;
            //++count;
        }
        //prev = this->shapes.getShapes()[i].type;
    }
    //std::cout << std::endl;
        //std::cout << count << " == " << this->getNumSpots() << std::endl;
    if (selected_types.size() != this->getNumSpots())
        return false;

    for (size_t i = 0; i < selected_types.size() - 1; ++i) {
        if (selected_types[i] != selected_types[i+1]) {
            return false;
        }
    }

    return true;
    /*std::vector<shape_type> selected_shapes;
    for (size_t i = 0; i < this->shapes.getShapes().size(); ++i) {
        if (this->shapes.getShapes()[i].selected != -1) {
            selected_shapes.push_back(this->shapes.getShapes()[i]);
        }
    }
    // if correct number of shapes are entered, check equality
    if (selected_shapes.size() == this->getNumShapes()) {
        
        int prev = -1;
        for (size_t i = 0; i < selected_shapes.size(); ++i) {
            //if (this->shapes.getShapes()[i].selected == j)
            //    this->shapes.getShapes()[i].selected = -1;
        //}
        
        //for (int i = 0; i < this->getNumShapes(); ++i) {
            
            if (prev != -1) {
                if (prev != selected_shapes[i].type)
                    return false;
            }
            prev = selected_shapes.type;
        }

        return true;
    }
    return false;*/
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
    std::cout << "setting new state: " << s << std::endl;

    if (s >= 0 && s <= 2) {
        this->state = s;
        //changeState();
        initSpots();
        //if (s == 1)
        //    this->shapes.setMaxShapes(10);
        //if (s == 2)
        //    this->shapes.setMaxShapes(13);
    }
    else if (s == 3) {
        // TODO: game over code
        this->state = s;
        //this->spots.clear();
        std::cout << "game over" << std::endl;
    }
    else
        std::cout << "ERROR: attempting to set invalid puzzle state (" <<
        s << ")." << std::endl;
}