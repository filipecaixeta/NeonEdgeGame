#include <menu/MenuState.h>
#include <InputManager.h>

MenuState::MenuState()
{

}

MenuState::~MenuState()
{
	for (auto &i: menuOptions)
	{
		delete i.second;
	}
	menuOptions.clear();
}

void MenuState::LoadAssets()
{

}

void MenuState::Update()
{
	if(InputManager::GetInstance().KeyPress((int)'q'))
	{
		quitRequested = true;
	}
	if(InputManager::GetInstance().KeyPress(SDLK_UP))
	{
		SetOption(currentOption-1);
	}
	if(InputManager::GetInstance().KeyPress(SDLK_DOWN))
	{
		SetOption(currentOption+1);
	}
}

void MenuState::Render()
{
	bg.Render(CenterVertical(&bg));
	int pos=0;
	for(auto option: menuOptions)
	{
		option.second->Render(CenterVertical(option.second)+Vec2(0,pos));
		pos += option.second->GetHeight();
	}
}

bool MenuState::QuitRequested()
{
	return quitRequested;
}

bool MenuState::Is(std::string type)
{
	return (type == "Menu");
}

void MenuState::SetOption(unsigned int i)
{
	currentOption = i%menuOptions.size();
	for (i=0; i<menuOptions.size(); i++)
	{
		menuOptions[i].second->SetScaleX(1.0);
		menuOptions[i].second->SetScaleY(1.0);
	}
	menuOptions[currentOption].second->SetScaleX(1.3);
	menuOptions[currentOption].second->SetScaleY(1.3);
}

State *MenuState::get()
{
	return this;
}

Vec2 MenuState::CenterVertical(Sprite *sp)
{
	return CenterVertical(sp->GetWidth());
}

Vec2 MenuState::CenterVertical(int size)
{
	SDL_Point windowSize = Game::GetInstance().GetScreenSize();
	return Vec2((windowSize.x-size)/2,0);
}
