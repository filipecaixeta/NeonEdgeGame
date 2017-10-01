#include "SaveComponent.h"
#include <fstream>

SaveComponent *SaveComponent::instance_ = nullptr;

SaveComponent::SaveComponent()
{
	if (instance_==nullptr)
	{
		instance_ = this;
	}
}

SaveComponent::~SaveComponent()
{

}

void SaveComponent::Update(GameObject *obj, std::string fileName)
{
	if (saveToFile)
	{
		Delete(fileName);
		instance_->name = obj->name;
		instance_->box.x = obj->box.x;
		instance_->box.y = obj->box.y;
		instance_->facing = obj->facing;
		instance_->footing = obj->footing; 
		instance_->lastFooting = obj->lastFooting;
		std::fstream fs;
		fs.open(fileName, std::fstream::out | std::fstream::app);
		fs.write((char*)&instance_, sizeof(instance_));
		fs.close();
	}
	else
	{
		std::fstream fs;
		fs.open(fileName, std::fstream::in);
		fs.read((char*)&instance_, sizeof(instance_));
		obj->name = instance_->name;
		obj->box.x = instance_->box.x;
		obj->box.y = instance_->box.y;
		obj->facing = instance_->facing;
		obj->footing = instance_->footing;
		obj->lastFooting = instance_->lastFooting;
		fs.close();
	}
}

void SaveComponent::Save(bool s)
{
	saveToFile = s;
}

void SaveComponent::Delete(std::string fileName)
{
	std::fstream fs;
	fs.open(fileName, std::fstream::out | std::fstream::trunc);
	fs.close();
}

SaveComponent &SaveComponent::GetInstance()
{
	if (instance_==nullptr)
		throw std::string("Instancia de SaveComponent eh um nullptr");
	else
		return *instance_;
}
