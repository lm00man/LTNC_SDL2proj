#pragma once

#include"game.h"
class textureManager {
    public:
    static SDL_Texture* LoadTexture(const char* path);
    static SDL_Texture* LoadText(const char* path, SDL_Renderer* renderer,TTF_Font* font);
};
