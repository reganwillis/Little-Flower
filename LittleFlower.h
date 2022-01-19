// keep track of state of little flower (growth)
// TODO: keep track of state of puzzles
#ifndef LITTLE_FLOWER_H
#define LITTLE_FLOWER_H

#include <array>
#include <string>

class LittleFlower {
    private:
        // vars
        std::array<int, 4> possible_states;
        int current_state;

        // functions
        void initState();
    public:
        // constructor and deconstructor
        LittleFlower();
        virtual ~LittleFlower();

        // getters
        const std::array<int, 4> getPossibleStates() const;  // return list of possible states
        const int getState() const;  // return actual state
        // implementation - loop through possible states and act accordingly

        // setters
        void setState(int state);  // accepts member of possible_states array
};

#endif