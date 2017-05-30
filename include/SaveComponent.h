#ifndef SAVECOMPONENT_H
#define SAVECOMPONENT_H

#include <string>

#include "GameObject.h"
#include "Rect.h"
#include "Vec2.h"

class SaveComponent
{
	public:

		std::string name;
		Rect box = Rect();
		GameObject::Face facing;
		GameObject::Footing footing;
		GameObject::Footing lastFooting;

		SaveComponent();
		~SaveComponent();
		void Update(GameObject *obj, std::string fileName);
		void Save(bool s);
		void Delete(std::string fileName);
		static SaveComponent &GetInstance();

	private:
		bool saveToFile;
		static SaveComponent *instance_;
};

#endif // SAVECOMPONENT_H