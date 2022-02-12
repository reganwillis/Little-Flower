#include "Puzzles.h"

void Puzzles::initPuzzles() {
    // start at the first puzzle
    this->state = 0;
}

void Puzzles::initSpots() {
    this->spot_texture.loadFromFile("Images/spot.png");

    this->spots.clear();  // clear out old spots before adding new ones

    float chunks = 1.f/(getNumSpots() + 1);
    float multiplier = 0.f;

    for (int i = 0; i < getNumSpots(); ++i) {
        sf::Sprite spot;
        spot.setTexture(this->spot_texture);

        // center spots on screen
        multiplier = multiplier + chunks;
        spot.setPosition((this->windowBoundsX * multiplier) - (spot.getGlobalBounds().width / 2), 10.f);
        this->spots.push_back(spot);
    }
}

Puzzles::Puzzles() {
    this->initPuzzles();
}

Puzzles::~Puzzles() {}

bool Puzzles::checkEquality(std::vector<Shapes::shape>& vec) {
    if (this->getNumSpots() == 0)
        return false;

    std::vector<int> selected_types;

    for (size_t i = 0; i < vec.size(); ++i) {

        if (vec[i].selected != -1)
            selected_types.push_back(vec[i].type);
    }

    if (selected_types.size() != this->getNumSpots())
        return false;

    for (size_t i = 0; i < selected_types.size() - 1; ++i) {
        if (selected_types[i] != selected_types[i+1])
            return false;
    }

    return true;
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
    else if (this->state == 3)
        return 0;
    
    std::cout << "ERROR: Puzzle state not within bounds (" << this->state <<
    "). Returning -1 for Puzzles::getNumSpots()" << std::endl;
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
    else if (this->state == 3)
        return 0;

    std::cout << "ERROR: Puzzle state not within bounds (" << this->state <<
    "). Returning -1 for Puzzles::getNumShapes()" << std::endl;
    return -1;
}

std::vector<sf::Sprite>& Puzzles::getSpots() {
    return this->spots;
}

void Puzzles::setState(int s) {

    if (s >= 0 && s <= 3) {
        this->state = s;
        initSpots();
    }
    else
        std::cout << "ERROR: attempting to set invalid puzzle state (" << s << ")." << std::endl;
}

void Puzzles::setWindowBounds(float x, float y) {
    this->windowBoundsX = x;
    this->windowBoundsY = y;
    this->initSpots();  // call initSpots after bounds have been set
}