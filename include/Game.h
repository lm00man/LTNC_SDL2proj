
#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_ttf.h>
#include<bits/stdc++.h>

struct MenuItem {
    std::string text;
    SDL_Rect rect;
    bool selected;
};
enum GameState {
    MENU,
    PLAYING,
    EXIT
};
class Game {
    public:
    Game();
    ~Game();
    bool init(const char* title, int width, int height,bool show);
    void handleEvent();
    void update();
    void render();
    void close();
    bool Running(){return isRunning;}
    static SDL_Renderer* renderer;
    std::vector<MenuItem> menuItems;
    GameState state;
    static TTF_Font *font;
    int selectedItem;
    void createMenu();
    void renderMenu(SDL_Renderer renderer);
    void renderText(const char * string,int x, int y, bool centered,TTF_Font* font,SDL_Renderer* renderer);
    Uint32 gameStartTime;
    float difficultyFactor;
    int score;
    private:
        SDL_Window* window;
        bool isRunning;

};

#endif //GAME_H