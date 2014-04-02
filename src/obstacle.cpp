
#include "obstacle.hpp"

// Obstacle class
// TODO: make a new class called entity class, and have player and obstacle and background inherit from that.

void Obstacle::setPosX(int x)
{
	posX = x;
}

void Obstacle::setPosY(int y)
{
	posY = y;
}

void Obstacle::setWidth(int w)
{
	width = w;
}

void Obstacle::setHeight(int h)
{
	height = h;
}

int Obstacle::getPosX()
{
	return posX;
}

int Obstacle::getPosY()
{
	return posY;
}

int Obstacle::getWidth()
{
	return width;
}

int Obstacle::getHeight()
{
	return height;
}

void Obstacle::render(SDL_Renderer *renderer)
{
	SDL_Rect obstacleRect = {posX,posY,width,height};
	SDL_SetRenderDrawColor(renderer, 255,0,0,255);
	SDL_RenderDrawRect(renderer, &obstacleRect);	
	SDL_RenderFillRect(renderer, &obstacleRect);
}

void Obstacle::setAttrs(int x, int y, int w, int h)
{
    posX = x;
    posY = y;
    width = w;
    height = h;
}

Obstacle::Obstacle() {}

Obstacle::Obstacle(int x, int y, int w, int h)
{
    setAttrs(x,y,w,h);
}

Obstacle::~Obstacle()
{
	posX = 0;
	posY = 0;
	width = 0;
	height = 0;
}
