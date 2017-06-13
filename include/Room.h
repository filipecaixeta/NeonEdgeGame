#ifndef ROOM_H_
#define ROOM_H_

#define __USE_MINGW_ANSI_STDIO 0

#include <vector>
#include <string>

#include "Vec2.h"
#include "TileSet.h"
#include "TileMap.h"
#include "GameObject.h"

class Room
{
public:
	Room(TileSet* tileSet, int index, Vec2 position);
	~Room();
	void AddObject(GameObject* ptr);
	void AddObjectAsFirst(GameObject* ptr);
	void RemoveObject(GameObject* ptr);
	void RemovePlayer();
	TileMap* GetMap();
	Vec2 GetPos();
	void ObjectUpdate(float dt);
	void ObjectCollision();
	void ObjectCleanup();
	void Update(float dt);
	void Render();

private:
	int index;
	Vec2 position;
	TileMap* map;
	std::vector<GameObject*> objectArray;
};

#endif