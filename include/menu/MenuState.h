#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "Game.h"
#include "Sprite.h"
#include <string>
#include <cstdio>
#include <cstdlib>

#define INT_MIN_SIZE -32768
#define INT_MAX_SIZE 32767

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
		int currentOption = 0;
		std::string fontName;
        int fontSize = 0;
		SDL_Color fontColor;
		Sprite bgOptions;
};

#endif // MENUSTATE_H
