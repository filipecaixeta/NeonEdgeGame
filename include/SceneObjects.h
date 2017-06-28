#ifndef SCENEOBJECTS_H
#define SCENEOBJECTS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL2/SDL.h>

#include "Sprite.h"

class SceneObjects
{
	struct Obj
	{
		Sprite sp;
		std::vector<SDL_Rect> positionVec;
	};
public:
	SceneObjects(std::string fileName);
	void Render();
	void Update();
	std::unordered_map<std::string,Obj> objs;
	void LoadObjects(std::string file);
	std::string fileName;
};

#endif // SCENEOBJECTS_H
