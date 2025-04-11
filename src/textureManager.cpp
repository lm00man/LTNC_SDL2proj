#include"TextureManager.h"
#include"SDL_image.h"

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
SDL_Texture *textureManager::LoadText(const char *path, SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Color color = {255, 255, 255};
    SDL_Surface *tmpsurface = TTF_RenderText_Blended(font, path,color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpsurface);
    int textureWidth = tmpsurface->w;
    int textureHeight = tmpsurface->h;
    SDL_FreeSurface(tmpsurface);
    return texture;
}
