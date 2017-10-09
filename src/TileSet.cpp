/**
 * Copyright 2017 Neon Edge Game
 * File Name: TileSet.cpp
 * Header File Name: TileSet.h
 * Class Name: TileSet
 * Objective: manages Tiles of rooms.
 */

#include "TileSet.h"

/**
 * Objective: Constructor of the TileSet.

 * @param int tileWidth.
 * @param int tileHeight.
 * @param string file - Sprite file name.
 * @param int adjustX - Adjust tile in X axis.
 * @param int adjustY - Adjust tile in Y axis.
 * @return: a instance of TileSet.
 */
TileSet::TileSet(int tileWidth, int tileHeight, std::string file, int adjustX, int adjustY) {
    if (tileWidth >= INT_MIN_SIZE && tileWidth <= INT_MAX_SIZE ) {
        tileSet = Sprite(file); // Sprite file.
        TileSet::tileWidth = tileWidth; // Width of TileSet.
        columns = tileSet.GetWidth()/tileWidth; // Number of columns in TileSet.
    }
    if (tileHeight >= INT_MIN_SIZE && tileHeight <= INT_MAX_SIZE) {
        TileSet::tileHeight = tileHeight; // Height of TileSet.
        rows = tileSet.GetHeight()/tileHeight; // Number of rows in TileSet.
    }
    if(adjustX >= INT_MIN_SIZE && adjustX <= INT_MAX_SIZE){
        TileSet::adjustX = adjustX; // Adjust X axis.
    }
    if(adjustY >= INT_MIN_SIZE && adjustY <= INT_MAX_SIZE){
        TileSet::adjustY = adjustY; // Ajdust Y axis.
    }
}

/**
 * Function Objective: Destroct the class TileSet, delocalizing some memory used in the class and
 *                      shutdown dependent libraries.
 *
 * @param none.
 * @return: none.
 */
TileSet::~TileSet() {

}

/**
 * Objective: Render TileSet.

 * @param int index -.
 * @param int x -.
 * @param int y -.
 * @return: none.
*/
void TileSet::Render(int index, int x, int y) {
    if (index >= INT_MIN_SIZE && index <= INT_MAX_SIZE) {
        if ((x >= INT_MIN_SIZE && x <= INT_MIN_SIZE) && (y >= INT_MIN_SIZE && y <= INT_MAX_SIZE)) {
            // Valid if index is between 0 and end of matrix
            if(index > -1 && index < columns*rows) {
                tileSet.SetClip(index%columns*(tileWidth+adjustX), index/columns*(tileHeight+adjustY),
                 tileWidth+adjustX, tileHeight+adjustY);
                tileSet.Render(x-adjustX, y-adjustY);
            }
        }
    }
}

/**
 * Objective: Return a Sprite of TileSet.

 * @param none.
 * @param none.
 * @return: sprite of TileSet.
 */
Sprite TileSet::GetTileSet() {
    return tileSet;
}

/**
 * Objective: Return number of tileWidth from TileSet.

 * @param none.
 * @param none.
 * @return: int tileWidth.
*/
int TileSet::GetTileWidth() {
    return tileWidth;
}

/**
 * Objective: Return number of tileHeight from TileSet.

 * @param none.
 * @param none.
 * @return: int tileHeight.
*/
int TileSet::GetTileHeight() {
    return tileHeight;
}

/**
 * Objective: Return Number of columns from TileSet.

 * @param none.
 * @param none.
 * @return: int columns.
*/
int TileSet::GetColumns() {
    return columns;
}

/**
   Objective: Return number of rows from TileSet.
   @param int tileWidth.
   @param int tileHeight.
   @return: int rows.

*/
int TileSet::GetRows() {
    return rows;
}
