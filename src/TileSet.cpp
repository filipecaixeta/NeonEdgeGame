/**
 * Copyright 2017 Neon Edge Game
 * File Name: TileSet.cpp
 * Header File Name: TileSet.h
 * Class Name: TileSet
 * Objective: manages Tiles of rooms.
 */

#include "TileSet.h"
#include "Logger.h"

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
    //Log::instance.info("Initing TileSet");
    if (tileWidth >= INT_MIN_SIZE && tileWidth <= INT_MAX_SIZE ) {
        Log::instance.info("Seting tile columns");
        tileSet = Sprite(file); // Sprite file.
        TileSet::tileWidth = tileWidth; // Width of TileSet.
        columns = tileSet.GetWidth()/tileWidth; // Number of columns in TileSet.
    } else {
        Log::instance.warning("Warning the tileWidth is not in the allowed range.");
    }
    if (tileHeight >= INT_MIN_SIZE && tileHeight <= INT_MAX_SIZE) {
        Log::instance.info("Seting tile rows");
        TileSet::tileHeight = tileHeight; // Height of TileSet.
        rows = tileSet.GetHeight()/tileHeight; // Number of rows in TileSet.
    } else {
        Log::instance.warning("Warning the tileHeight is not in the allowed range.");
    }
    if(adjustX >= INT_MIN_SIZE && adjustX <= INT_MAX_SIZE){
        Log::instance.info("Seting tile adjustX");
        TileSet::adjustX = adjustX; // Adjust X axis.
    } else {
        Log::instance.warning("Warning the adjustX is not in the allowed range.");
    }
    if(adjustY >= INT_MIN_SIZE && adjustY <= INT_MAX_SIZE){
        Log::instance.info("Seting tile adjustY");
        TileSet::adjustY = adjustY; // Ajdust Y axis.
    } else {
        Log::instance.warning("Warning the adjustY is not in the allowed range.");
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
    Log::instance.info("Destroy TileSet");
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
        if ((x >= INT_MIN_SIZE && x <= INT_MAX_SIZE) && (y >= INT_MIN_SIZE && y <= INT_MAX_SIZE)) {
            // Valid if index is between 0 and end of matrix
            if(index > -1 && index < columns*rows) {
                tileSet.SetClipPosition(index%columns*(tileWidth+adjustX), index/columns*(tileHeight+adjustY),
                                tileWidth+adjustX, tileHeight+adjustY);
                tileSet.RenderTexture(x-adjustX, y-adjustY);
            } else {
            }
        } else {
            Log::instance.warning("tileSet x value out of range");
        }
    } else{
        Log::instance.warning("tileSet index out of range");
    }
}

/**
 * Objective: Return a Sprite of TileSet.

 * @param none.
 * @param none.
 * @return: sprite of TileSet.
 */
Sprite TileSet::GetTileSet() {
    if(&tileSet != NULL){
        return tileSet;
    } else {
        Log::instance.warning("Width of tileset is low than 0.");
    }
}

/**
 * Objective: Return number of tileWidth from TileSet.

 * @param none.
 * @param none.
 * @return: int tileWidth.
 */
int TileSet::GetTileWidth() {
    if(tileWidth > 0){
        return tileWidth;
    } else{
        Log::instance.warning("Width of tileset is low than 0.");
    }
}

/**
 * Objective: Return number of tileHeight from TileSet.

 * @param none.
 * @param none.
 * @return: int tileHeight.
 */
int TileSet::GetTileHeight() {
    if(tileHeight > 0){
        return tileHeight;
    } else{
        Log::instance.warning("Height of tileset is low than 0.");
    }
}

/**
 * Objective: Return Number of columns from TileSet.

 * @param none.
 * @param none.
 * @return: int columns.
 */
int TileSet::GetColumns() {

    if(rows > 0){
        return columns;
    } else {
        Log::instance.warning("columns of tileset is low than 0.");
    }
}

/**
   Objective: Return number of rows from TileSet.
   @param int tileWidth.
   @param int tileHeight.
   @return: int rows.

*/
int TileSet::GetRows() {
    if(rows > 0){
        return rows;
    } else {
        Log::instance.warning("rown of tileset is low than 0.");
    }
}
