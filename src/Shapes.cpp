#include "Shapes.H"

void Shapes::initVars() {
    this->shape_spawn_timer_max = 250.f;
    this->shape_spawn_timer = this->shape_spawn_timer_max;
    this->max_shapes = 10;
}

void Shapes::initShapeTypes() {
    sf::Texture shape_0_texture;
    shape_0_texture.loadFromFile("Images/32_32_yellow.png");
    sf::Texture shape_1_texture;
    shape_1_texture.loadFromFile("Images/32_32_blue.png");
    sf::Texture shape_2_texture;
    shape_2_texture.loadFromFile("Images/32_32.png");
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

bool Shapes::updateShapes() {
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

    for (auto &s : this->shapes) {
        s.move(0.f, 1.f);
    }

    return spawn;
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