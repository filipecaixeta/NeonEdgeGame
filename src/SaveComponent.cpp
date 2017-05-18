#include <SaveComponent.h>

SaveComponent *SaveComponent::instance_ = nullptr;

SaveComponent::SaveComponent(std::string fileName)
{
	if (instance_==nullptr)
	{
		instance_ = this;
	}
	// Abre o arquivo fileName
}

SaveComponent::~SaveComponent()
{
	// Fecha o arquivo de novo pra ter certeza
}

void SaveComponent::Update(GameObject *obj, float dt)
{
	if (saveToFile)
	{
		//	Salva
		//	obj->objName
		//	obj->hitpoints;
		//	obj->GetPosition();
		//	E outros
	}
}

void SaveComponent::Save(bool s)
{
	saveToFile = s;
}

SaveComponent &SaveComponent::GetInstance()
{
	if (instance_==nullptr)
		throw std::string("Instancia de SaveComponent eh um nullptr");
	else
		return *instance_;
}
