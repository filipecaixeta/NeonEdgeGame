#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H
#include <GameObject.h>
#include <string>
#include <Vec2.h>
#include <Rect.h>
#include <Sprite.h>

class GraphicsComponent
{
	public:
		GraphicsComponent(std::string baseName_);
		~GraphicsComponent();
		void Update(GameObject *obj,float dt);
		void UpdateSprite(std::string sprite);
		void Render(Vec2 position);
		Vec2 GetSize();
	private:
		std::unordered_map<std::string, Sprite*> sprites;
		Sprite* sp;
		Rect box;
		bool mirror;
		std::string baseName;
};

#endif // GRAPHICSCOMPONENT_H
