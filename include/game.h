
#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>



class Game {
    public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height,bool show);
    void handleEvent();
    void update();
    void render();
    void close();
    bool Running(){return isRunning;}
    static SDL_Renderer* renderer;
    private:
        SDL_Window* window;
        bool isRunning;
};
#endif //GAME_H