#ifndef MENUSTATE_H
#define MENUSTATE_H
#include <Game.h>
#include <Sprite.h>
#include <string>
#include <cstdio>
#include <cstdlib>

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
		virtual bool SelectedOptionIs(std::string opt);
		virtual State* get();

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
		Sprite bgOptions;
};

#endif // MENUSTATE_H
