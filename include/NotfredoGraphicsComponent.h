#ifndef NOTFREDOGRAPHICSCOMPONENT_H
#define NOTFREDOGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GameObject.h"

class NotfredoGraphicsComponent
{
private:
	std::unordered_map<std::string, Sprite*> sprites;
	Sprite* sp;
	bool mirror;
	std::string baseName;

public:
	NotfredoGraphicsComponent(std::string baseName_);
	~NotfredoGraphicsComponent();
	void Update(GameObject* obj, float dt);
	void UpdateSprite(GameObject* obj, std::string sprite);
	void Render(Vec2 position);
	Vec2 GetSize();	
};

#endif // NOTFREDOGRAPHICSCOMPONENT_H
