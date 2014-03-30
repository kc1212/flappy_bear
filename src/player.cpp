
#include "player.hpp"
#include "config.hpp"

#include <cstdio>

// Player::Player() : Texture()
// {
// }

Player::Player(const char* path, SDL_Renderer* renderer, int _x, int _y) : Texture(path, renderer)
{
	v = a = 0;
	posX = _x;
	posY = _y;
	s = (double)_y;
	jumped = false;
}

Player::~Player(){}

void Player::jump(){
	jumped = true;
	v = V_0;
	if (DEBUG) printf("***jumped!\tv:%.2f\tposY:%d\n", v, posY);
}

void Player::die(){
	printf("died!\n");
}

void Player::updatePosition()
{
	if (!jumped) return;
	double t = 0.001*LOOP_DELAY;

	s = s - v*t + 0.5*(G*t*t);
	v = v - G*t;

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

