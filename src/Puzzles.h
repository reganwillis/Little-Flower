#ifndef PUZZLES_H
#define PUZZLES_H

#include "Shapes.h"
#include <vector>

class Puzzles {
    private:
        // vars
        int state;  // 0, 1 or 2

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
        std::vector<Shapes::shape_type> shapes;

        void initPuzzles();
        void initSpots();
    public:
        // constructor and deconstructor
        Puzzles();
        virtual ~Puzzles();

        // functions
        //void changeState();
        //void addShape();
        bool checkEquality();

        // getters
        int getState();
        int getNumSpots();
        int getNumShapes();
        sf::Texture& getSpotTexture();  // TODO: remove
        std::vector<sf::Sprite>& getSpots();

        // setters
        void setState(int s);
};

#endif