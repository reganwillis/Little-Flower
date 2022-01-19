// LITTLE FLOWER CPP
#include "LittleFlower.h"

void LittleFlower::initState() {
    this->possible_states = {0, 1, 2, 3};
    setState(this->possible_states[0]);
}

LittleFlower::LittleFlower() {
    this->initState();
}

LittleFlower::~LittleFlower() {
    // TODO: is this needed
    setState(this->possible_states[0]);
}

const std::array<int, 4> LittleFlower::getPossibleStates() const {
    //int *ps = possible_states;
    //return ps;
    return this->possible_states;
}

const int LittleFlower::getState() const {
    return this->current_state;
}

void LittleFlower::setState(int state) {
    this->current_state = state;
}