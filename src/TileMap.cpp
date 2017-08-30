#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "TileMap.h"

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
    std::string num;
    f.open(file.c_str(), std::ios::in);
    if(f.is_open()) {
        getline(f, num, ',');
        //std::cout << "leu: " << num << std::endl;
        mapWidth = atoi(num.c_str());
        getline(f, num, ',');
        //std::cout << "leu: " << num << std::endl;
        mapHeight = atoi(num.c_str());
        getline(f, num, ',');
        //std::cout << "leu: " << num << std::endl;
        mapDepth = atoi(num.c_str());
        while(getline(f, num, ',')){
            tileMatrix.push_back(atoi(num.c_str())-1);
            //std::cout << "leu: " << num << std::endl;
            //std::cout << "atoi: " << atoi(num.c_str())-1 << std::endl;
        }
    }
    else {
        std::cout<< "f.open: unable to open file: " << file.c_str();
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    TileMap::tileSet = tileSet;
}

void TileMap::SetTile(int x, int y, int z, int n) {
    tileMatrix[x + (y*mapWidth) + (z*mapWidth*mapHeight)] = n;
}

int TileMap::At(int x, int y, int z) {
    //if (x < 0 || y < 0 || x >= mapWidth || y >= mapHeight)
        //std::cerr << "Tile at (" << x << "," << y << "," << z << ") out of map boundaries" << std::endl;
    return tileMatrix.at(x + (y*mapWidth) + (z*mapWidth*mapHeight));
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    int i, j;
    int tileWidth = tileSet->GetTileWidth();
    int tileHeight = tileSet->GetTileHeight();
    for(j = mapHeight-1; j >= 0; j--){
        for(i = mapWidth-1; i >= 0; i--){
            if(origem == false) {
                tileSet->Render(At(i, j, layer), i*tileWidth - cameraX,
                j*tileHeight - cameraY);
            }
                
//            else
//                tileSet->Render(At(i, j, layer), i*tileWidth - cameraX,
//                                j*tileHeight + 1500 - cameraY);
        }
    }

    /*for(int j = mapHeight-1; j > -1; j--) {
        for(int i = mapWidth-1; i > -1; i--) {
            tileSet->Render(tileMatrix[layer][j][i], i*tileSet->GetTileWidth() + position.x * mapWidth * tileSet->GetTileWidth() - cameraX,
                            j*tileSet->GetTileHeight() + position.y * mapHeight * tileSet->GetTileHeight() - cameraY);
        }
    }*/
}

void TileMap::Render(int cameraX, int cameraY) {
    for(int k = 0; k < mapDepth; k++)
        RenderLayer(k, cameraX, cameraY);
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
    return Rect((x*GetTileWidth())/*+(mapWidth*GetTileWidth()*position.x)*/,
                (y*GetTileHeight())/*+(mapHeight*GetTileHeight()*position.y)*/,
                GetTileWidth(),GetTileHeight());
}

Vec2 TileMap::GetTileSize() {
    return Vec2(GetTileWidth(),GetTileHeight());
}

Vec2 TileMap::GetSize() {
    return Vec2(mapWidth*GetTileWidth(),mapHeight*GetTileHeight());
}

SDL_Point TileMap::GetPos() {
    return position; 
}
