
// timer class, primarily used for setting fps

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
//	void pause();
//	void unpause();

	Uint32 getTicks();
	bool isStarted(){ return mStarted; }
	bool isPaused(){ return mPaused; }

private:
	Uint32 mStartTicks;
	Uint32 mPauseTicks;

	bool mPaused;
	bool mStarted;
};
