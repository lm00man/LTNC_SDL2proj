#include "Map.h"

#include <ctime>
#include <bits/locale_classes.h>

#include"textureManager.h"

int arr1[20][20];
void rand_map_gen() {
    srand(time(NULL));
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 20; col++) {
            arr1[row][col] = (rand() % 2 == 0) ? 1 : 0;
        }
    }
}

Map::Map() {
    dirt = textureManager::LoadTexture("assets/dirt.png");
    grass = textureManager::LoadTexture("assets/grass.png");
    water =textureManager::LoadTexture("assets/water.png");

    Map::LoadMap(arr1);
};

void Map::LoadMap(int arr[20][20]) {
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 20; col++) {
            map[row][col] = arr[row][col];
        }
    }
};

