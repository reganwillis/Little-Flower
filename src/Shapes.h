#ifndef SHAPES_H
#define SHAPES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

// TODO:
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

        // functions
        void initVars();
        void initShapeTypes();
    public:
        // constructor and deconstructor
        Shapes();
        virtual ~Shapes();

        // shape types
        struct shape_type {
            int type;  // (0, 1 or 2)
            sf::Texture texture;
            sf::Sprite sprite;
        } type_1, type_2, type_3;

        std::vector<shape_type> shapes;

        // functions
        void addShape();
        bool updateShapes(float bounds);
        void moveShape(shape_type& shape, float offset_x, float offset_y);

        // getters
        std::vector<shape_type>& getShapes();

        // setters
        void setBounds(float x, float y);
};

#endif