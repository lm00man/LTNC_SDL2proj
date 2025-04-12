#pragma once

#include <SDL2/SDL.h>
#include <ctime>
#include<random>
#include<vector>
class GameObject {
public:
    virtual ~GameObject() {} ;
    void virtual render() {};
};
class Player : public GameObject {
    public:
    Player(char const* textsheet) ;
    ~Player() =default;
    void Input_handling(SDL_Keycode key);
    void render() override;
    void update();
    int player_x, player_y;
    SDL_Rect dstRect = {player_x,player_y,64,64};
    private:
    SDL_Texture* playerTexture;
};
