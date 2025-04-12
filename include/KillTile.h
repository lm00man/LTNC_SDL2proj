#pragma once
#include <SDL.h>
#include<ctime>
#include<string>
#include<random>
struct KillTile {
    KillTile( const char* texturePath, int gridX, int gridY, int tileSize, Uint32 lifetimeMs);
    ~KillTile();
    void render(SDL_Renderer* renderer);
    void update();
    SDL_Texture* texture;
    SDL_Rect rect;
    int gridX;
    int gridY;
    Uint32 spawnTime ;
    Uint32 lifeTimeMs;
    bool isExpired() const;
    bool checkCollision(const SDL_Rect& r) const;
    int getX()  const {return  gridX;};
    int getY() const {return gridY;};
    float getRemainingLifetimePercent() const;
    float warningThreshold;
};
class TimedRandomTileManager {
private:
    SDL_Renderer* renderer;
    int tileSize;
    std::string tileTexturePath;
    std::vector<KillTile*> activeTiles;

    int gridWidth;
    int gridHeight;
    int spawnMargin;


    Uint32 minSpawnIntervalMs;
    Uint32 maxSpawnIntervalMs;
    Uint32 nextSpawnTime;
    Uint32 minLifetimeMs;
    Uint32 maxLifetimeMs;
    std::vector<std::pair<int, int>> predeterminedPositions;

    std::mt19937 rng;

    bool** occupied;

    int randomInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }
    void setNextSpawnTime();
    bool findRandomPossibleTiles(int& outX, int& outY);
public:
    TimedRandomTileManager(SDL_Renderer* renderer, int tileSize, const std::string& texturePath,
                          int gridWidth, int gridHeight, int spawnMargin);
    ~TimedRandomTileManager();
    void setSpawnInterval(Uint32 minMs, Uint32 maxMs);
    void setTileLifeTime(Uint32 minMs, Uint32 maxMs);
    void update();
    void render(SDL_Renderer* renderer);
    bool checkCollision(const SDL_Rect& r);
    int getActiveCount() const;
    void setPredeterminedPositions(const std::vector<std::pair<int, int>>& positions);
    void clearAllTiles();
};