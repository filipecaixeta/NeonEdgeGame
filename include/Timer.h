#ifndef TIMER_H_
#define TIMER_H_

#define MAX_FLOAT 3.4e+38f
#define MIN_FLOAT  -3.4e+38f
#define MAX_INT 3767.0f
#define MIN_INT -3767.0f

class Timer {
public:
	Timer();
	Timer(float limit);
	~Timer();
	void Start();
    void Stop();
    void Reset();
	void Update(float dt);
	void SetLimit(float l);
	bool IsRunning();
	float GetElapsed();
	float GetTime();

private:

	float time = 0;
	float limit = 0;
	bool running = false;

};

#endif /* TIMER_H_ */
