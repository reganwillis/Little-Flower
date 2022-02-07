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

    // get random shape type
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
    shape.sprite.setPosition(static_cast<float>(rand() % static_cast<int>(this->bounds_x - shape.sprite.getGlobalBounds().width)), 0.f - shape.sprite.getGlobalBounds().height);

    this->shapes.push_back(shape);
}

bool Shapes::updateShapes() {

    if (this->shapes.size() < this->max_shapes) {
        if (this->shape_spawn_timer >= shape_spawn_timer_max) {
            this->shape_spawn_timer = 0.f;
            return true;
        }
        this->shape_spawn_timer += 1.f;

        return false;
    }

    return false;
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
- bool movingToMouse: true if input sprite is moving to a mouse position (default=false)
Returns bool: if shape was aligned return true
*/
bool Shapes::alignShape(shape_type& shape, float new_x, float curr_x, float new_y, float curr_y, bool movingToMouse) {
    
    if (movingToMouse) {
        // do not move shape to mouse if mouse is not within bounds
        if (!(new_x > (shape.sprite.getGlobalBounds().width / 2) && 
            new_x < (this->bounds_x - (shape.sprite.getGlobalBounds().width / 2)) && 
            new_y > (shape.sprite.getGlobalBounds().height / 2) && 
            new_y < (this->bounds_y - (shape.sprite.getGlobalBounds().height / 2)))) {
                return false;
            }
    }

    // align shape to new position
    if (new_x > curr_x)
        moveShape(shape, new_x - curr_x, 0.f);
    if (new_x < curr_x)
        moveShape(shape, new_x - curr_x, 0.f);
    if (new_y > curr_y)
        moveShape(shape, 0.f, new_y - curr_y);
    if (new_y < curr_y)
        moveShape(shape, 0.f, new_y - curr_y);

    return true;
}

std::vector<Shapes::shape_type>& Shapes::getShapes() {
    return this->shapes;
}

void Shapes::setBounds(float x, float y) {
    this->bounds_x = x;
    this->bounds_y = y;
}

void Shapes::changeState(int s) {

    if (s == 0)
        this->max_shapes = 7;
    if (s == 1)
        this->max_shapes = 10;
    if (s == 2)
        this->max_shapes = 13;
    if (s == 3)
        this->max_shapes = 0;
    this->shape_spawn_timer = 0.f;  // reset spawn timer
    this->shapes.clear();
}