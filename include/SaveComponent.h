#ifndef SAVECOMPONENT_H
#define SAVECOMPONENT_H

#include <string>

#include "GameObject.h"
#include "Rect.h"
#include "Vec2.h"

class SaveComponent
{
	public:
		SaveComponent();
		~SaveComponent();
		void Update(GameObject *obj, std::string fileName);
		void Save(bool s);

	private:
		std::string name;
		Rect box = Rect();
		GameObject::Face facing;
		GameObject::Footing footing;
		GameObject::Footing lastFooting;

		bool saveToFile;
		static SaveComponent *instance_;
		static SaveComponent &GetInstance();
		void Delete(std::string fileName);
};

#endif // INCLUDE_SAVECOMPONENT_H
