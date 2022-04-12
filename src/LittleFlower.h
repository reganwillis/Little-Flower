#ifndef LITTLE_FLOWER_H
#define LITTLE_FLOWER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <array>
#include <iostream>
#include <string>

/*
This class keeps track of the state of Little Flower.
*/
class LittleFlower {
    private:
        // vars
        int current_state;  // 0, 1, 2, or 3

        // little flower stage textures
        sf::Texture current_texture;
        sf::Texture little_flower_stage_0_texture;
        sf::Texture little_flower_stage_1_texture;
        sf::Texture little_flower_stage_2_texture;
        sf::Texture little_flower_stage_3_texture;

        // functions
        void initState();
        void initTextures();
    public:
        // constructor and deconstructor
        LittleFlower();
        virtual ~LittleFlower();

        // functions
        void updateTexture();

        // getters
        const int getState() const;
        sf::Texture& getTexture();

        // setters
        void setState(int state);
};

#endif