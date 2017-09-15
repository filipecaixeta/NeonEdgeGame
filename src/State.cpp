/*
  Copyright 2017 Neon Edge Game
  File Name: State.cpp
  Header File Name: State.h
  Class Name: State
  Objective: manages the states.
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
  Function Objective: center vertical position from sprite.
  param: none.
  return: none.
 */

Vec2 State::CenterVertical(Sprite *sp) {
    return CenterVertical(sp->GetWidth());
}

/*
  Function Objective: center vertical position from sprite.
  param: none.
  return: none.
 */

Vec2 State::CenterVertical(int size) {
    SDL_Point windowSize = Game::GetInstance().GetScreenSize();
    return Vec2((windowSize.x-size)/2,0);
}

/*
  Function Objective: center vertical position from sprite.
  param: none.
  return: none.
 */

Vec2 State::CenterVertical(Vec2 size) {
    return CenterVertical(size.x);
}

/*
  Function Objective: center horizontal position from sprite.
  param: none.
  return: none.
 */

Vec2 State::CenterHorizontal(Sprite *sp) {
    return CenterHorizontal(sp->GetHeight());
}

/*
  Function Objective: center horizontal position from sprite.
  param: none.
  return: none.
 */

Vec2 State::CenterHorizontal(int size) {
    SDL_Point windowSize = Game::GetInstance().GetScreenSize();
    return Vec2(0,(windowSize.y-size)/2);
}

/*
  Function Objective: center horizontal position from sprite.
  param: none.
  return: none.
 */

Vec2 State::CenterHorizontal(Vec2 size) {
    return CenterHorizontal(size.y);
}

/*
  Function Objective: get state and return it.
  param: none.
  return: none.
 */

State* State::get() {
    return this;
}

/*
  Function Objective: set quit request state.
  param: none.
  return: none.
 */

bool State::QuitRequested() {
    return quitRequested;
}
