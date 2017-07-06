#ifndef SCENEOBJECTS_H
#define SCENEOBJECTS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>

#include "Sprite.h"

class SceneObjects
{
	struct Obj
	{
		Sprite sp;
		std::vector<SDL_Point> positionVec;
	};
public:
	SceneObjects(std::string fileName);
	void Render();
	void Update();
	void LoadObjects(std::string file);
	void AddObject(std::string name, Vec2 pos);
	void AddObject(std::string name, SDL_Point pos);
	std::unordered_map<std::string,Obj> objs;
	std::string fileName;
};

#endif // SCENEOBJECTS_H
