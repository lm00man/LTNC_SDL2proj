
#include"game.h"
#include"Gameobject.h"
#include"Grid.h"


#include<iostream>

player* player = nullptr;
Grid* pGrid = nullptr;
SDL_Renderer Game::*renderer = nullptr;
TTF_Font* Game::font = nullptr;
KillTile* ktile = nullptr;
constexpr int width = 1024;
constexpr int height = 768;
Game::Game() :  window(nullptr),state(MENU),selectedItem(0){};
Game::~Game(){};

bool Game::init(const char *title,int width, int height, bool show) {
    int flags = 0;
    if (show) {
        flags = SDL_WINDOW_SHOWN;
    }
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    if (TTF_Init() < 0) return false;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0 ) {

        std::cout << "SDL_Init OK" << std::endl;
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if(window) {
            std::cout << "SDL_CreateWindow OK" << std::endl;
            renderer = SDL_CreateRenderer(window, -1, 0);
            font = TTF_OpenFont("font/Daydream.ttf", 30);
            if(font) {
                std::cout << "TTF_OpenFont OK" << std::endl;
            }
            else {
                std::cout << "TTF_OpenFont ERROR" << std::endl;
            }
            if(renderer) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                std::cout << "SDL_CreateRenderer OK" << SDL_GetError()<<std::endl;
            }
            else {
                std::cerr<<"SDL_CreateRenderer ERROR"<<SDL_GetError()<<std::endl;
            }
        }
        else {
            std::cerr<<"SDL_CreateWindow ERROR"<<SDL_GetError()<<std::endl;
        }

        isRunning = true;
    }
    else {
        std::cerr<<"SDL_Init ERROR"<<SDL_GetError()<<std::endl;
        isRunning = false;
    }
    createMenu();
    player = new class player("assets/meat_ball.png");
    pGrid = new class Grid("assets/Grid_cell.png");

    return true;
}
void Game::createMenu() {
    std::vector<std::string> options = {"Random Bullshit go", "Exit"};
    int ypos = height/2;
    for (const auto& option : options) {
        MenuItem item;
        item.text = option;
        item.rect = {width/2 - 532/2,ypos - 64/2,532,64};
        item.selected = false;
        menuItems.push_back(item);
        ypos += 70;
    }
    menuItems[0].selected = true;
}

void Game::update() {
    if(state == PLAYING) {
        player->update();
        ktile -> createKillTiles(rand() % Grid::rows, rand() % Grid::cols, 3000);
        ktile -> update();
        if (KillTile::checkCollision(player::get_xpos(), player::get_ypos())) {
            std::cout << "Player hit a kill tile!" << std::endl;
            isRunning = false;
        }
    }

}
void Game::renderText(const char* text, int x, int y,bool centered,TTF_Font * font, SDL_Renderer* renderer) {
    SDL_Color color = {255, 255, 255};
    SDL_Surface *tmpsurface = TTF_RenderText_Blended(font, text,color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpsurface);
    int textureWidth = tmpsurface->w;
    int textureHeight = tmpsurface->h;
    SDL_FreeSurface(tmpsurface);
    SDL_Rect rect = {x - textureWidth/2, y- textureHeight/2, textureWidth, textureHeight};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

void Game::render(){
    SDL_RenderClear(renderer);
    if (state == MENU) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        renderText("SDL2_Game", width/2 , 100, true,font,renderer);
        for(auto i = 0, j = 0; i < menuItems.size(); i++) {
            const MenuItem& item = menuItems[i];
            SDL_SetRenderDrawColor(renderer,
                                     item.selected ? 100 : 60,
                                     item.selected ? 100 : 60,
                                     item.selected ? 180 : 100,
                                     255);
            SDL_RenderFillRect(renderer, &item.rect);

            // Draw button border
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &item.rect);

            // Draw button text
            renderText(item.text.c_str(),item.rect.x + item.rect.w / 2,item.rect.y + item.rect.h / 2, true,font,renderer);
        }
    }
    else if(state == PLAYING) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        player->render();
        pGrid -> render(renderer);
        ktile ->render(renderer, 128, 128);
    };
    SDL_RenderPresent(renderer);
}

void Game::handleEvent() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
        std::cout<<"SDL_event Quit";
        break;
        case(SDL_KEYDOWN):
            switch(event.key.keysym.sym) {
                case SDLK_w:
                    if (state == MENU) {
                        menuItems[selectedItem].selected = false;
                        selectedItem = (selectedItem - 1 + menuItems.size()) % menuItems.size();
                        menuItems[selectedItem].selected = true;
                    }
                break;

                case SDLK_s:
                    if (state == MENU) {
                        menuItems[selectedItem].selected = false;
                        selectedItem = (selectedItem + 1) % menuItems.size();
                        menuItems[selectedItem].selected = true;
                    }
                break;

                case SDLK_RETURN:
                case SDLK_SPACE:
                    if (state == MENU) {
                        // Handle menu selection
                        if (selectedItem == 0) {
                            state = PLAYING;
                        }
                        else if (selectedItem == 1) {
                            state = EXIT;
                            isRunning = false;
                        }
                    }
                break;
                case SDLK_ESCAPE:
                    if (state == PLAYING) {
                        state = MENU;
                    } else {
                        state = EXIT;
                        isRunning = false;
                    }
                break;
            }
        if (state == PLAYING) {
            player ->Input_handling(event.key.keysym.sym);
        }
        default:
            //std::cout<<"SDL_event OK";
            break;
    }
}
void Game::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    std::cout << "Game Quit" << std::endl;
}





