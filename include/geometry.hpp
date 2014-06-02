#ifndef _GEOMETRY_HPP_
#define _GEOMETRY_HPP_

#include "SDL2/SDL.h"
#include "game_entity.hpp"

class Geometry : public GameEntity
{
public:
	Geometry();
	Geometry(SDL_Renderer* renderer, int x, int y, int w, int h);
	~Geometry();
	void render() const;
private:
	int mRed, mGreen, mBlue, mAlpha;
};

#endif
