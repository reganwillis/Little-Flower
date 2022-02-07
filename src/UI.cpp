#include "UI.h"

void UI::initVars() {
    this->button = 0;
    this->visible = false;
    this->mintingEnabled = false;
    this->reset_flower = false;
}

void UI::initTextures() {
    this->background.loadFromFile("./Images/nav-bar.png");
    this->about.loadFromFile("./Images/about.png");
    this->reset.loadFromFile("./Images/reset.png");
    this->mint_current.loadFromFile("./Images/mint-disabled.png");
    this->mint.loadFromFile("./Images/mint.png");
    this->mint_disabled.loadFromFile("./Images/mint-disabled.png");
}

void UI::initTextStrings() {
    this->about_text = "Little Flower made by Regrow Games <3";
    this->reset_text = "Are you sure you want to start over with a new flower? (Current flower will be lost)";
    this->mint_text = "Mint Little Flower as an NFT on the Tezos blockchain.";
}

UI::UI() {
    this->initVars();
    this->initTextures();
    this->initTextStrings();
}

UI::~UI() {}

void UI::updateUI() {
    //if (this->visible) {}
    //else {}

    if (button == 0) {
        current_text = "";
    }
    else if (button == 1) {
        current_text = about_text;
    }
    else if (button == 2) {
        current_text = reset_text;
        this->reset_flower = true;
    }
    else if (button == 3 && mintingEnabled == true) {
        current_text = mint_text;
    }
    else if (button == 3 && mintingEnabled == false) {
        current_text = "";
    }
    else {
        current_text = "ERROR: button var out of bounds";
    }

    if (this->mintingEnabled) {
        this->mint_current = this->mint;
    }
    else {
        this->mint_current = this->mint_disabled;
    }
}

sf::Texture& UI::getAboutTexture() {
    return this->about;
}

sf::Texture& UI::getResetTexture() {
    return this->reset;
}

sf::Texture& UI::getMintTexture() {
    return this->mint_current;
}

std::string UI::getTextString() {
    return this->current_text;
}

std::string UI::getAboutTextString() {
    return this->about_text;
}

std::string UI::getResetTextString() {
    return this->reset_text;
}

std::string UI::getMintTextString() {
    return this->mint_text;
}

void UI::setButton(int i) {
    button = i;
}

void UI::setVisible(bool b) {
    this->visible = b;
}

void UI::setMintingEnabled(bool b) {
    this->mintingEnabled = b;
}

bool UI::resetFlower() {
    if (this->reset_flower == true) {
        this->button = 0;
        this->reset_flower = false;
        return true;
    }

    return false;
}