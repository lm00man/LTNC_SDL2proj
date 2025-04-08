
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include"game.h"
class GameObject {
public:
    virtual ~GameObject() {} ;
    void virtual render() {};
};
class player : public GameObject {
    public:
    player(char const* textsheet,int x,int y) ;
    ~player() =default;
    void Input_handling(SDL_Event e);
    void render() override;
    void update();
    private:
    SDL_Texture* playerTexture;
    int player_x, player_y;
    SDL_Rect dstRect = {player_x,player_y,64,64};
};

#endif //GAMEOBJECT_H
