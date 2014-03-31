// collidable class, subclass of texture
#ifndef _COLLIDABLE_HPP_
#define _COLLIDABLE_HPP_

#include "texture.hpp"

class Collidable : public Texture
{
	public:
		Collidable(const char* path, SDL_Renderer* renderer, int _x, int _y);
		~Collidable();
	protected:
		bool isCollided();
		const int startX;
		const int startY;
};

#endif
