#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class MessageBox {
    private:
        //vars
        sf::Font font;
        sf::Text text;
        std::vector<sf::Sprite> sprites;
        
        // message box textures & sprites
        sf::Texture box;
        sf::Sprite box_sprite;
        sf::Texture okay_button;
        sf::Texture yes_button;
        sf::Texture no_button;
        sf::Sprite okay_button_sprite;
        sf::Sprite yes_button_sprite;
        sf::Sprite no_button_sprite;

        // functions
        void initMessageBox(int type);
        void initText(std::string t);
    public:
        // constructor and deconstructor
        MessageBox(std::string t="", int type=0);  // type: 0-okay, 1-yes or no
        virtual ~MessageBox();

        // functions
        void clear();

        // getters
        std::vector<sf::Sprite>& getSprites();
        sf::Text getText();
};

#endif