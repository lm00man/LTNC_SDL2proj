
#include<SDL.h>
#include"game.h"
Game *game = nullptr;

int main(int argc, char *argv[]) {
    game = new Game();
    game->init("Game_1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1024,768, true);
    const int fps = 60;
    const int frameDelay = 1000 / fps;

    while(game->Running()) {
        Uint32 startTicks = SDL_GetTicks();

        game->handleEvent();
        game->update();
        game->render();

        Uint32 frameTime = SDL_GetTicks() - startTicks;
        if(frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->close();
    delete game;
    return 0;
}