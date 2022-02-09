#include "UI.h"

// TODO: reorganize repeated functions

void UI::initVars() {
    this->button = 0;
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
    if (this->mintingEnabled) {
        this->mint_current = this->mint;
    }
    else {
        this->mint_current = this->mint_disabled;
    }

    if (button == 0) {
        this->msgBox->clear();
    }
    else if (button == 1) {
        this->msgBox = new MessageBox(about_text);
    }
    else if (button == 2) {
        this->reset_flower = true;

        if (this->msgBox->getSprites().empty()) {  // TODO: is there a better way to prevent spawning new message boxes constantly
            this->msgBox->clear();
            this->msgBox = new MessageBox(reset_text, 1);
        }
    }
    else if (button == 3 && mintingEnabled == true) {

        if (this->msgBox->getSprites().empty()) {
            this->msgBox->clear();
            this->msgBox = new MessageBox(mint_text, 1);
        }
    }
    else if (button == 3 && mintingEnabled == false) {
        this->msgBox->clear();
        this->button = 0;
    }
    else {
        std::cout << "ERROR: button var out of bounds\n";
        this->msgBox->clear();
        this->button = 0;
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

int UI::getButton() {
    return button;
}

bool UI::getMintingEnabled() {
    return mintingEnabled;
}

MessageBox* UI::getMsgBox() {
    return this->msgBox;
}

void UI::setButton(int i) {
    button = i;
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