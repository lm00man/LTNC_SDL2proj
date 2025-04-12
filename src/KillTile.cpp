#include<KillTile.h>
#include"TextureManager.h"
#include"Grid.h"
KillTile::KillTile
( const char* texturePath,int gridX, int gridY, int tileSize, Uint32 lifetimeMs) {
    this->gridX = gridX;
    this->gridY = gridY;
    rect.x = gridX ;
    rect.y = gridY ;
    rect.w = tileSize;
    rect.h = tileSize;

    texture = TextureManager::LoadTexture(texturePath);
    spawnTime = SDL_GetTicks();
    this->lifeTimeMs = lifetimeMs;
    warningThreshold = 0.7f; // Start warning at 70% of lifetime
}
KillTile::~KillTile() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}
bool KillTile::isExpired() const {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 age = currentTime - spawnTime;
    return age >= lifeTimeMs;
}
bool KillTile::checkCollision(const SDL_Rect& playerRect) const {
    return SDL_HasIntersection(&rect, &playerRect);
}
float KillTile::getRemainingLifetimePercent() const {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 age = currentTime - spawnTime;
    if (age >= lifeTimeMs) return 0.0f;
    return 1.0f - (float)age / lifeTimeMs;
}
void KillTile::render(SDL_Renderer* renderer) {
    float lifePercent = getRemainingLifetimePercent();

    // Set alpha based on remaining life
    if (texture) {
        // Full alpha until warning threshold
        Uint8 alpha = 255;

        // If we're in warning phase, make the tile blink
        if (lifePercent < warningThreshold) {
            float warningPhasePercent = lifePercent / warningThreshold;

            // Create a pulsing effect that gets faster as lifetime decreases
            float pulseSpeed = 3.0f + (1.0f - warningPhasePercent) * 10.0f;
            float pulseValue = 0.5f + 0.5f * sin(SDL_GetTicks() * 0.01f * pulseSpeed);

            // Set alpha based on pulse value
            alpha = (Uint8)(128 + 127 * pulseValue);
        }

        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    } else {
        // Fallback - render a red rectangle if texture failed to load
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        // Add a lifetime indicator (a shrinking inner rectangle)
        int shrinkAmount = (int)(rect.w * (1.0f - lifePercent) * 0.5f);
        SDL_Rect innerRect = {
            rect.x + shrinkAmount,
            rect.y + shrinkAmount,
            rect.w - 2 * shrinkAmount,
            rect.h - 2 * shrinkAmount
        };
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &innerRect);
    }
}
void TimedRandomTileManager::setNextSpawnTime() {
    nextSpawnTime = SDL_GetTicks() + randomInt(minSpawnIntervalMs, maxSpawnIntervalMs);
}
void TimedRandomTileManager::setPredeterminedPositions(const std::vector<std::pair<int, int> > &positions) {
    this -> predeterminedPositions = positions;
}

bool TimedRandomTileManager::findRandomPossibleTiles(int& outX, int& outY) {
    // If we have predetermined positions, use those
    if (!predeterminedPositions.empty()) {
        // Filter out occupied positions
        std::vector<std::pair<int, int>> availablePositions;

        for (const auto& pos : predeterminedPositions) {
            int x = pos.first;
            int y = pos.second;

            // Make sure position is within grid bounds
            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                // Check if position is unoccupied
                if (!occupied[x][y]) {
                    availablePositions.push_back(pos);
                }
            }
        }

        // If no predetermined positions are available, return false
        if (availablePositions.empty()) {
            return false;
        }

        // Pick a random available position
        int randomIndex = randomInt(0, availablePositions.size() - 1);
        outX = availablePositions[randomIndex].first;
        outY = availablePositions[randomIndex].second;
        return true;
    }
    else {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
}
TimedRandomTileManager::TimedRandomTileManager
(SDL_Renderer *renderer, int tileSize, const std::string &texturePath, int gridWidth, int gridHeight, int spawnMargin = 1){
    this->renderer = renderer;
    this->tileSize = tileSize;
    tileTexturePath = texturePath;
    this->gridWidth = gridWidth;
    this->gridHeight = gridHeight;
    this->spawnMargin = spawnMargin;

    // Default timing parameters
    minSpawnIntervalMs = 1000;  // 1 second
    maxSpawnIntervalMs = 3000;  // 3 seconds
    minLifetimeMs = 2000;       // 2 seconds
    maxLifetimeMs = 5000;       // 5 seconds

    // Initialize RNG
    rng.seed(static_cast<unsigned int>(time(nullptr)));

    // Set initial spawn time
    setNextSpawnTime();

    // Initialize occupancy grid
    occupied = new bool*[gridWidth];
    for (int x = 0; x < gridWidth; x++) {
        occupied[x] = new bool[gridHeight];
        for (int y = 0; y < gridHeight; y++) {
            occupied[x][y] = false;
        }
    }
}
TimedRandomTileManager::~TimedRandomTileManager() {
        // Clean up active tiles
        for (auto tile : activeTiles) {
            delete tile;
        }
        activeTiles.clear();

        // Free occupancy grid
        for (int x = 0; x < gridWidth; x++) {
            delete[] occupied[x];
        }
        delete[] occupied;
    }

    // Set spawn interval range
void TimedRandomTileManager::setSpawnInterval(Uint32 minMs, Uint32 maxMs) {
    minSpawnIntervalMs = minMs;
    maxSpawnIntervalMs = maxMs;
}

// Set tile lifetime range
void TimedRandomTileManager::setTileLifeTime(Uint32 minMs, Uint32 maxMs) {
    minLifetimeMs = minMs;
    maxLifetimeMs = maxMs;
}

// Update the manager - spawn new tiles and remove expired ones
void TimedRandomTileManager::update() {
    Uint32 currentTime = SDL_GetTicks();

    // Check for expired tiles
    for (auto it = activeTiles.begin(); it != activeTiles.end();) {
        if ((*it)->isExpired()) {
            // Mark position as unoccupied
            int x = (*it)->getX();
            int y = (*it)->getY();
            occupied[x][y] = false;

            // Delete tile and remove from list
            delete *it;
            it = activeTiles.erase(it);
        } else {
            ++it;
        }
    }

    // Check if it's time to spawn a new tile
    if (currentTime >= nextSpawnTime) {
        int x, y;
        if (findRandomPossibleTiles(x, y)) {
            // Determine lifetime for this tile
            Uint32 lifetime = randomInt(minLifetimeMs, maxLifetimeMs);

            // Create and add the tile
            KillTile* newTile = new KillTile( tileTexturePath.c_str(),
                                                     x, y, tileSize, lifetime);
            activeTiles.push_back(newTile);

            // Mark position as occupied
            occupied[x][y] = true;
        }

        // Set time for next spawn
        setNextSpawnTime();
    }
}

// Check if player collides with any active tile
bool TimedRandomTileManager::checkCollision(const SDL_Rect& playerRect) {
    for (auto tile : activeTiles) {
        if (tile->checkCollision(playerRect)) {
            return true;
        }
    }
    return false;
}

// Render all active tiles
void TimedRandomTileManager::render(SDL_Renderer* renderer) {
    for (auto tile : activeTiles) {
        tile->render(renderer);
    }
}

// Get active tile count
int TimedRandomTileManager::getActiveCount() const {
    return activeTiles.size();
}

// Clear all active tiles
void TimedRandomTileManager::clearAllTiles() {
    for (auto tile : activeTiles) {
        // Mark position as unoccupied
        int x = tile->getX();
        int y = tile->getY();
        occupied[x][y] = false;

        delete tile;
    }
    activeTiles.clear();
}
