#include "gameObject.h"
#include "textureManager.h"
#include"game.h"

#include "stdlib.h"


GameObject::GameObject(const char *texsheet, int x,int y) {
    objTexture = textureManager::LoadTexture(texsheet);
    xpos = x;
    ypos = y;
    srcRect.h = 64;
    srcRect.w = 64;
    srcRect.x = 0;
    srcRect.y = 0;

    dstRect.h =64;
    dstRect.w =64;
}
void GameObject::Game_obj_update() {

    xpos+= 5;

    dstRect.x = xpos;
    dstRect.y = ypos;
    if(xpos > 400 - srcRect.w ) {
        srcRect.w = dstRect.w*2;
        xpos = 0;
    }
};
void GameObject::Game_obj_render() {
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &dstRect);
};
