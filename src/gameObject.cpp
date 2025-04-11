#include "gameObject.h"
#include "textureManager.h"
#include"game.h"
#include"Grid.h"

#include "stdlib.h"


constexpr int move_Dist = 16 + 128;
player::player(char const *textsheet) {
    player_x = Grid::getCellPos(0,0).first + 32;
    player_y = Grid::getCellPos(0,0).second + 32;
    playerTexture = textureManager::LoadTexture(textsheet);
}
void player::update() {
    dstRect.x = player_x;
    dstRect.y = player_y;
}
void player::render() {
    SDL_RenderCopy(Game::renderer, playerTexture, nullptr, &dstRect);
}
void player::Input_handling(SDL_Keycode key) {
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
void KillTile::createKillTiles(int x, int y,Uint32 duration) {
    Uint32 currentTime = SDL_GetTicks();
    tiles.emplace_back(x, y, currentTime, duration);
}
void KillTile::update() {
    Uint32 currentTime = SDL_GetTicks();
    tiles.erase(
        std::remove_if(tiles.begin(), tiles.end(), [currentTime](const KillTile& tile) {
            return currentTime - tile.creationTime >= tile.duration;
        }),
        tiles.end()
    );
}
bool KillTile::checkCollision(int x, int y) {
    for (const auto& tile : KillTile::tiles) {
        if (tile.x == x && tile.y == y) {
            return true; // Player collided with a kill tile
        }
    }
    return false;
}

void KillTile::render(SDL_Renderer* renderer, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for kill tiles
    for (const auto& tile : KillTile::tiles) {
        SDL_Rect rect = {tile.x * width, tile.y * height, width, height};
        SDL_RenderFillRect(renderer, &rect);
    }
}



