
#pragma once
#include <SDL_render.h>
#include <vector>
class Grid {
    public:
    Grid(const char * textsheet);
    ~Grid() = default;
    void render(SDL_Renderer* renderer);
    SDL_Texture *tile;
    int xpos;
    int ypos;
    static const int cols =4;
    static const int rows =4;
    static const int width = 128;
    static const int height = 128;
    static const int spacing = 16;
    int totalGridHeight = height * rows + spacing*(rows-1);
    int totalGridWidth = width * cols + spacing*(cols-1);
    std::vector<std::vector<bool>> map;
    static std::pair<int, int> getCellPos(int row, int col);
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
    void fillCell(std::vector<std::pair<int,int>>& arr);
};

