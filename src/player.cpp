
#include "player.hpp"
#include "config.hpp"
#include "utils.hpp"


Player::Player(const char* path, SDL_Renderer* renderer, int startX, int startY)
	: mStartX(startX), mStartY(startY), mTexture(path, renderer, true)
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
	if (mDead)
	{
		return;
	}

	mJumped = true;
	mVelocity = V_0;
	log_info("jumped! [v:%.2f, mRect.y:%d]", mVelocity, mRect.y);
}

void Player::updatePosition()
{
	if (!mJumped)
	{
		return;
	}

	// Once player falls out of bounds dont let it keep falling
	if (mRect.y >= SCREEN_HEIGHT)
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
	if (DEBUG) debug("player data [s:%.2f, v:%.2f, mRect.y:%d]", mDisplacement, mVelocity, mRect.y);
}

void Player::render() const
{
	if ( 0 != SDL_RenderCopy(mRenderer, mTexture.getTexture(), NULL, &mRect))
	{
		log_err("player render copy failed! SDL_Error: %s", SDL_GetError());
	}
	if (DEBUG) debug("player renderer: [ptr:%p, texture:%p, x:%d, y:%d, w:%d, h:%d]",
					  (void*)mRenderer, (void*)mTexture.getTexture(), mRect.x, mRect.y, mRect.w, mRect.h);
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


