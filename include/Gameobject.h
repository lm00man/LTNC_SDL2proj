
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include"game.h"
#include<vector>
class GameObject {
public:
    virtual ~GameObject() {} ;
    void virtual render() {};
};
class player : public GameObject {
    public:
    player(char const* textsheet) ;
    ~player() =default;
    void Input_handling(SDL_Keycode key);
    void render() override;
    void update();
    static int player_x, player_y;
    static int get_xpos() {return player_x;};
    static int get_ypos() {return player_y;};
    private:
    SDL_Texture* playerTexture;
    SDL_Rect dstRect = {player_x,player_y,64,64};
};
struct KillTile {
    void render(SDL_Renderer* renderer, int width, int height);
    int x, y;
    Uint32 creationTime;
    Uint32 duration;
    KillTile(int gridX, int gridY, Uint32 time, Uint32 activeDuration)
        : x(gridX), y(gridY), creationTime(time), duration(activeDuration){};
    static std::vector<KillTile> tiles;
    void createKillTiles(int x, int y, Uint32 time);
    void update();
    static bool checkCollision(int x, int y);
};


#endif //GAMEOBJECT_H
