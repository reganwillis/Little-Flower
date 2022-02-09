#include "MessageBox.h"

void MessageBox::initTextures() {

    if (this->type == 0) {
        this->box.loadFromFile("./Images/about_message_box.png");
        this->okay_button.loadFromFile("./Images/okay_button.png");
    }
    else if (this->type == 1) {
        this->box.loadFromFile("./Images/reset_message_box.png");
        this->yes_button.loadFromFile("./Images/yes_button.png");
        this->no_button.loadFromFile("./Images/no_button.png");
    }
    else if (this->type == 2) {
        this->box.loadFromFile("./Images/mint_message_box.png");
        this->yes_button.loadFromFile("./Images/yes_button.png");
        this->no_button.loadFromFile("./Images/no_button.png");
    }
}

void MessageBox::initMessageBox() {

    if (type == 0) {  // about message box
        sf::Sprite message_box(this->box);
        sf::Sprite okay_button_sprite(this->okay_button);

        message_box.setScale(0.5f, 0.5f);

        message_box.setPosition(360/2 - message_box.getGlobalBounds().width/2, 200);
        okay_button_sprite.setPosition((360/2) - (okay_button_sprite.getGlobalBounds().width / 2), 280);
        
        this->sprites.push_back(message_box);
        this->sprites.push_back(okay_button_sprite);
    }
    else if (type == 1 || type == 2) {  // reset message box or mint message box
        sf::Sprite message_box(this->box);
        sf::Sprite yes_button_sprite(this->yes_button);
        sf::Sprite no_button_sprite(this->no_button);

        message_box.setScale(0.5f, 0.5f);

        message_box.setPosition(360/2 - message_box.getGlobalBounds().width/2, 200);
        yes_button_sprite.setPosition((360/2) - (yes_button_sprite.getGlobalBounds().width + 5), 280);
        no_button_sprite.setPosition((360/2) + (5), 280);
        
        this->sprites.push_back(message_box);
        this->sprites.push_back(no_button_sprite);
        this->sprites.push_back(yes_button_sprite);
    }
}

MessageBox::MessageBox(int type, bool show) {
    this->show = show;
    this->type = type;

    if (this->show) {
        initTextures();
        initMessageBox();
    }
}

MessageBox::~MessageBox() {}

void MessageBox::clear() {
    this->show = false;
    this->sprites.clear();
}

std::vector<sf::Sprite>& MessageBox::getSprites() {
    return this->sprites;
}

bool MessageBox::isShowing() {
    return this->show;
}