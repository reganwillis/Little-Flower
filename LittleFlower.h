// keep track of state of little flower (growth)
// TODO: keep track of state of puzzles
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

// TODO:
// public: get sf texture matching state
// private: set sf texture according to current_state
// public: get sf::Text of text matching state
// private: set sf::Text of text according to current_state
// where to initialize text?


class LittleFlower {
    private:
        // vars
        std::array<int, 4> possible_states;
        int current_state;

        // little flower stage textures
        sf::Texture current_texture;
        sf::Texture little_flower_stage_0_texture;
        sf::Texture little_flower_stage_1_texture;
        sf::Texture little_flower_stage_2_texture;
        sf::Texture little_flower_stage_3_texture;

        // little flower state text
        std::string current_text;
        std::string state_0;
        std::string state_1;
        std::string state_2;
        std::string state_3;

        // functions
        void initState();
        void initTextures();
        void initTextStrings();
    public:
        // constructor and deconstructor
        LittleFlower();
        virtual ~LittleFlower();

        // functions
        void updateState();
        void updateTexture();
        void updateTextString();

        // getters
        const std::array<int, 4> getPossibleStates() const;  // needed??
        const int getState() const;  // return actual state
        // implementation - loop through possible states and act accordingly
        sf::Texture& getTexture();
        std::string getTextString();

        // setters
        void setState(int state);  // accepts member of possible_states array
};

#endif