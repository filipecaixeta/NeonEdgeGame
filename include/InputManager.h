#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

#include "SDL.h"
#include <unordered_map>

class InputManager {
private:
	int mouseX;
	int mouseY;
	int updateCounter;
	bool quitRequested;
	bool mouseState [6] = {false};
	int mouseUpdate [6] = {0};
	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;

	static InputManager* instance;

	InputManager();

public:
	~InputManager();
	void Update();
	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);
	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	int GetMouseX();
	int GetMouseY();
	bool QuitRequested();
	static InputManager& GetInstance();
};

#endif /* INPUTMANAGER_H_ */
