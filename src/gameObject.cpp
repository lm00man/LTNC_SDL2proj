#include "gameObject.h"
#include "textureManager.h"
#include"game.h"

#include "stdlib.h"
player::player(char const *textsheet, int x, int y) : player_x(x),player_y(y) {
    playerTexture = textureManager::LoadTexture(textsheet);
}
void player::update() {
    player_x++;
    player_y++;
    dstRect = { player_x, player_y, 64, 64 };
    if(player_x > 400 - dstRect.w ) {
        player_x = 0;
    }
}
void player::render() {
    SDL_RenderCopy(Game::renderer, playerTexture, nullptr, &dstRect);
}
