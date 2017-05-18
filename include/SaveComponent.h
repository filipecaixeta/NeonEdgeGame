#ifndef SAVECOMPONENT_H
#define SAVECOMPONENT_H
#include <GameObject.h>
#include <string>

class SaveComponent
{
	public:
		SaveComponent(std::string fileName);
		~SaveComponent();
		void Update(GameObject *obj,float dt);
		void Save(bool s);
		static SaveComponent &GetInstance();

	private:
		bool saveToFile;
		static SaveComponent *instance_;
};

#endif // SAVECOMPONENT_H
