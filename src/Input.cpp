/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: Input.cpp
 * Header File Name: Input.h
 * Class Name: Input
 * Objective:
 */

#include "Input.h"

/**
 * Objective: it constructs Input object.
 *
 * @param type typeParam.
 * @return instance of Input.
 */
Input::Input(type typeParam): typeObject(typeParam) {
    if (typeObject == type::SLIDER) {
        // loadingBar = new LoadingBar("sliderMenu.png", 5,1 5, 10);
    } else {
        // It does nothing.
    }
}

/**
 * Objective:
 *
 * @param Vec2 position.
 * @return none.
 */
void Input::SetPosition(Vec2 position) {
    if ((position.x >= INT_MIN_SIZE && position.x <= INT_MAX_SIZE) &&
            (position.y >= INT_MIN_SIZE && position.y <= INT_MAX_SIZE)) {
        this->position = position;
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it sets input value.
 *
 * @param float value.
 * @return none.
 */
void Input::SetValue(float value) {
    if (value >= FLOAT_MIN_SIZE && value <= FLOAT_MAX_SIZE) {
        this->value = value;
        if (typeObject == type::SLIDER) {
            loadingBar->SetPercentage(value);
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it sets input option.
 *
 * @param int option.
 * @return none.
 */
void Input::SetOption(int option) {
    if (option >= FLOAT_MIN_SIZE && option <= FLOAT_MAX_SIZE) {
        this->option = option;
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it sets input text.
 *
 * @param string text.
 * @return none.
 */
void Input::SetText(std::string text) {
    this->text = text;
}

/**
 * Objective: it gets input value.
 *
 * @param none.
 * @return float value.
 */
float Input::GetValue() {
    return value;
}

/**
 * Objective: it gets input option.
 *
 * @param none.
 * @return int option.
 */
int Input::GetOption() {
    return option;
}

/**
 * Objective: it gets input position.
 *
 * @param none.
 * @return Vec2 position.
 */
Vec2 Input::GetPosition() {
    return position;
}

/**
 * Objective: it gets inpput size.
 *
 * @param none.
 * @return Vec2 'size'.
 */
Vec2 Input::GetSize() {
    if (typeObject == type::SLIDER) {
        return loadingBar->GetSize();
    } else {
        return Vec2(1.0, 1.0);
    }
}

/**
 * Objective: it gets string input text.
 *
 * @param none.
 * @return string text.
 */
std::string Input::GetText() {
    return text;
}

/**
 * Objective: it renders.
 *
 * @param none.
 * @return none.
 */
void Input::Render() {
    if (typeObject == type::SLIDER) {
        loadingBar->Render(position.x, position.y);
    } else {
        // It does nothing.
    }
}
