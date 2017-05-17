#include "State.h"


State::State():
	bg(),
	music(),
	quitRequested(false)
{

}

State::~State()
{

}

void State::Render()
{

}

void State::Update()
{

}

State* State::get() {
	return this;
}

bool State::QuitRequested() {
	return quitRequested;
}
