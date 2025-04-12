#include"Grid.h"

#include <iostream>

#include "TextureManager.h"
constexpr int screenWidth = 1024;
constexpr int screenHeight = 768;
std::vector<std::pair<int,int>> allCellPos = {{232,104},
{376,104},
{520,104},
{664,104},
{232,248},
{376,248},
{520,248},
{664,248},
{376,392},
{520,392},
{664,392},
{232,536},
{376,536},
{520,536},
{664,536}};
Grid::Grid(const char *textsheet){
    xpos = (screenWidth -totalGridWidth) / 2;
    ypos = (screenHeight -totalGridHeight) / 2;
    tile = TextureManager::LoadTexture(textsheet);
    for( auto vec : map ) {
        std::fill(vec.begin(), vec.end(), 0);
    }
}
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
void Grid::fillCell(std::vector<std::pair<int,int>>& arr) {
    for(int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            arr.emplace_back(Grid::getCellPos(i,j));
        }
    }
}