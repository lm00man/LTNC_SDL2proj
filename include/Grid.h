
#ifndef MAP_H
#define MAP_H
#include <SDL_render.h>
#include <vector>
const int grid = 32;
class Grid {
    public:
    Grid(const char * textsheet, int x, int y);
    ~Grid();
    bool isWalkable(int x, int y);
    void setWalkable(int x, int y, bool val);
    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight, int gridSize, int cellSize, int spacing);
    SDL_Texture *tile;
    int xpos;
    int ypos;
    static const int cols =4;
    static const int rows =4;
    static const int width = 64;
    static const int height = 64;
    static const int spacing = 8;
    std::vector<std::vector<bool>> map;
};

#endif //MAP_H
