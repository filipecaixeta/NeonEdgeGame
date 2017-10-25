#include "menu/MenuState.h"
#include "InputManager.h"

#include <assert.h>

MenuState::MenuState():
	menuOptions(),
	currentOption(-1),
	fontName("Sabo-Filled.ttf"),
	fontSize(72),
	fontColor({255,255,255,255})
{

}

MenuState::~MenuState() {
	for (auto &i: menuOptions) {
		delete i.sprite;
	}
	menuOptions.clear();
}

void MenuState::LoadAssets()
{

}

void MenuState::Update() {
	if (InputManager::GetInstance().KeyPress((int)'q')) {
		quitRequested = true;
	} else {
        // It does nothing
    }
	if(InputManager::GetInstance().KeyPress(SDLK_UP)) {
		SetOption(-1);
	} else {
        // It does nothing.
    }
	if (InputManager::GetInstance().KeyPress(SDLK_DOWN)) {
		SetOption(1);
	} else {
        // It does nothing.
    }
}

void MenuState::Render() {
	bg.Render(CenterVertical(&bg));
    int offset = 70;
	int pos=offset;
	for (auto option: menuOptions) {
		option.sprite->Render(CenterVertical(option.sprite)+Vec2(0,pos));
		pos += offset;
        assert(pos >= INT_MIN_SIZE && pos <= INT_MAX_SIZE);
	}
}

bool MenuState::QuitRequested() {
	return quitRequested;
}

bool MenuState::Is(std::string type) {
	return (type == "Menu");
}

void MenuState::SetOption(int i = 0) {
	if (!menuOptions.size())
		return;

	currentOption = currentOption+i;
	if (currentOption<0) {
		currentOption = menuOptions.size()+i;
	} else {
        // It does nothing.
    }

	currentOption = currentOption%menuOptions.size();

	if (menuOptions[currentOption].selectable==false) {
		SetOption(i);
		return;
	} else {
        // It does nothing.
    }
}

State *MenuState::get() {
	return this;
}

bool MenuState::SelectedOptionIs(std::string opt) {
	return menuOptions[currentOption].key==opt;
}
