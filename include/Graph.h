#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "TileMap.h"
#include "Rect.h"
#include "Character.h"

typedef struct Node node;

struct Node {
  int x;
  int y;
  int z;
  float graph_distance;
  float physical_distance;
  float combined_distance;
  node* going_through;
};

class Graph {
private:
    ~Graph();
    Graph(TileMap* map,Character* enemy,Character* player);
    std::vector<node> pathStack;
    node startNode;
    node endNode;
};

#endif // INCLUDE_GRAPH_H_
