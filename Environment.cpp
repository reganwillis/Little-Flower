#include "Environment.h"

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
