
#include "player.hpp"
#include "config.hpp"

#include <cstdio>


Player::Player(const char* path, SDL_Renderer* renderer, int _x, int _y)
	: Texture(path, renderer), startX(_x), startY(_y)
{
	reset();
}

Player::~Player(){}

void Player::reset()
{
	v = a = 0;
	posX = startX;
	posY = startY;
	s = (double)startY;
	jumped = false;
	dead = false;
}


void Player::restartGame()
{
	if (dead)
	{
		reset();
	}
}

bool Player::isDead(){
    return dead;
}

void Player::die(){
	dead = true;
}

void Player::jump(){
	jumped = true;
	v = V_0;
	if (DEBUG) printf("***jumped!\tv:%.2f\tposY:%d\n", v, posY);
}

void Player::updatePosition()
{
	if (!jumped || dead)
	{
		return;
	}

	// TODO use SDL_GetTicks will probably be more accurate for time calculation
	double t = 0.001*LOOP_DELAY;

	s = s - v*t + 0.5*(ACCEL*t*t);
	v = v - ACCEL*t;

	if (v > V_MAX)
	{
		v = V_MAX;
	}
	else if (v < -V_MAX)
	{
		v = -V_MAX;
	}

	posY = (int)s;
	if (DEBUG) printf("s: %.2f\tv: %.2f\tposY: %d\n", s, v, posY);
}

void Player::render(SDL_Renderer *renderer)
{
	Texture::render(renderer, posX, posY);
}

// TODO if we don't need to use getV and hasJumped in the project,
// do we still need them for the unit test
double Player::getV()
{
	return v;
}

bool Player::hasJumped()
{
	return jumped;
}

SDL_Rect Player::getPlayerRect()
{
	SDL_Rect rect = {posX,posY,width,height};
	return rect;
}

