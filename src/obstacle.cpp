
#include "obstacle.hpp"

// Obstacle class
// TODO: make a new class called entity class, and have player and obstacle and background inherit from that.

void Obstacle::setPosX(int x)
{
	Obstacle::setPositions(x,posY,width,height);
}

void Obstacle::setPosY(int y)
{
	Obstacle::setPositions(posX,y,width,height);
}

void Obstacle::setWidth(int w)
{
	Obstacle::setPositions(posX,posY,w,height);
}

void Obstacle::setHeight(int h)
{
	Obstacle::setPositions(posX,posY,width,h);
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

SDL_Rect Obstacle::getTopRect()
{
	return topRect;
}

SDL_Rect Obstacle::getBotRect()
{
	return botRect;
}

void Obstacle::render(SDL_Renderer *renderer)
{
	topObstacle.render(renderer);
	botObstacle.render(renderer);
}

void Obstacle::setPositions(int x, int y, int w, int h)
{
	posX = x;
	posY = y;
	width = w;
	height = h;

	topObstacle.setPosX(posX);
	topObstacle.setPosY(posY);
	topObstacle.setWidth(width);
	topObstacle.setHeight(height);
	topRect = (SDL_Rect){posX,posY,width,height};

	botObstacle.setPosX(posX);
	botObstacle.setPosY(posY + OBSTACLE_VGAP + height);
	botObstacle.setWidth(width);
	botObstacle.setHeight(SCREEN_HEIGHT - OBSTACLE_VGAP - posY - height);
	botRect = (SDL_Rect){posX,posY + OBSTACLE_VGAP + height,width,SCREEN_HEIGHT - OBSTACLE_VGAP - posY - height};
}

void Obstacle::setTexture(const char* imageTop, const char* imageBot, SDL_Renderer* renderer)
{
	topObstacle.resetTexture(imageTop, renderer);
	botObstacle.resetTexture(imageBot, renderer);
}

Obstacle::Obstacle() {}

Obstacle::Obstacle(int x, int y, int w, int h, const char* imageTop, const char* imageBot, SDL_Renderer* renderer)
{
	setTexture(imageTop, imageBot, renderer);
	setPositions(x,y,w,h);
}

Obstacle::~Obstacle()
{}

