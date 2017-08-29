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

Vec2 State::CenterVertical(Sprite *sp) {
    return CenterVertical(sp->GetWidth());
}

Vec2 State::CenterVertical(int size) {
    SDL_Point windowSize = Game::GetInstance().GetScreenSize();
    return Vec2((windowSize.x-size)/2,0);
}

Vec2 State::CenterVertical(Vec2 size) {
    return CenterVertical(size.x);
}

Vec2 State::CenterHorizontal(Sprite *sp) {
    return CenterHorizontal(sp->GetHeight());
}

Vec2 State::CenterHorizontal(int size) {
    SDL_Point windowSize = Game::GetInstance().GetScreenSize();
    return Vec2(0,(windowSize.y-size)/2);
}

Vec2 State::CenterHorizontal(Vec2 size) {
    return CenterHorizontal(size.y);
}

State* State::get() {
    return this;
}

bool State::QuitRequested() {
    return quitRequested;
}
