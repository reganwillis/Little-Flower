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
        bool show;
        int type;

        // message box textures
        sf::Texture box;
        sf::Texture okay_button;
        sf::Texture yes_button;
        sf::Texture no_button;

        //vars
        std::vector<sf::Sprite> sprites;
    
        // functions
        void initTextures();
        void initMessageBox();
    public:
        // constructor and deconstructor
        MessageBox(int type=0, bool show=false);  // type: 0-about, 1-reset, 2-mint
        virtual ~MessageBox();

        // functions
        void clear();

        // getters
        std::vector<sf::Sprite>& getSprites();
        bool isShowing();
};

#endif