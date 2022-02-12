#ifndef SHAPES_H
#define SHAPES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

class Shapes {
    private:
        // vars
        float shape_spawn_timer, shape_spawn_timer_max;
        unsigned int max_shapes;
        float bounds_x, bounds_y;

        // functions
        void initVars();
        void initShapeTypes();
    public:
        // constructor and deconstructor
        Shapes();
        virtual ~Shapes();

        // individual shape
        struct shape {
            int type;  // (0, 1 or 2)
            sf::Texture texture;
            sf::Sprite sprite;
            int selected;
        } type_1, type_2, type_3;

        std::vector<shape> shapes;

        // functions
        void addShape();
        bool updateShapes();
        void moveShape(shape& shape, float offset_x, float offset_y);
        bool alignShape(shape& shape, float new_x, float curr_x, float new_y, float curr_y, bool movingToMouse=false);

        // getters
        std::vector<shape>& getShapes();

        // setters
        void setBounds(float x, float y);
        void changeState(int s);
};

#endif