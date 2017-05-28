#ifndef MENUSTATE_H
#define MENUSTATE_H
#include <Game.h>
#include <Sprite.h>
#include <string>

class MenuState: public State
{
	public:
		MenuState();
		virtual ~MenuState();
		virtual void LoadAssets();
		virtual void Update();
		virtual void Render();
		virtual bool QuitRequested();
		virtual bool Is(std::string type);
		virtual void SetOption(int i);
		virtual State* get();

		Vec2 CenterVertical(Sprite *sp);
		Vec2 CenterVertical(int size);
		Vec2 CenterVertical(Vec2 size);
		Vec2 CenterHorizontal(Sprite* sp);
		Vec2 CenterHorizontal(int size);
		Vec2 CenterHorizontal(Vec2 size);

		struct Option
		{
			std::string key;
			Sprite *sprite;
			bool selectable;
			int current;
		};

protected:
		std::vector<Option> menuOptions;
		int currentOption;
		std::string fontName;
		int fontSize;
		SDL_Color fontColor;
};

#endif // MENUSTATE_H
