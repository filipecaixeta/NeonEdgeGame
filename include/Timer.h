/*
 * Timer.h
 *
 *  Created on: 12 de abr de 2017
 *      Author: Gabriel
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer {
private:
	float time = 0;
	float limit = 0;
    bool running = false;

public:
	Timer();
	Timer(float limit);
	~Timer();
	void Start();
    void Stop();
	void Update(float dt);
	void Reset();
	float GetTime();
	float GetLimit();
    void SetLimit(float l);
    bool isRunning();
    float getElapsed();
};

#endif /* TIMER_H_ */
