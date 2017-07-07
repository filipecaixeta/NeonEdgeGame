#include <menu/MenuState.h>
#include <InputManager.h>

MenuState::MenuState():
	menuOptions(),
	currentOption(-1),
	fontName("Sabo-Filled.ttf"),
	fontSize(72),
	fontColor({255,255,255,255})
{

}

MenuState::~MenuState()
{
	for (auto &i: menuOptions)
	{
		delete i.sprite;
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
		SetOption(-1);
	}
	if(InputManager::GetInstance().KeyPress(SDLK_DOWN))
	{
		SetOption(1);
	}
}

void MenuState::Render()
{
	int offset = 70;
	bg.Render(CenterVertical(&bg));
	int pos=offset;
	for(auto option: menuOptions)
	{
		option.sprite->Render(CenterVertical(option.sprite)+Vec2(0,pos));
		pos += offset;
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

void MenuState::SetOption(int i)
{
	if (!menuOptions.size())
		return;

	currentOption = currentOption+i;
	if (currentOption<0)
	{
		currentOption = menuOptions.size()+i;
	}
	currentOption = currentOption%menuOptions.size();

	if (menuOptions[currentOption].selectable==false)
	{
		SetOption(i);
		return;
	}
}

State *MenuState::get()
{
	return this;
}

bool MenuState::SelectedOptionIs(std::string opt)
{
	return menuOptions[currentOption].key==opt;
}
