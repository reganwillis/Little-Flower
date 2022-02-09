#include "MessageBox.h"

void MessageBox::initMessageBox(int type) {
    this->box.loadFromFile("./Images/64_64.png");
    this->box_sprite.setTexture(this->box);
    this->sprites.push_back(this->box_sprite);

    if (type == 0) {
        this->okay_button.loadFromFile("./Images/64_64.png");
        this->okay_button_sprite.setTexture(this->okay_button);
        this->okay_button_sprite.setPosition(90, 90);
        this->sprites.push_back(this->okay_button_sprite);
    }
    if (type == 1) {
        this->no_button.loadFromFile("./Images/64_64.png");
        this->no_button_sprite.setTexture(this->no_button);
        this->no_button_sprite.setPosition(90, 90);
        this->sprites.push_back(this->no_button_sprite);

        this->yes_button.loadFromFile("./Images/64_64.png");
        this->yes_button_sprite.setTexture(this->yes_button);
        this->yes_button_sprite.setPosition(160, 90);
        this->sprites.push_back(this->yes_button_sprite);
    }
}

void MessageBox::initText(std::string t) {
    this->font.loadFromFile("Fonts/Anonymous.ttf");
    this->text.setFont(this->font);
    this->text.setCharacterSize(12);
    this->text.setPosition(0, 40);
    this->text.setString(t);
}

MessageBox::MessageBox(std::string t, int type) {

    if (t != "") {
        initText(t);
        initMessageBox(type);
    }
}

MessageBox::~MessageBox() {}

void MessageBox::clear() {
    this->text.setString("");
    //this->box.
    this->sprites.clear();
}

std::vector<sf::Sprite>& MessageBox::getSprites() {
    return this->sprites;
}

sf::Text MessageBox::getText() {
    return this->text;
}