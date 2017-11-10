/**
 * Copyright 2017 Neon Edge Game
 * File Name: InputManager.cpp
 * Header File Name: InputManager.h
 * Class Name: InputManager
 * Objective: it manages system input commands.
 */

#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

/**
 * Objective: it constructs the Input Manager object.
 *
 * @param none.
 * @return instace of Input Manager.
 */
InputManager::InputManager(): mouseX(0), mouseY(0), updateCounter(0), quitRequested(false),
                              mouseState{ false }, mouseUpdate{ 0 },
                              translationTable{ SDLK_SPACE, SDLK_e, SDLK_q, SDLK_a, SDLK_d, SDLK_s,
                              SDLK_w, SDLK_s, SDLK_z, SDLK_j, SDLK_k, SDLK_l } {
}

InputManager::~InputManager() {
}

/**
 * Objective: it updates system input events.
 *
 * @param none.
 * @return none.
 */
void InputManager::Update() {
    SDL_GetMouseState(&mouseX, &mouseY);
    if (updateCounter < 100) {
        updateCounter++;
    } else {
        updateCounter = 0;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.key.repeat != 1) {
            if (event.type == SDL_QUIT) {
                quitRequested = true;
            } else {
                // It does nothing.
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
            } else {
                // It does nothing.
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
            } else {
                // It does nothing.
            }

            if (event.type == SDL_KEYDOWN) {
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                lastKey = event.key.keysym.sym;
            } else {
                // It does nothing.
            }

            if (event.type == SDL_KEYUP) {
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            } else {
                // It does nothing.
            }
        } else {
            // It does nothing.
        }
    }
}

/**
 * Objective: it translate key
 *
 * @param int key - pressed key value.
 * @return int translatedKey - translated key value.
 */
int InputManager::TranslateKey(int key) {
    int translatedKey = translationTable[key];

    return translatedKey;
}

/**
 * Objective: it checks if some key was pressed.
 *
 * @param int key - pressed key value.
 * @param bool translate - transtate status.
 * @return bool keyPressStatus.
 */
bool InputManager::KeyPress(int key, bool translate) {
    if (translate) {
        key = TranslateKey(key);
    } else {
        // It does nothing.
    }

    bool keyPressStatus = false;

    if (keyUpdate[key] == updateCounter) {
        keyPressStatus = keyState[key];
    } else {
        keyPressStatus = false;
    }

    return keyPressStatus;
}

/**
 * Objective: it checks if some key was released.
 *
 * @param int key - pressed key value.
 * @param bool translate - transtate status.
 * @return bool keyReleaseStatus.
 */
bool InputManager::KeyRelease(int key, bool translate) {
    if (translate) {
        key = TranslateKey(key);
    } else {
        // It does nothing.
    }

    bool keyReleaseStatus = false;

    if (keyUpdate[key] == updateCounter) {
        keyReleaseStatus = !keyState[key];
    } else {
        keyReleaseStatus = false;
    }

    return keyReleaseStatus;
}

/**
 * Objective: it checks if some key is pressed.
 *
 * @param int key - pressed key value.
 * @param bool translate - transtate status.
 * @return keyIsDownStatus.
 */
bool InputManager::IsKeyDown(int key, bool translate) {
    if (translate) {
        key = TranslateKey(key);
    } else {
        // It does nothing.
    }

    bool keyIsDownStatus = keyState[key];

    return keyIsDownStatus;
}

/**
 * Objective: it checks if mouse button was pressed.
 *
 * @param bool button - pressed button value.
 * @return mousePressStatus.
 */
bool InputManager::MousePress(int button) {
    bool mousePressStatus = false;

    if (mouseUpdate[button] == updateCounter) {
        mousePressStatus = mouseState[button];
    } else {
        mousePressStatus = false;
    }

    return mousePressStatus;
}

/**
 * Objective: it checks if mouse button was released.
 *
 * @param bool button - pressed button value.
 * @return mouseReleaseStatus.
 */
bool InputManager::MouseRelease(int button) {
    bool mouseReleaseStatus = false;

    if (mouseUpdate[button] == updateCounter) {
        mouseReleaseStatus = !mouseState[button];
    } else {
        mouseReleaseStatus = false;
    }

    return mouseReleaseStatus;
}

/**
 * Objective: it checks if mouse button is pressed.
 *
 * @param bool button - pressed button value.
 * @return mouseIsDownStatus.
 */
bool InputManager::IsMouseDown(int button) {
    bool mouseIsDownStatus = mouseState[button];

    return mouseIsDownStatus;
}

/**
 * Objective: it sets the translations of keys values.
 *
 * @param int src - key to be setted.
 * @param int dest - value to be setted in the key.
 * @return none.
 */
void InputManager::SetTranslationKey(int src, int dest) {
    translationTable[src] = dest;
}

/**
 * Objective: it gets mouse position in x axis.
 *
 * @param none.
 * @return int mouseX - mouse position in x axis value.
 */
int InputManager::GetMouseX() {
    return mouseX;
}

/**
 * Objective: it gets mouse position in y axis.
 *
 * @param none.
 * @return int mouseY - mouse position in y axis value.
 */
int InputManager::GetMouseY() {
    return mouseY;
}

/**
 * Objective: it gets the translations of keys values.
 *
 * @param int key - pressed key value.
 * @return translationKey.
 */
int InputManager::GetTranslationKey(int key) {
    int translationKey = translationTable[key];

    return translationKey;
}

/**
 * Objective: it gets last key.
 *
 * @param none.
 * @return int temp - last key value.
 */
int InputManager::GetLastKey() {
    int temp = lastKey;
    lastKey = -1;

    return temp;
}

/**
 * Objective: it checks if quit was requested.
 *
 * @param none.
 * @return bool quitRequested - quit request status.
 */
bool InputManager::QuitRequested() {
    return quitRequested;
}

/**
 * Objective: it gets Input Manager object.
 *
 * @param none.
 * @return InputManager instance - Input Manager object.
 */
InputManager & InputManager::GetInstance() {
    if (instance == nullptr) {
        instance = new InputManager();
    } else {
        // It does nothing.
    }

    return *instance;
}
