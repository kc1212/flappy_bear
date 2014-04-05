
#include "player.hpp"
#include "config.hpp"

#include <cstdio>


Player::Player(const char* path, SDL_Renderer* renderer, int startX, int startY)
	: mStartX(startX), mStartY(startY), mTexture(path, renderer)
{	
	mRenderer = renderer;
	mRect.w = mTexture.getWidth();
	mRect.h = mTexture.getHeight();
	reset();
}

Player::~Player(){}

void Player::reset()
{
	mVelocity = mAcceleration = 0;
	mRect.x = mStartX;
	mRect.y = mStartY;
	mDisplacement = static_cast<double>(mStartY);
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
	if (DEBUG) printf("***jumped!\tv:%.2f\tmRect.y:%d\n", mVelocity, mRect.y);
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

	mRect.y = static_cast<int>(mDisplacement);
	if (DEBUG) printf("s: %.2f\tv: %.2f\tmRect.y: %d\n", mDisplacement, mVelocity, mRect.y);
}

void Player::render() const
{
	SDL_RenderCopy(mRenderer, mTexture.getTexture(), NULL, &mRect);
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


