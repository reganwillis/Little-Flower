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

UI::UI() {
    this->initVars();
    this->initTextures();
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
        if (!this->msgBox->isShowing())
            this->msgBox = new MessageBox(0, true);
    }
    else if (button == 2) {
        this->reset_flower = true;

        if (!this->msgBox->isShowing())
            this->msgBox = new MessageBox(1, true);
    }
    else if (button == 3 && mintingEnabled == true) {

        if (!this->msgBox->isShowing())
            this->msgBox = new MessageBox(2, true);
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