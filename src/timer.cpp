#include <SDL.h>
#include "timer.hpp"

Timer::Timer()
{
	mStartTicks = 0;
	mPauseTicks = 0;
	mPaused = false;
	mStarted = false;
}

Timer::~Timer(){}

void Timer::start()
{
	mStarted = true;
	mPaused = false;
	mStartTicks = SDL_GetTicks();
	mPauseTicks = 0;
}

void Timer::stop()
{
	mStarted = false;
	mPaused = false;
	mStartTicks = 0;
	mPauseTicks = 0;
}

Uint32 Timer::getTicks()
{
	Uint32 t = 0;

	if (isStarted())
	{
		if (isPaused())
		{
			t = mPauseTicks;
		}
		else
		{
			t = SDL_GetTicks() - mStartTicks;
		}
	}

	return t;
}



