#include"Grid.h"

#include <iostream>

#include "textureManager.h"

Grid::Grid(const char *textsheet, int x, int y) : xpos(x), ypos(y) {
    tile = textureManager::LoadTexture(textsheet);
    for( auto vec : map ) {
        std::fill(vec.begin(), vec.end(), 0);
    }
}
void Grid::setWalkable(int x, int y, bool val) {
};
bool Grid::isWalkable(int x, int y) {
}
void Grid::render(SDL_Renderer* renderer, int screenWidth, int screenHeight, int gridSize, int cellSize, int spacing) {
    int totalGridSize = (gridSize * cellSize) + (gridSize - 1) * spacing;
    xpos = (screenWidth - totalGridSize) / 2;
    ypos = (screenHeight - totalGridSize) / 2;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            SDL_Rect dstRect = {
                xpos + j * (cellSize + spacing), // X position with spacing
                ypos + i * (cellSize + spacing), // Y position with spacing
                cellSize,                            // Cell width
                cellSize                             // Cell height
            };
            SDL_RenderCopy(renderer,tile,nullptr,&dstRect);
        }
    }
}
