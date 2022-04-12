#include "LittleFlower.h"

void LittleFlower::initState() {
    setState(0);
}

void LittleFlower::initTextures() {
    this->little_flower_stage_0_texture.loadFromFile("Create-Flower/Output/little-flower-stage-0.png");
    this->little_flower_stage_1_texture.loadFromFile("Create-Flower/Output/little-flower-stage-1.png");
    this->little_flower_stage_2_texture.loadFromFile("Create-Flower/Output/little-flower-stage-2.png");
    this->little_flower_stage_3_texture.loadFromFile("Create-Flower/Output/little-flower-stage-3.png");
    this->current_texture = this->little_flower_stage_0_texture;
}

LittleFlower::LittleFlower() {
    this->initState();
    this->initTextures();
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

const int LittleFlower::getState() const {
    return this->current_state;
}

sf::Texture& LittleFlower::getTexture() {
    return this->current_texture;
}

void LittleFlower::setState(int state) {
    this->current_state = state;
}