#include <iostream>
#include <fstream>
#include <cstdio>

#include "SceneObjects.h"
#include "Camera.h"

SceneObjects::SceneObjects(std::string fileName):
	fileName(fileName)
{
	std::cerr << fileName <<std::endl;
	LoadObjects(this->fileName);
}

void SceneObjects::Render()
{
	for(auto& obj: objs)
		for(auto& pos: obj.second.positionVec)
		{
			if (!objsAfter[obj.first])
				obj.second.sp.Render(pos.x - Camera::GetInstance().pos.x, pos.y - Camera::GetInstance().pos.y - obj.second.sp.GetHeight());
		}
}

void SceneObjects::RenderAfter()
{
	for(auto& obj: objs)
		for(auto& pos: obj.second.positionVec)
		{
			if (objsAfter[obj.first])
				obj.second.sp.Render(pos.x - Camera::GetInstance().pos.x, pos.y - Camera::GetInstance().pos.y - obj.second.sp.GetHeight());
		}
}

void SceneObjects::Update()
{
//	LoadObjects(fileName);
}

void SceneObjects::AddObject(std::string name, Vec2 pos)
{
	objsAfter[name]=false;
	AddObject(name,SDL_Point{pos.x,pos.y});
}

void SceneObjects::AddObjectAfter(std::string name, Vec2 pos)
{
	objsAfter[name]=true;
	AddObject(name,SDL_Point{pos.x,pos.y});
}

void SceneObjects::AddObject(std::string name, SDL_Point pos)
{
	if (objs.count(name)==0)
	{
		Obj obj;
		std::string name2 = std::string("sceneObjs/")+std::string(name)+std::string(".png");
		if (FILE *file = std::fopen((Resources::BASENAME_IMAGE+name2).c_str(), "r"))
		{
			fclose(file);
			obj.sp.Open(name2);
			obj.positionVec.push_back(pos);
			objs.emplace(name,obj);
		}
	}
	else
	{
		objs[name].positionVec.push_back(pos);
	}
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
		SDL_Point pos;
		std::sscanf(line.c_str(),"%s %d,%d",name,&pos.x,&pos.y);
		if (objs.count(name)==0)
		{
			Obj obj;
			std::string name2 = std::string("sceneObjs/")+std::string(name)+std::string(".png");
			if (FILE *file = std::fopen((Resources::BASENAME_IMAGE+name2).c_str(), "r"))
			{
				fclose(file);
				obj.sp.Open(name2);
				obj.positionVec.push_back(pos);
				objs.emplace(name,obj);
			}
		}
		else
		{
			objs[name].positionVec.push_back(pos);
		}
	}
	f.close();
}
