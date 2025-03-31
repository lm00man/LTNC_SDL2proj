
#include"game.h"
#include"textureManager.h"
#include"Gameobject.h"

#include <cstdio>
#include<iostream>

Game::Game(){};
Game::~Game(){};

GameObject* player;

SDL_Renderer Game::*renderer = nullptr;

int count = 0;

void Game::init(const char *title, int xpos, int ypos,int width, int height, bool show) {
    window = nullptr;
    renderer = nullptr;
    int flags = 0;
    if (show) {
        flags = SDL_WINDOW_SHOWN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0 ) {
        std::cout << "SDL_Init OK" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window) {
            std::cout << "SDL_CreateWindow OK" << std::endl;
            renderer = SDL_CreateRenderer(window, -1, 0);
            if(renderer) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                std::cout << "SDL_CreateRenderer OK" << SDL_GetError()<<std::endl;
            }
            else {
                std::cerr<<"SDL_CreateRenderer ERROR"<<SDL_GetError()<<std::endl;
            }
        }
        else {
            std::cerr<<"SDL_CreateWindow ERROR"<<SDL_GetError()<<std::endl;
        }

        isRunning = true;
    }
    else {
        std::cerr<<"SDL_Init ERROR"<<SDL_GetError()<<std::endl;
        isRunning = false;
    }
    player = new GameObject("assets/Sprite-0001.png",32,32);
}
void Game::update() {
    player->Game_obj_update();
}
void Game::render() {
    SDL_RenderClear(renderer);
    player->Game_obj_render();
    SDL_RenderPresent(renderer);
}
void Game::handleEvent() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
        std::cout<<"SDL_event Quit";
        break;
        default:
            //std::cout<<"SDL_event OK";
            break;
    }
}
void Game::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game Quit" << std::endl;
}



