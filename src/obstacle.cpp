
#include "obstacle.hpp"

// Obstacle class
// TODO: make a new class called entity class, and have player and obstacle and background inherit from that.

static SDL_Rect rectFactory(int x, int y, int w, int h)
{
	SDL_Rect rect = {x, y, w, h};
	return rect;
}

Obstacle::Obstacle() : mStartRect(rectFactory(0, 0, 0, 0)) {}

Obstacle::Obstacle(int x, int y, int w, int h, const char* imageTop, const char* imageBot, SDL_Renderer* renderer)
	: mStartRect(rectFactory(x, y, w, h))
{
	setTexture(imageTop, imageBot, renderer);
	setPositions(x,y,w,h);
	mHasBeenPassed = false;
	mRenderer = renderer;
}

Obstacle::~Obstacle()
{}


void Obstacle::setPosX(int x)
{
	Obstacle::setPositions(x, mRect.y, mRect.w, mRect.h);
}

void Obstacle::setPosY(int y)
{
	Obstacle::setPositions(mRect.x, y, mRect.w, mRect.h);
}

void Obstacle::setWidth(int w)
{
	Obstacle::setPositions(mRect.x, mRect.y, w, mRect.h);
}

void Obstacle::setHeight(int h)
{
	Obstacle::setPositions(mRect.x, mRect.y, mRect.w, h);
}

SDL_Rect Obstacle::getTopRect()
{
	return mRect;
}

SDL_Rect Obstacle::getBotRect()
{
	return mBotRect;
}

void Obstacle::render() const
{
	SDL_RenderCopy(mRenderer, mTopTexture.getTexture(), NULL, &mRect);
	SDL_RenderCopy(mRenderer, mBotTexture.getTexture(), NULL, &mBotRect);
}

void Obstacle::setPositions(int x, int y, int w, int h)
{
	mRect.x = x;
	mRect.y = y;
	mRect.w = w;
	mRect.h = h;

	mBotRect.x = x;
	mBotRect.y = y + OBSTACLE_VGAP + h;
	mBotRect.w = w;
	mBotRect.h = SCREEN_HEIGHT - OBSTACLE_VGAP - y - h;
}

void Obstacle::resetPositions()
{
	mRect.x = mStartRect.x;
	mRect.y = mStartRect.y;
	mRect.w = mStartRect.w;
	mRect.h = mStartRect.h;

	mBotRect.x = mStartRect.x;
	mBotRect.y = mStartRect.y + OBSTACLE_VGAP + mStartRect.h;
	mBotRect.w = mStartRect.w;
	mBotRect.h = SCREEN_HEIGHT - OBSTACLE_VGAP - mStartRect.y - mStartRect.h;

	mHasBeenPassed = false;	
}

void Obstacle::setTexture(const char* imageTop, const char* imageBot, SDL_Renderer* renderer)
{
	mTopTexture.resetTexture(imageTop, renderer, true);
	mBotTexture.resetTexture(imageBot, renderer, true);
}

