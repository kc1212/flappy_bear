
#include "player.hpp"
#include "config.hpp"

#include <cstdio>


Player::Player(const char* path, SDL_Renderer* renderer, int startX, int startY)
	: mTexture(path, renderer), mStartX(startX), mStartY(startY)
{	
	mRenderer = renderer;
	mWidth = mTexture.getWidth();
	mHeight = mTexture.getHeight();
	reset();
}

Player::~Player(){}

void Player::reset()
{
	mVelocity = mAcceleration = 0;
	mPosX = mStartX;
	mPosY = mStartY;
	mDisplacement = (double)mStartY;
	mJumped = false;
	mDead = false;
}


void Player::restartGame()
{
	if (mDead)
	{
		reset();
	}
}

bool Player::isDead(){
	return mDead;
}

void Player::die(){
	mDead = true;
}

void Player::jump(){
	mJumped = true;
	mVelocity = V_0;
	if (DEBUG) printf("***jumped!\tv:%.2f\tmPosY:%d\n", mVelocity, mPosY);
}

void Player::updatePosition()
{
	if (!mJumped || mDead)
	{
		return;
	}

	// TODO use SDL_GetTicks will probably be more accurate for time calculation
	double t = 0.001*LOOP_DELAY;

	mDisplacement = mDisplacement - mVelocity*t + 0.5*(ACCEL*t*t);
	mVelocity = mVelocity - ACCEL*t;

	if (mVelocity > V_MAX)
	{
		mVelocity = V_MAX;
	}
	else if (mVelocity < -V_MAX)
	{
		mVelocity = -V_MAX;
	}

	mPosY = (int)mDisplacement;
	if (DEBUG) printf("s: %.2f\tv: %.2f\tmPosY: %d\n", mDisplacement, mVelocity, mPosY);
}

void Player::render()
{
	SDL_Rect renderQuad = {mPosX, mPosY, mWidth, mHeight};	
	SDL_RenderCopy(mRenderer, mTexture.getTexture(), NULL, &renderQuad);
}

// TODO if we don't need to use getV in the project,
// do we still need them for the unit test
double Player::getV()
{
	return mVelocity;
}

bool Player::hasJumped()
{
	return mJumped;
}

SDL_Rect Player::getPlayerRect()
{
	SDL_Rect rect = {mPosX,mPosY,mWidth,mHeight};
	return rect;
}

