#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <vector>

#include "Vec2.h"
#include "Rect.h"
#include "TileSet.h"

#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f
#define INT_MIN_SIZE -32768
#define INT_MAX_SIZE 32767

class TileMap {
private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
	SDL_Point position;
	bool origem;
	int GetDepth();

	void SetTileSet(TileSet* tileSet);
	void SetTile(int x, int y, int z, int n);

public:
	TileMap(std::string file, TileSet* tileSet, SDL_Point pos = {0, 0}, bool origemEmbaixo = false);
	~TileMap();
	void Load(std::string file);
	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
	void Render(int cameraX = 0, int cameraY = 0);
	int At(int x, int y, int z = 0);
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	Rect GetTileBox(int x,int y);
	Vec2 GetTileSize();
	Vec2 GetSize();
	SDL_Point GetPos();
};

#endif /* TILEMAP_H_ */
