
#pragma once
#include <SDL_render.h>
#include <vector>
class Grid {
    public:
    Grid(const char * textsheet);
    ~Grid();
    bool isWalkable(int x, int y);
    void setWalkable(int x, int y, bool val);
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
};

