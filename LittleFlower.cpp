// LITTLE FLOWER CPP
#include "LittleFlower.h"

void LittleFlower::initState() {
    this->possible_states = {0, 1, 2, 3};
    setState(this->possible_states[0]);
}

void LittleFlower::initTextures() {
    this->little_flower_stage_0_texture.loadFromFile("Images/little-flower-stage-0.jpg");
    this->little_flower_stage_1_texture.loadFromFile("Images/little-flower-stage-1.jpg");
    this->little_flower_stage_2_texture.loadFromFile("Images/little-flower-stage-2.jpg");
    this->little_flower_stage_3_texture.loadFromFile("Images/little-flower-stage-3.jpg");
    this->current_texture = this->little_flower_stage_0_texture;
}

void LittleFlower::initTextStrings() {
    this->state_0 = "STATE: 0";
    this->state_1 = "STATE: 1";
    this->state_2 = "STATE: 2";
    this->state_3 = "GAME COMPLETE";
}

LittleFlower::LittleFlower() {
    this->initState();
    this->initTextures();
    this->initTextStrings();
}

LittleFlower::~LittleFlower() {
    // TODO: is this needed
    setState(this->possible_states[0]);
}

void LittleFlower::updateState() {}

void LittleFlower::updateTexture() {
    if (this->current_state == this->possible_states[0]) {
        //std::cout << "updating to texture 0.\n";
        this->current_texture = this->little_flower_stage_0_texture;
    }
    else if (this->current_state == this->possible_states[1]) {
        //std::cout << "updating to texture 1.\n";
        this->current_texture = this->little_flower_stage_1_texture;
    }
    else if (this->current_state == this->possible_states[2]) {
        //std::cout << "updating to texture 2.\n";
        this->current_texture = this->little_flower_stage_2_texture;
    }
    else if (this->current_state == this->possible_states[3]) {
        //std::cout << "updating to texture 3.\n";
        this->current_texture = this->little_flower_stage_3_texture;
    }
    else {
        std::cout << "ERROR: texture update logic failure.\n";
    }
}

void LittleFlower::updateTextString() {
    if (this->current_state == this->possible_states[0]) {
        this->current_text = this->state_0;
    }
    else if (this->current_state == this->possible_states[1]) {
        this->current_text = this->state_1;
    }
    else if (this->current_state == this->possible_states[2]) {
        this->current_text = this->state_2;
    }
    else if (this->current_state == this->possible_states[3]) {
        this->current_text = this->state_3;
    }
    else {
        std::cout << "ERROR: texture update logic failure.\n";
    }
}

const std::array<int, 4> LittleFlower::getPossibleStates() const {
    //int *ps = possible_states;
    //return ps;
    return this->possible_states;
}

const int LittleFlower::getState() const {
    return this->current_state;
}

sf::Texture& LittleFlower::getTexture() {
    return this->current_texture;
}

std::string LittleFlower::getTextString() {
    return this->current_text;
}

void LittleFlower::setState(int state) {
    this->current_state = state;
}