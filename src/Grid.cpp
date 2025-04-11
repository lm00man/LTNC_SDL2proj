#include"Grid.h"

#include <iostream>

#include "textureManager.h"
constexpr int screenWidth = 1024;
constexpr int screenHeight = 768;
Grid::Grid(const char *textsheet){
    xpos = (screenWidth -totalGridWidth) / 2;
    ypos = (screenHeight -totalGridHeight) / 2;
    tile = textureManager::LoadTexture(textsheet);
    for( auto vec : map ) {
        std::fill(vec.begin(), vec.end(), 0);
    }
}
void Grid::setWalkable(int x, int y, bool val) {
};
bool Grid::isWalkable(int x, int y) {
};
void Grid::render(SDL_Renderer* renderer) {
    xpos = (screenWidth - totalGridWidth) / 2;
    ypos = (screenHeight - totalGridHeight) / 2;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            SDL_Rect dstRect = {
                xpos + j * (width + spacing),
                ypos + i * (height + spacing),
                width,
                height                                    };
            SDL_RenderCopy(renderer,tile,nullptr,&dstRect);
        }
    }
}
std::pair<int, int> Grid::getCellPos(int row, int col){
    int totalGridWidth = height*rows + spacing*(rows -1);
    int totalGridHeight = width*cols + spacing*(cols -1);
    return std::make_pair((screenWidth-totalGridWidth)/2 + col*(width+spacing), (screenHeight-totalGridHeight)/2 + row*(height+spacing));
}
