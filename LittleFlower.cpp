#include "LittleFlower.h"

void LittleFlower::initState() {
    setState(0);
}

void LittleFlower::initTextures() {
    this->little_flower_stage_0_texture.loadFromFile("Output/little-flower-stage-0.png");
    this->little_flower_stage_1_texture.loadFromFile("Output/little-flower-stage-1.png");
    this->little_flower_stage_2_texture.loadFromFile("Output/little-flower-stage-2.png");
    this->little_flower_stage_3_texture.loadFromFile("Output/little-flower-stage-3.png");
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
    setState(0);
}

void LittleFlower::updateTexture() {
    if (this->current_state == 0)
        this->current_texture = this->little_flower_stage_0_texture;
    else if (this->current_state == 1)
        this->current_texture = this->little_flower_stage_1_texture;
    else if (this->current_state == 2)
        this->current_texture = this->little_flower_stage_2_texture;
    else if (this->current_state == 3)
        this->current_texture = this->little_flower_stage_3_texture;
    else
        std::cout << "ERROR: texture update logic failure.\n";
}

void LittleFlower::updateTextString() {
    if (this->current_state == 0) {
        this->current_text = this->state_0;
    }
    else if (this->current_state == 1) {
        this->current_text = this->state_1;
    }
    else if (this->current_state == 2) {
        this->current_text = this->state_2;
    }
    else if (this->current_state == 3) {
        this->current_text = this->state_3;
    }
    else {
        std::cout << "ERROR: texture update logic failure.\n";
    }
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