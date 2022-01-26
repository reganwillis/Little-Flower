#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <string>

// TODO: set background
// TODO: space out buttons
// TODO: reset button resets flower

class UI {
    private:
        // vars
        int button;  // (0, 1, 2, 3)

        // UI visibility
        bool visible;
        bool mintingEnabled;

        // UI textures
        sf::Texture background;
        sf::Texture about;
        sf::Texture reset;
        sf::Texture mint_current;
        sf::Texture mint;
        sf::Texture mint_disabled;

        // UI text
        std::string current_text;
        std::string about_text;
        std::string reset_text;
        std::string mint_text;

        // funcitons
        void initVars();
        void initTextures();
        void initTextStrings();
    public:
        // constructor and deconstructor
        UI();
        virtual ~UI();

        // functions
        void updateUI();

        // getters
        sf::Texture& getAboutTexture();
        sf::Texture& getResetTexture();
        sf::Texture& getMintTexture();
        std::string getTextString();
        std::string getAboutTextString();
        std::string getResetTextString();
        std::string getMintTextString();

        // setters
        void setButton(int i);
        void setVisible(bool b);
        void setMintingEnabled(bool b);
};

#endif