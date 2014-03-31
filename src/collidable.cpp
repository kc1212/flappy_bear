
#include "collidable.hpp"
#include <cstdio>

Collidable::Collidable(const char* path, SDL_Renderer* renderer, int _x, int _y)
	: Texture(path, renderer), startX(_x), startY(_y) {}

Collidable::~Collidable() {}

bool Collidable::isCollided()
{
	// TODO only checking bountry at the moment, need to collision detection for other objects
	if (posY <= -10 || posY >= SCREEN_HEIGHT - height + 10)
	{
		if (DEBUG) printf("***collided!\tposY: %d\n", posY);
		return true;
	}
	return false;
}

