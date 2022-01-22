#include "CreateFlower.h"
//#include <type_traits>
#include <tr1/memory>

// define basic color palette (must match input image palette)
void CreateFlower::initBasicPalette() {
    this->basic.background = sf::Color(255, 255, 255, 255);
    this->basic.outline = sf::Color(0, 0, 0, 255);
    this->basic.stem = sf::Color(0, 168, 0, 255);
    this->basic.stem_detail = sf::Color(0, 104, 0, 255);
    this->basic.center = sf::Color(160, 82, 45, 255);
    this->basic.center_detail = sf::Color(205, 133, 63, 255);
    this->basic.petals = sf::Color(238, 221, 130, 255);
    this->basic.petals_detail = sf::Color(218, 165, 32, 255);
    this->basic.eye = sf::Color(156, 252, 252, 255);
    this->basic.pupil = sf::Color(0, 72, 252, 255);
    this->basic.petals_background = sf::Color(255, 192, 203, 255);
    this->basic.petals_foreground = sf::Color(226, 106, 106);
}

// initialize flower rarity and palette
void CreateFlower::initFlower() {
    // initialize flower with no rarity
    this->flower.rarity.common = false;
    this->flower.rarity.uncommon = false;
    this->flower.rarity.rare = false;
    this->flower.rarity.ultrarare = false;

    // input flower image has basic color palette
    this->flower.palette = this->basic;

    std::cout << "\nFlower initialized with no rarity and basic palette.";  // debug
}

// get pixel art by randomly chosing one of 4 images
void CreateFlower::setRarity() {
    // choose random number
    int numOfImageChosen = rand() % 1000;
    //numOfImageChosen = 999;  // debug
    std::cout << "\nBase Image: " << numOfImageChosen;  // debug

    // randomly load the image
    if (numOfImageChosen <= 899) {
        this->img_arr[0] = "Input/little-flower-stage-0.png";
        this->img_arr[1] = "Input/little-flower-stage-1.png";
        this->img_arr[2] = "Input/little-flower-stage-2-common.png";
        this->img_arr[3] = "Input/little-flower-stage-3-common.png";
        this->flower.rarity.common = true;
        std::cout << "\ncommon flower created";  // debug
    }
    else if (numOfImageChosen > 899 && numOfImageChosen <= 989) {
        this->img_arr[0] = "Input/little-flower-stage-0.png";
        this->img_arr[1] = "Input/little-flower-stage-1.png";
        this->img_arr[2] = "Input/little-flower-stage-2-uncommon.png";
        this->img_arr[3] = "Input/little-flower-stage-3-uncommon.png";
        this->flower.rarity.uncommon = true;
        std::cout << "\nuncommon flower created";  // debug
    }
    else if (numOfImageChosen > 989 && numOfImageChosen <= 998) {
        this->img_arr[0] = "Input/little-flower-stage-0.png";
        this->img_arr[1] = "Input/little-flower-stage-1.png";
        this->img_arr[2] = "Input/little-flower-stage-2-uncommon.png";
        this->img_arr[3] = "Input/little-flower-stage-3-rare.png";
        this->flower.rarity.rare = true;
        std::cout << "\nrare flower created";  // debug
    }
    else if (numOfImageChosen == 999) {
        this->img_arr[0] = "Input/little-flower-stage-0.png";
        this->img_arr[1] = "Input/little-flower-stage-1.png";
        this->img_arr[2] = "Input/little-flower-stage-2.png";
        this->img_arr[3] = "Input/little-flower-stage-3.png";
        this->flower.rarity.ultrarare = true;
        std::cout << "\nultrarare flower created";  // debug
    }
    else {
        // default
        std::cout << "\nERROR: numOfImageChosen out of bounds: " << numOfImageChosen << ". Loading common image.";
        this->img_arr[0] = "Input/little-flower-stage-0.png";
        this->img_arr[1] = "Input/little-flower-stage-1.png";
        this->img_arr[2] = "Input/little-flower-stage-2-common.png";
        this->img_arr[3] = "Input/little-flower-stage-3-common.png";
        this->flower.rarity.common = true;
        std::cout << "\ndefault common flower created";  // debug
    }
}

// generate random opaque colors using RGB values
sf::Color CreateFlower::generateRandomColor() {
    // choose random number
    int red = rand() % 255;
    int green = rand() % 255;
    int blue = rand() % 255;
    std::cout << "\nColor Palette: (" << red << ", " << green << ", " << blue << ")";  // debug

    return sf::Color(red, green, blue, 255);
}

// create color palette according to art
void CreateFlower::addColorPalette() {
    // fill flower palette with randomly generated colors
    this->flower.palette.stem = generateRandomColor();
    this->flower.palette.stem_detail = generateRandomColor();
    this->flower.palette.center = generateRandomColor();
    this->flower.palette.center_detail = generateRandomColor();
    this->flower.palette.petals = generateRandomColor();
    this->flower.palette.petals_detail = generateRandomColor();
    this->flower.palette.eye = generateRandomColor();
    this->flower.palette.pupil = generateRandomColor();
    this->flower.palette.petals_background = generateRandomColor();
    this->flower.palette.petals_foreground = generateRandomColor();
    std::cout << "\nFlower palette set.";  // debug
}

// change pixel colors of image according to new palette
void CreateFlower::changePixelColorsToPalette() {
    // traverse through all pixels
    for (size_t i = 0; i < this->flower.img.getSize().x; ++i) {
        for (size_t j = 0; j < this->flower.img.getSize().y; ++j) {
            sf::Color currPixelColor = this->flower.img.getPixel(i, j);

            if (this->flower.rarity.ultrarare == true) {
                if (currPixelColor != this->basic.outline && currPixelColor != this->basic.background)
                    this->flower.img.setPixel(i, j, generateRandomColor());
            }
            else {
                // change pixel colors according to new palette
                if (currPixelColor == this->basic.stem)
                    this->flower.img.setPixel(i, j, this->flower.palette.stem);
                else if (currPixelColor == this->basic.stem_detail)
                    this->flower.img.setPixel(i, j, this->flower.palette.stem_detail);
                else if (currPixelColor == this->basic.center)
                    this->flower.img.setPixel(i, j, this->flower.palette.center);
                else if (currPixelColor == this->basic.center_detail)
                    this->flower.img.setPixel(i, j, this->flower.palette.center_detail);
                else if (currPixelColor == this->basic.petals)
                    this->flower.img.setPixel(i, j, this->flower.palette.petals);
                else if (currPixelColor == this->basic.petals_detail)
                    this->flower.img.setPixel(i, j, this->flower.palette.petals_detail);
                else if (currPixelColor == this->basic.eye)
                    this->flower.img.setPixel(i, j, this->flower.palette.eye);
                else if (currPixelColor == this->basic.pupil)
                    this->flower.img.setPixel(i, j, this->flower.palette.pupil);
                else if (currPixelColor == this->basic.petals_background)
                    this->flower.img.setPixel(i, j, this->flower.palette.petals_background);
                else if (currPixelColor == this->basic.petals_foreground)
                    this->flower.img.setPixel(i, j, this->flower.palette.petals_foreground);
            }
        }
    }
}

void CreateFlower::saveImages() {

    for (int i = 0; i < 4; ++i) {
        this->flower.img.loadFromFile(img_arr[i]);
        this->changePixelColorsToPalette();
        this->flower.img.saveToFile(std::string("./Output/little-flower-stage-") + std::to_string(i) + ".png");
    }
}

// constructor
CreateFlower::CreateFlower() {
    this->initBasicPalette();
    this->initFlower();
    this->setRarity();
    this->addColorPalette();
    //this->changePixelColorsToPalette();
    this->saveImages();
}

// deconstructor
CreateFlower::~CreateFlower() {}

sf::Image CreateFlower::getFlowerImg() {
    return this->flower.img;
}