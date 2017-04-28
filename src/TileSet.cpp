#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file, int adjustX, int adjustY) {
	tileSet = Sprite(file);
	TileSet::tileWidth = tileWidth;
	TileSet::tileHeight = tileHeight;
	columns = tileSet.GetWidth()/tileWidth;
	rows = tileSet.GetHeight()/tileHeight;
	TileSet::adjustX = adjustX;
	TileSet::adjustY = adjustY;
}

TileSet::~TileSet() {

}

void TileSet::Render(int index, int x, int y) {
	if(index > -1 && index < columns*rows) {
		tileSet.SetClip(index%columns*(tileWidth+adjustX), index/columns*(tileHeight+adjustY), tileWidth+adjustX, tileHeight+adjustY);
		tileSet.Render(x-adjustX, y-adjustY);
	}
}

Sprite TileSet::GetTileSet() {
	return tileSet;
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}

int TileSet::GetColumns() {
	return columns;
}

int TileSet::GetRows() {
	return rows;
}
