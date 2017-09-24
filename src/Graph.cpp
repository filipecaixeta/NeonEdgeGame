/**
    Copyright (c) 2017 Neon Edge Game.
    File Name: Graph.cpp
    Header File Name: Graph.h
    Class Name: Graph
    Objective: it does nothing.

*/

#include "Graph.h"

/**
    Objective: it does nothing.
    @param TileMap map - current map.
    @param Character enemy - enemy of current map.
    @param Character player - character of current map.
    @return none.

*/
Graph::Graph(TileMap *map, Character *enemy, Character *player) {
    /*
    for (int i = 0; i < map->GetHeight(); i++) {
        for (int j = 0; j < map->GetWidth(); j++) {
            pathStack.emplace_back(AddNode(j, i));
            if (Rect(j * map->GetTileWidth(), i * map->GetTileHeight(), map->GetTileWidth(),
                     map->GetTileHeight()).IsInside(enemy->box.GetCenter())) {
                CopyNode(&pathStack.back, &startNode);
            }

            if (Rect(j * map->GetTileWidth(), i * map->GetTileHeight(), map->GetTileWidth(),
                     map->GetTileHeight()).IsInside(player->box.GetCenter())) {
                CopyNode(&pathStack.back, &endNode);
            }
        }
    }
    */
}
