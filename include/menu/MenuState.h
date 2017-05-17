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
		virtual void SetOption(unsigned int i);
		virtual State* get();

		Vec2 CenterVertical(Sprite *sp);
		Vec2 CenterVertical(int size);

	protected:
		std::vector<std::pair<std::string,Sprite*> > menuOptions;
		int currentOption;
};

#endif // MENUSTATE_H
