#include "Environment.h"

// DELETED CODE FROM GAME.CPP - HANDLE HERE IF NEEDED
/*
// initialize game textures
void Game::initTextures() {
    this->sunBackgroundImg.loadFromFile("Images/background.jpg");
    this->rainBackgroundImg.loadFromFile("Images/stormy-background.jpg");
}

void Game::updateEnv() {
    if (this->env.getSun()) {
        this->background.setTexture(this->sunBackgroundImg);
    } else {
        this->background.setTexture(this->rainBackgroundImg);
    }
}
*/



void Environment::initWeather() {
    this->weather.sun = false;
    this->weather.rain = false;
}

// TODO: keep track of in-game time and set daytime accordingly
void Environment::initTime() {
    this->daytime = true;
}

// constructor
Environment::Environment() {
    this->initWeather();
    this->initTime();
}

// deconstructor
Environment::~Environment() {}

const bool Environment::getSun() const {
    return this->weather.sun;
}

const bool Environment::getRain() const {
    return this->weather.rain;
}

const bool Environment::isDaytime() const {
    return this->daytime;
}
