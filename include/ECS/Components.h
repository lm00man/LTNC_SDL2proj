
#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <SDL_mouse.h>

#include "EntityComponentSystem.h"
class positionsComponent: public Component {
private:
    int xpos= 0;
    int ypos = 0;
public:
    int x() {return xpos;}
    int y(){return ypos;}
    void init() override {
        xpos = 0;
        ypos = 0;
    }
    void setPos(int x, int y) {
        xpos = x;
        ypos = y;
    }

    void update() override {
        xpos++;
        ypos++;
    }
    void render() override {}
    ~positionsComponent() override{};
};


#endif //COMPONENTS_H
