// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_INPUTMANAGER_H_
#define INCLUDE_INPUTMANAGER_H_

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
#define MOVE_UP_KEY 6
#define MOVE_DOWN_KEY 7
#define ACTIVE_KEY 8
#define HOT_KEY_1 9
#define HOT_KEY_2 10
#define HOT_KEY_3 11
#define INT_SIZE_MAX 2147483647
#define INT_SIZE_MIN -2147483648

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
	int translationTable[12];
	int lastKey;

	static InputManager *instance;

	InputManager();

 public:
	~InputManager();
	void Update();
	int TranslateKey(int key);
	bool KeyPress(int key, bool translate = 0);
	bool KeyRelease(int key, bool translate = 0);
	bool IsKeyDown(int key, bool translate = 0);
	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	void SetTranslationKey(int src, int dest);
	int GetMouseX();
	int GetMouseY();
	int GetTranslationKey(int key);
	int GetLastKey();
	bool QuitRequested();
	static InputManager & GetInstance();
};

#endif // INCLUDE_INPUTMANAGER_H_
