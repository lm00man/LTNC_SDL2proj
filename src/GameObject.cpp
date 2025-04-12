#include "gameObject.h"
#include "TextureManager.h"
#include"game.h"
#include"Grid.h"

#include "stdlib.h"


constexpr int move_Dist = 16 + 128;
Player::Player(char const *textsheet) {
    player_x = Grid::getCellPos(0,0).first + 32;
    player_y = Grid::getCellPos(0,0).second + 32;
    playerTexture = TextureManager::LoadTexture(textsheet);
}
void Player::update() {
    dstRect.x = player_x;
    dstRect.y = player_y;
}
void Player::render() {
    SDL_RenderCopy(Game::renderer, playerTexture, nullptr, &dstRect);
}
void Player::Input_handling(SDL_Keycode key) {
    switch (key) {
        case SDLK_w:
            if(player_y > Grid::getCellPos(0,0).second + 32) player_y -= move_Dist;
        break;
        case SDLK_s:
            if(player_y < Grid::getCellPos(3,3).second +32) player_y += move_Dist;
        break;
        case SDLK_a:
            if(player_x > Grid::getCellPos(0,0).first +32) player_x -= move_Dist;
        break;
        case SDLK_d:
            if(player_x < Grid::getCellPos(3,3).first +32) player_x += move_Dist;
        break;
        default:
            break;
    }
}



