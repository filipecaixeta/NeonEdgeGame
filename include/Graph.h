#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "TileMap.h"
#include "Rect.h"
#include "Character.h"


typedef struct Node node;


struct Node{
  int x,y,z;
  float graph_distance;
  float physical_distance;
  float combined_distance;
  node* going_through;
};



class Graph
{
public:
    Graph(TileMap* map,Character* enemy,Character* player);
    ~Graph();
    void AddNode(int x,int y, int z = 0);
    node* FindNode(int x,int y);
    void CopyNode(node* source,node* target);



private:

    std::vector<node> pathStack;
    node startNode;
    node endNode;
};

#endif // GRAPH_H
