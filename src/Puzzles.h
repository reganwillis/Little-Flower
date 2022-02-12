#ifndef PUZZLES_H
#define PUZZLES_H

#include "Shapes.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Puzzles {
    private:
        // vars
        int state;  // 0, 1, 2 or 3
        float windowBoundsX, windowBoundsY;

        const int puzzle_1 = 7;
        const int puzzle_2 = 10;
        const int puzzle_3 = 13;
        
        const int spots_1 = 3;
        const int spots_2 = 4;
        const int spots_3 = 5;

        // spot rendering
        std::vector<sf::Sprite> spots;
        sf::Texture spot_texture;

        // list of chosen shapes
        Shapes shapes;

        void initPuzzles();
        void initSpots();
    public:
        // constructor and deconstructor
        Puzzles();
        virtual ~Puzzles();

        // functions
        bool checkEquality(std::vector<Shapes::shape>& vec);

        // getters
        int getState();
        int getNumSpots();
        int getNumShapes();
        std::vector<sf::Sprite>& getSpots();

        // setters
        void setState(int s);
        void setWindowBounds(float x, float y);
};

#endif