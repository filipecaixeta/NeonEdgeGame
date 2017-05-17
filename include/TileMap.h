#ifndef TILEMAP_H_
#define TILEMAP_H_
#include "TileSet.h"
#include <Rect.h>

class TileMap {
private:
	std::vector<std::vector<std::vector<int>>> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;

public:
	TileMap(std::string file, TileSet* tileSet);
	~TileMap();
	void Load(std::string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z = 0);
	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
	void Render(int cameraX = 0, int cameraY = 0);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	int GetTileWidth();
	int GetTileHeight();
	Rect GetAABB(int x,int y);
};

#endif /* TILEMAP_H_ */
