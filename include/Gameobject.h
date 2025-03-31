
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include"game.h"
class GameObject {
public:
    GameObject(const char* texsheet,int x,int y);
    ~GameObject();
    void Game_obj_render();
    void Game_obj_update();

private:
    int xpos, ypos;
    SDL_Texture* objTexture;
    SDL_Rect srcRect, dstRect;

};

#endif //GAMEOBJECT_H
