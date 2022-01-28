#include "Shapes.H"
#include <iostream>

void Shapes::initVars() {
    this->shape_spawn_timer_max = 250.f;
    this->shape_spawn_timer = this->shape_spawn_timer_max;
    this->max_shapes = 7;
}

void Shapes::initShapeTypes() {
    sf::Texture shape_0_texture;
    shape_0_texture.loadFromFile("Images/water-drop.png");
    sf::Texture shape_1_texture;
    shape_1_texture.loadFromFile("Images/heart-shape.png");
    sf::Texture shape_2_texture;
    shape_2_texture.loadFromFile("Images/crystal-ball.png");
    this->yellow.texture = shape_0_texture;
    this->blue.texture = shape_1_texture;
    this->pink.texture = shape_2_texture;
    this->yellow.type = 0;
    this->blue.type = 1;
    this->pink.type = 2;
}

Shapes::Shapes() {
    this->initVars();
    this->initShapeTypes();
}

Shapes::~Shapes() {}

void Shapes::addShape(sf::Sprite shape) {
    this->shapes.push_back(shape);
}

bool Shapes::updateShapes(float bounds) {
    bool spawn = false;

    if (this->shapes.size() < this->max_shapes) {
        if (this->shape_spawn_timer >= shape_spawn_timer_max) {
            spawn = true;
            this->shape_spawn_timer = 0.f;
        }
        else {
            spawn = false;
            this->shape_spawn_timer += 1.f;
        }
    }

    return spawn;
}

void Shapes::moveShape(sf::Sprite& shape, float offset_x, float offset_y) {

    if (offset_x < 0.f) {
        if (shape.getPosition().x > 0.f)
            shape.move(offset_x, 0.f);
    }
    else if (offset_x > 0.f) {
        if (shape.getPosition().x + shape.getGlobalBounds().width < this->bounds_x)
            shape.move(offset_x, 0.f);
    }
    if (offset_y < 0.f) {
        if (shape.getPosition().y > 0.f)
            shape.move(0.f, offset_y);
    }
    else if (offset_y > 0.f) {
        if (shape.getPosition().y + shape.getGlobalBounds().height < this->bounds_y)
            shape.move(0.f, offset_y);
    }
}

std::vector<sf::Sprite>& Shapes::getShapes() {
    return this->shapes;
}

sf::Texture& Shapes::getTexture() {
    // return random texture
    int num = rand() % 3;

    if (num == 0)
        return this->yellow.texture;
    if (num == 1)
        return this->blue.texture;
    else
        return this->pink.texture;
}

void Shapes::setBounds(float x, float y) {
    this->bounds_x = x;
    this->bounds_y = y;
}