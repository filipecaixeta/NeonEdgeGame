#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "TileMap.h"
#include "Logger.h"

TileMap::TileMap(std::string file, TileSet* tileSet, SDL_Point pos, bool origemEmbaixo) {
    position = pos;
    Load(file);
    SetTileSet(tileSet);
    origem = origemEmbaixo;
}

TileMap::~TileMap() {
    delete tileSet;
}

void TileMap::Load(std::string file) {
    std::ifstream f;
    std::string num = "";
    f.open(file.c_str(), std::ios::in);
    if (f.is_open()) {
        getline(f, num, ',');
        mapWidth = atoi(num.c_str());
        getline(f, num, ',');
        mapHeight = atoi(num.c_str());
        getline(f, num, ',');
        mapDepth = atoi(num.c_str());
        while (getline(f, num, ',')) {
            tileMatrix.push_back(atoi(num.c_str())-1);
        }
    } else {
        std::cout<< "f.open: unable to open file: " << file.c_str();
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    TileMap::tileSet = tileSet;
}

void TileMap::SetTile(int x, int y, int z, int n) {
    if ((x >= INT_MIN_SIZE && x <= INT_MAX_SIZE) &&
        (y >= INT_MIN_SIZE && y <= INT_MAX_SIZE) &&
        (z >= INT_MIN_SIZE && z <= INT_MAX_SIZE) &&
        (x >= INT_MIN_SIZE && x <= INT_MAX_SIZE)){
        tileMatrix[x + (y*mapWidth) + (z*mapWidth*mapHeight)] = n;
    } else {
        Log::instance.error("Tested value is higher or lower than allowed!");
    }
}

int TileMap::At(int x, int y, int z) {
    return tileMatrix.at(x + (y*mapWidth) + (z*mapWidth*mapHeight));
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    if (layer >= INT_MIN_SIZE && layer <= INT_MAX_SIZE) {
        int tileWidth = tileSet->GetTileWidth();
        int tileHeight = tileSet->GetTileHeight();
        if ((cameraX >= INT_MIN_SIZE && cameraX <= INT_MAX_SIZE) &&
            (cameraY >= INT_MIN_SIZE && cameraY <= INT_MAX_SIZE)) {
            for (int j = mapHeight-1; j >= 0; j--) {
                for (int i = mapWidth-1; i >= 0; i--) {
                    if (origem == false) {
                        tileSet->Render(At(i, j, layer), i*tileWidth - cameraX, j*tileHeight - cameraY);
                    } else {
                        // It does nothing
                    }
                }
            }
        } else {
            Log::instance.error("Tested value is higher or lower than allowed!");
        }
    } else {
        Log::instance.error("Tested value is higher or lower than allowed!");
    }
}

void TileMap::Render(int cameraX, int cameraY) {
    if ((cameraX >= INT_MIN_SIZE && cameraX <= INT_MAX_SIZE) &&
        (cameraY >= INT_MIN_SIZE && cameraY <= INT_MAX_SIZE)) {
            for (int k = 0; k < mapDepth; k++) {
                RenderLayer(k, cameraX, cameraY);
            }
    } else {
        Log::instance.error("Tested value is higher or lower than allowed!");
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

int TileMap::GetTileWidth() {
    return tileSet->GetTileWidth();
}

int TileMap::GetTileHeight() {
    return tileSet->GetTileHeight();
}

Rect TileMap::GetTileBox(int x, int y) {
    if ((x >= INT_MIN_SIZE && x <= INT_MAX_SIZE) && (y >= INT_MIN_SIZE && y <= INT_MAX_SIZE)) {
        return Rect((x*GetTileWidth()), (y*GetTileHeight()), GetTileWidth(), GetTileHeight());
    } else {
        Log::instance.error("Tested value is higher or lower than allowed!");
    }
}

Vec2 TileMap::GetTileSize() {
    return Vec2(GetTileWidth(), GetTileHeight());
}

Vec2 TileMap::GetSize() {
    return Vec2(mapWidth*GetTileWidth(), mapHeight*GetTileHeight());
}

SDL_Point TileMap::GetPos() {
    return position;
}
