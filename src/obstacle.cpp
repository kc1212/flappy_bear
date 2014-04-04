
#include "obstacle.hpp"

// Obstacle class
// TODO: make a new class called entity class, and have player and obstacle and background inherit from that.

void Obstacle::setPosX(int x)
{
	Obstacle::setAttrs(x,posY,width,height);
}

void Obstacle::setPosY(int y)
{
	Obstacle::setAttrs(posX,y,width,height);
}

void Obstacle::setWidth(int w)
{
	Obstacle::setAttrs(posX,posY,w,height);
}

void Obstacle::setHeight(int h)
{
	Obstacle::setAttrs(posX,posY,width,h);
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
    SDL_SetRenderDrawColor(renderer, 0xFF,0,0,0xFF);
    SDL_RenderDrawRect(renderer, &topRect);
    SDL_RenderDrawRect(renderer, &botRect);

    SDL_SetRenderDrawColor(renderer, 0,0,0xFF,0xFF);
    SDL_RenderFillRect(renderer, &topRect);
    SDL_RenderFillRect(renderer, &botRect);
}

SDL_Rect Obstacle::getTopRect()
{
	return topRect;
}

SDL_Rect Obstacle::getBotRect()
{
	return botRect;
}


void Obstacle::setAttrs(int x, int y, int w, int h)
{
    posX = x;
    posY = y;
    width = w;
    height = h;
    SDL_Rect obstacleTop = {posX,posY,width,height};
    SDL_Rect obstacleBot = {posX, posY + OBSTACLE_VGAP + height, width, SCREEN_HEIGHT - OBSTACLE_VGAP - posY - height};
    topRect = obstacleTop;
    botRect = obstacleBot;
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
