#ifndef LANCELOTGRAPHICSCOMPONENT_H
#define LANCELOTGRAPHICSCOMPONENT_H

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GameObject.h"
#include <string>

class LancelotGraphicsComponent
{
private:
	std::unordered_map<std::string, Sprite*> sprites;
	Sprite* sp;
	bool mirror;
	std::string baseName;

public:
	LancelotGraphicsComponent(std::string baseName_);
	~LancelotGraphicsComponent();
	void Update(GameObject* obj, float dt);
	void UpdateSprite(GameObject* obj, std::string sprite);
	void Render(Vec2 position);
	Vec2 GetSize();	
};

#endif // LANCELOTGRAPHICSCOMPONENT_H
