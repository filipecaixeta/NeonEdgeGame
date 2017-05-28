#ifndef GALLAHADGRAPHICSCOMPONENT_H
#define GALLAHADGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Sprite.h"
#include "GameObject.h"


class GallahadGraphicsComponent
{
private:
	std::unordered_map<std::string, Sprite*> sprites;
	Sprite* sp;
	bool mirror;
	std::string baseName;

public:
	GallahadGraphicsComponent(std::string baseName_);
	~GallahadGraphicsComponent();
	void Update(GameObject* obj, float dt);
	void UpdateSprite(GameObject* obj, std::string sprite);
	void Render(Vec2 position);
	Vec2 GetSize();	
};

#endif // GALLAHADGRAPHICSCOMPONENT_H
