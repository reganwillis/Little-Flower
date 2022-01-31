#include "Shapes.H"
#include <iostream>

void Shapes::initVars() {
    this->shape_spawn_timer_max = 150.f;
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
    this->type_1.texture = shape_0_texture;
    this->type_2.texture = shape_1_texture;
    this->type_3.texture = shape_2_texture;
    this->type_1.type = 0;
    this->type_2.type = 1;
    this->type_3.type = 2;
}

Shapes::Shapes() {
    this->initVars();
    this->initShapeTypes();
}

Shapes::~Shapes() {}

void Shapes::addShape() {
    shape_type shape;

    shape.selected = -1;

    // get random texture
    int num = rand() % 3;

    if (num == 0) {
        shape.type = type_1.type;
        shape.sprite.setTexture(type_1.texture);
    }
    else if (num == 1) {
        shape.type = type_2.type;
        shape.sprite.setTexture(type_2.texture);
    }
    else if (num == 2) {
        shape.type = type_3.type;
        shape.sprite.setTexture(type_3.texture);
    }
    else {
        std::cout << "Error: Invalid random number for shape type and texture (" << num << ")." << std::endl;
    }

    // get random position
    shape.sprite.setPosition(static_cast<float>(rand() % static_cast<int>(this->bounds_x - shape.sprite.getGlobalBounds().width)), 0.f);

    this->shapes.push_back(shape);
}

bool Shapes::updateShapes(float bounds) {
    bool spawn = false;
    //std::cout << "update shapes max_shapes: " << this->max_shapes << std::endl;
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

void Shapes::moveShape(shape_type& shape, float offset_x, float offset_y) {

    if (offset_x < 0.f) {
        if (shape.sprite.getPosition().x > 0.f)
            shape.sprite.move(offset_x, 0.f);
    }
    else if (offset_x > 0.f) {
        if (shape.sprite.getPosition().x + shape.sprite.getGlobalBounds().width < this->bounds_x)
            shape.sprite.move(offset_x, 0.f);
    }
    if (offset_y < 0.f) {
        if (shape.sprite.getPosition().y > 0.f)
            shape.sprite.move(0.f, offset_y);
    }
    else if (offset_y > 0.f) {
        if (shape.sprite.getPosition().y + shape.sprite.getGlobalBounds().height < this->bounds_y)
            shape.sprite.move(0.f, offset_y);
    }
}

/*
This function moves the input sprite from it's current x and y 
position to the new x and y position.
- shape_type& shape: input sprite
- float new_x: new input sprite x position
- float curr_x: current input sprite x position
- float new_y: new input sprite y position
- float curr_y: current input sprite y position
*/
void Shapes::alignShape(shape_type& shape, float new_x, float curr_x, float new_y, float curr_y) {
    if (new_x > curr_x)
        moveShape(shape, new_x - curr_x, 0.f);
    if (new_x < curr_x)
        moveShape(shape, new_x - curr_x, 0.f);
    if (new_y > curr_y)
        moveShape(shape, 0.f, new_y - curr_y);
    if (new_y < curr_y)
        moveShape(shape, 0.f, new_y - curr_y);
}

void Shapes::clearShapes() {
    this->shapes.clear();
}

std::vector<Shapes::shape_type>& Shapes::getShapes() {
    return this->shapes;
}

void Shapes::setBounds(float x, float y) {
    this->bounds_x = x;
    this->bounds_y = y;
}

void Shapes::setMaxShapes(unsigned int i) {
    //std::cout << this->max_shapes << " ";
    this->max_shapes = i;
    //std::cout << this->max_shapes;
}