#include <iostream>
#include <fstream>
#include <cstdio>

#include "SceneObjects.h"
#include "Camera.h"

SceneObjects::SceneObjects(std::string fileName):
	fileName(fileName)
{
	LoadObjects(this->fileName);
}

void SceneObjects::Render()
{
	for(auto& obj: objs)
		for(auto& pos: obj.second.positionVec)
			obj.second.sp.Render(pos.x - Camera::GetInstance().pos.x, pos.y - Camera::GetInstance().pos.y);
}

void SceneObjects::Update()
{
	LoadObjects(fileName);
}

void SceneObjects::LoadObjects(std::string file)
{
	std::ifstream f;
	f.open(file.c_str(), std::ios::in);

	if(!f.is_open())
	{
		std::cerr<< "f.open: unable to open file: " << file.c_str();
		return;
	}

	for(auto& i: objs)
		i.second.positionVec.clear();

	for (std::string line; std::getline(f, line); )
	{
		char name[40];
		SDL_Rect pos;
		std::sscanf(line.c_str(),"%s %d,%d",name,&pos.x,&pos.y);
		if (objs.count(name)==0)
		{
			Obj obj;
			obj.sp.Open(std::string("sceneObjs/")+std::string(name)+std::string(".png"));
			obj.positionVec.push_back(pos);
			objs.emplace(name,obj);
		}
		else
		{
			objs[name].positionVec.push_back(pos);
		}

	}
	f.close();
}
