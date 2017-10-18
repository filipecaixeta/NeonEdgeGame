/**
 * Copyright 2017 Neon Edge Game
 * File Name: State.cpp
 * Header File Name: State.h
 * Class Name: State
 * Objective: manages the states.
 */

#include "State.h"
#include "Game.h"

State::State():
    bg(),
    music(),
    quitRequested(false) {
}

State::~State() {
}

void State::Render() {
}

void State::Update() {
}

/*
 * Objective: center vertical position from sprite.
 *
 * @param: Sprite* sp.
 * @return: Vec2 CenterVertical.
 */
Vec2 State::CenterVertical(Sprite *sp) {
    return CenterVertical(sp->GetWidth());
}

/*
 * Objective: center vertical position from sprite.
 *
 * @param: int size.
 * @return: Vec2.
 */
Vec2 State::CenterVertical(int size) {
    if (size >= INT_MIN_SIZE && size <= INT_MAX_SIZE) {
        SDL_Point windowSize = Game::GetInstance().GetScreenSize();
        return Vec2((windowSize.x-size)/2, 0);
    } else {
        // It does nothing.
    }
}

/*
 * Objective: center vertical position from sprite.
 *
 * @param: Vec2 size.
 * @return: Vec2.
 */
Vec2 State::CenterVertical(Vec2 size) {
    float vec_size_x = 0.0f;
    vec_size_x = size.x;
    if (vec_size_x >= FLOAT_MIN_SIZE && vec_size_x <= FLOAT_MAX_SIZE){
        return CenterVertical(vec_size_x);
    } else {
        // It does nothing.
    }
}

/*
 * Objective: center horizontal position from sprite.
 *
 * @param: none.
 * @return: none.
 */
Vec2 State::CenterHorizontal(Sprite *sp) {
    return CenterHorizontal(sp->GetHeight());
}

/*
 * Objective: center horizontal position from sprite.
 *
 * @param: int size.
 * @return: Vec2.
 */

Vec2 State::CenterHorizontal(int size) {
    if (size >= INT_MIN_SIZE && size <= INT_MAX_SIZE) {
        SDL_Point windowSize = Game::GetInstance().GetScreenSize();
        return Vec2(0,(windowSize.y-size)/2);
    } else {
        // It does nothing.
    }
}

/*
 * Objective: center horizontal position from sprite.
 *
 * @param: Vec2 size.
 * @return: Vec2.
 */
Vec2 State::CenterHorizontal(Vec2 size) {
    float vec_size_y = 0.0f;
    vec_size_y = size.y;
    if (vec_size_y >= FLOAT_MIN_SIZE && vec_size_y <= FLOAT_MAX_SIZE){
        return CenterVertical(vec_size_y);
    } else {
        // It does nothing.
    }

}

/*
 * Objective: get state and return it.
 *
 * @param: none.
 * @return: State* this state.
 */
State* State::get() {
    return this;
}

/*
 * Objective: set quit request state.
 *
 * @param: none.
 * @return: bool quitRequested.
 */
bool State::QuitRequested() {
    return quitRequested;
}
