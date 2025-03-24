
#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include<cstdio.h>
class Game {
    public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height,bool fullscreen); {
        SDL_Init(SDL_INIT_EVERYTHING);
    }
    void update();
    void render();
    void close();
    bool isRunning();
    private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

};
#endif //GAME_H