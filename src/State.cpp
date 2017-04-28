#include "State.h"

State::~State() {

}

void State::LoadAssets() {

}

void State::Update() {

}

void State::Render() {

}

bool State::QuitRequested() {
	return quitRequested;
}

bool State::Is(std::string type) {
	return (type == "State");
}

State* State::get() {
	return this;
}
