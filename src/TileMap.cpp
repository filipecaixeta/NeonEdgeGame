#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "TileMap.h"

TileMap::TileMap(std::string file, TileSet* tileSet, SDL_Point pos)
{
	position = pos;
	Load(file);
	SetTileSet(tileSet);
}

TileMap::~TileMap()
{
	delete tileSet;
}

void TileMap::Load(std::string file)
{
	std::ifstream f;
	std::string num;
	f.open(file.c_str(), std::ios::in);
	if(f.is_open()){
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
	else{
		std::cout<< "f.open: unable to open file: " << file.c_str();
	}

	/*std::FILE* fileReader = fopen(file.c_str(), "r");
	if(fileReader != NULL)
	{
		char n [2];
		fgets(n, 3, fileReader);
		mapWidth = atoi(n);
		fgets(n, 2, fileReader);
		fgets(n, 3, fileReader);
		mapHeight = atoi(n);
		fgets(n, 2, fileReader);
		fgets(n, 3, fileReader);
		mapDepth = atoi(n);
		fgets(n, 2, fileReader);
		for(int k = 0; k < mapDepth; k++)
		{
			tileMatrix.emplace_back(std::vector<std::vector<int>>());
			for(int j = 0; j < mapHeight; j++)
			{
				tileMatrix[k].emplace_back(std::vector<int>());
				for(int i = 0; i < mapWidth; i++)
				{
					fgets(n, 2, fileReader);
					fgets(n, 3, fileReader);
					tileMatrix[k][j].emplace_back(atoi(n)-1);
				}
				fgets(n, 2, fileReader);
			}
			fgets(n, 3, fileReader);
		}
	}
	else
	{
		std::cerr << "Unable to read" << file.c_str() << std::endl;
	}
	fclose(fileReader);*/
}

void TileMap::SetTileSet(TileSet* tileSet)
{
	TileMap::tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z)
{
	//if (x < 0 || y < 0 || x >= mapWidth || y >= mapHeight)
		//std::cerr << "Tile at (" << x << "," << y << "," << z << ") out of map boundaries" << std::endl;
	return tileMatrix.at(x + (y*mapWidth) + (z*mapWidth*mapHeight));
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	int i, j;
	int tileWidth = tileSet->GetTileWidth();
	int tileHeight = tileSet->GetTileHeight();
	for(j = 0; j < mapHeight; j++){
		for(i = 0; i < mapWidth; i++){
			tileSet->Render(At(i, j, layer), i*tileWidth + position.x * mapWidth * tileWidth - cameraX,
							j*tileHeight + position.y * mapHeight * tileHeight- cameraY);
		}
	}

	/*for(int j = mapHeight-1; j > -1; j--) {
		for(int i = mapWidth-1; i > -1; i--) {
			tileSet->Render(tileMatrix[layer][j][i], i*tileSet->GetTileWidth() + position.x * mapWidth * tileSet->GetTileWidth() - cameraX,
							j*tileSet->GetTileHeight() + position.y * mapHeight * tileSet->GetTileHeight() - cameraY);
		}
	}*/
}

void TileMap::Render(int cameraX, int cameraY)
{
	for(int k = 0; k < mapDepth; k++)
		RenderLayer(k, cameraX, cameraY);
}

int TileMap::GetWidth()
{
	return mapWidth;
}

int TileMap::GetHeight()
{
	return mapHeight;
}

int TileMap::GetDepth()
{
	return mapDepth;
}

int TileMap::GetTileWidth()
{
	return tileSet->GetTileWidth();
}

int TileMap::GetTileHeight()
{
	return tileSet->GetTileHeight();
}

Rect TileMap::GetTileBox(int x, int y)
{
	return Rect((x*GetTileWidth())+(mapWidth*GetTileWidth()*position.x),
				(y*GetTileHeight())+(mapHeight*GetTileHeight()*position.y),
				GetTileWidth(),GetTileHeight());
}

Vec2 TileMap::GetTileSize()
{
	return Vec2(GetTileWidth(),GetTileHeight());
}

Vec2 TileMap::GetSize()
{
	return Vec2(mapWidth*GetTileWidth(),mapHeight*GetTileHeight());
}

SDL_Point TileMap::GetPos()
{
	return position; 
}
