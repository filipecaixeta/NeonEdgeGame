#include "Timer.h"

Timer::Timer() {

}

Timer::Timer(float limit) {
	time = -1;
	Timer::limit = limit;
}

Timer::~Timer() {

}

void Timer::Start() {
	time = 0;
}

void Timer::Update(float dt) {
	time += dt;
}

void Timer::Reset() {
	time = -1;
}

float Timer::GetTime() {
	return time;
}

float Timer::GetLimit() {
	return limit;
}
