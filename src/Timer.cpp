#include "Timer.h"
#include <algorithm>

Timer::Timer()
{

}

Timer::Timer(float limit)
{
	Timer::limit = limit;
}

Timer::~Timer()
{

}

void Timer::Start()
{
	time = 0;
    running = true;
}

void Timer::Stop()
{
    running = false;
}

void Timer::Update(float dt)
{
    if(running)
    {
        time += dt;
        if (time >= limit)
            running = false;
    }
}

void Timer::SetLimit(float l)
{
    limit = l;
}

bool Timer::isRunning()
{
    return running;
}

float Timer::getElapsed()
{
    return std::min(1.0f,time/limit);
}
