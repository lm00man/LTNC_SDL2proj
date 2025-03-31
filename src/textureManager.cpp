#include"TextureManager.h"

#include<iostream>

SDL_Renderer* Game::renderer = nullptr;
SDL_Texture *textureManager::LoadTexture(const char *path) {
    SDL_Surface *tmpsurface = IMG_Load(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer,tmpsurface);
    if(!tmpsurface) {
        std::cerr<<"IMG_Load ERROR"<<SDL_GetError()<<std::endl;
    }
    SDL_FreeSurface(tmpsurface);
    return texture;
}
