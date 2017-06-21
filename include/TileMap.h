#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <vector>

#include "Vec2.h"
#include "Rect.h"
#include "TileSet.h"

class TileMap {
private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
	SDL_Point position;

public:
	TileMap(std::string file, TileSet* tileSet, SDL_Point pos = {0, 0});
	~TileMap();
	void Load(std::string file);
	void SetTileSet(TileSet* tileSet);
	void SetTile(int x, int y, int z, int n);
	int At(int x, int y, int z = 0);
	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
	void Render(int cameraX = 0, int cameraY = 0);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	int GetTileWidth();
	int GetTileHeight();
	Rect GetTileBox(int x,int y);
	Vec2 GetTileSize();
	Vec2 GetSize();
	SDL_Point GetPos();
};

#endif /* TILEMAP_H_ */
