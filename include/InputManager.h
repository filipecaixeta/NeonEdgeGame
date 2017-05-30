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

#define JUMP_KEY 0
#define ATTACK_KEY 1
#define SPECIAL_KEY 2
#define MOVE_LEFT_KEY 3
#define MOVE_RIGHT_KEY 4
#define CROUCH_KEY 5

#include "SDL.h"
#include <unordered_map>

class InputManager {
private:
	int mouseX;
	int mouseY;
	int updateCounter;
	bool quitRequested;
	bool mouseState [6];
	int mouseUpdate [6];
	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;
	int translationTable[6];
	int lastKey;

	static InputManager* instance;

	InputManager();

public:
	~InputManager();
	void Update();
	int TranslateKey(int key);
	bool KeyPress(int key,bool translate=0);
	bool KeyRelease(int key,bool translate=0);
	bool IsKeyDown(int key,bool translate=0);
	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	void SetTranslationKey(int src, int dest);
	int GetMouseX();
	int GetMouseY();
	int GetTranslationKey(int key);
	int GetLastKey();
	bool QuitRequested();
	static InputManager& GetInstance();
};

#endif /* INPUTMANAGER_H_ */
