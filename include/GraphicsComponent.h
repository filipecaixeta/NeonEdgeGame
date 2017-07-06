#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Character.h"

class Character;

class GraphicsComponent
{
public:
	GraphicsComponent(std::string baseName_);
	virtual ~GraphicsComponent();
	virtual void Update(GameObject* obj, float dt) = 0;
	virtual void UpdateSprite(GameObject* obj, std::string sprite);
	virtual void Render(Vec2 position);
	virtual Vec2 GetSize();
	virtual SDL_Surface*GetSurface();
	virtual SDL_Rect GetClip();
	virtual bool GetMirror();
	virtual void AddSprite(std::string baseName, std::string name, int frameCount, int frameTime, bool loops = false);
protected:
	std::unordered_map<std::string, Sprite*> sprites;
	std::unordered_map<std::string, SDL_Surface*> surfaces;
	Sprite* sp;
	SDL_Surface* surface;
	bool mirror;
	std::string baseName;
};

#endif // GRAPHICSCOMPONENT_H
