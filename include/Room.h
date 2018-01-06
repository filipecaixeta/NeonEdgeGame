#ifndef ROOM_H_
#define ROOM_H_
#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f
#define INT_MIN_SIZE -32768
#define INT_MAX_SIZE 32767
#define __USE_MINGW_ANSI_STDIO 0

#include <vector>
#include <string>

#include "Vec2.h"
#include "TileSet.h"
#include "TileMap.h"
#include "GameObject.h"
#include "SceneObjects.h"

struct ObjectData
{
	int id;
	int x;
	int y;
};

class Room
{
public:
	Room(TileSet* tileSet, int index, Vec2 position, TileSet* background,std::string mapName);
	~Room();
	void AddObject(GameObject* ptr);
	void AddObjectAsFirst(GameObject* ptr);
	void RemoveObject(GameObject* ptr);
	GameObject* GetFirst();
	TileMap* GetMap();
	Vec2 GetPos();
	void ObjectUpdate(float dt);
	void ObjectCollision();
	void Update(float dt);
	void Render();

private:
	void CreateObjects();
	void LoadObjects(std::string file);
	void ObjectCleanup();
	void RemovePlayer();

	int index;
	Vec2 position;
	TileMap* map;
	std::vector<ObjectData> objectData;
	std::vector<GameObject*> objectArray;
	SceneObjects sceneObjects;
	TileMap* backgroundMap;
};

#endif
