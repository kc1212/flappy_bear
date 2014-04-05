
#include "obstacle.hpp"

// Obstacle class
// TODO: make a new class called entity class, and have player and obstacle and background inherit from that.

void Obstacle::setPosX(int x)
{
	Obstacle::setPositions(x,mPosY,mWidth,mHeight);
}

void Obstacle::setPosY(int y)
{
	Obstacle::setPositions(mPosX,y,mWidth,mHeight);
}

void Obstacle::setWidth(int w)
{
	Obstacle::setPositions(mPosX,mPosY,w,mHeight);
}

void Obstacle::setHeight(int h)
{
	Obstacle::setPositions(mPosX,mPosY,mWidth,h);
}

SDL_Rect Obstacle::getTopRect()
{
	return mTopRect;
}

SDL_Rect Obstacle::getBotRect()
{
	return mBotRect;
}

void Obstacle::render(SDL_Renderer *renderer)
{
	mTopTexture.render(renderer);
	mBotTexture.render(renderer);
}

void Obstacle::setPositions(int x, int y, int w, int h)
{
	mPosX = x;
	mPosY = y;
	mWidth = w;
	mHeight = h;

	mTopTexture.setPosX(mPosX);
	mTopTexture.setPosY(mPosY);
	mTopTexture.setWidth(mWidth);
	mTopTexture.setHeight(mHeight);
	mTopRect = (SDL_Rect){mPosX,mPosY,mWidth,mHeight};

	mBotTexture.setPosX(mPosX);
	mBotTexture.setPosY(mPosY + OBSTACLE_VGAP + mHeight);
	mBotTexture.setWidth(mWidth);
	mBotTexture.setHeight(SCREEN_HEIGHT - OBSTACLE_VGAP - mPosY - mHeight);
	mBotRect = (SDL_Rect){mPosX,mPosY + OBSTACLE_VGAP + mHeight,mWidth,SCREEN_HEIGHT - OBSTACLE_VGAP - mPosY - mHeight};
}

void Obstacle::setTexture(const char* imageTop, const char* imageBot, SDL_Renderer* renderer)
{
	mTopTexture.resetTexture(imageTop, renderer);
	mBotTexture.resetTexture(imageBot, renderer);
}

Obstacle::Obstacle() {}

Obstacle::Obstacle(int x, int y, int w, int h, const char* imageTop, const char* imageBot, SDL_Renderer* renderer)
{
	setTexture(imageTop, imageBot, renderer);
	setPositions(x,y,w,h);
	mHasBeenPassed = false;
}

Obstacle::~Obstacle()
{}

