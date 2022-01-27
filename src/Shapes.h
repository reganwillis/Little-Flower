#ifndef SHAPES_H
#define SHAPES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

// TODO:
// speed up how fast the mouse can more with shape following
// function for comparing chosen shapes called from Game::updateShapes()
// if shape (and mouse?) intersects with circle put it there
// check equality of chosen shapes and use to progress game

class Shapes {
    private:
        // vars
        float shape_spawn_timer;
        float shape_spawn_timer_max;
        unsigned int max_shapes;
        float bounds_x;
        float bounds_y;

        std::vector<sf::Sprite> shapes;

        // shape types
        struct shape_type {
            int type;  // (0, 1 or 2)
            sf::Texture texture;
        } yellow, blue, pink;

        // functions
        void initVars();
        void initShapeTypes();
    public:
        // constructor and deconstructor
        Shapes();
        virtual ~Shapes();

        // functions
        void addShape(sf::Sprite shape);
        bool updateShapes(float bounds);
        void moveShape(sf::Sprite& shape, float offset_x, float offset_y);

        // getters
        std::vector<sf::Sprite>& getShapes();
        sf::Texture& getTexture();

        // setters
        void setBounds(float x, float y);
};

#endif