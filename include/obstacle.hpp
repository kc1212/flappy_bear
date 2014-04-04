#ifndef _OBSTACLES_HPP_
#define _OBSTACLES_HPP_

#include "SDL2/SDL.h"
#include "texture.hpp"

// TODO this class doesn't subclass from Texture. But it should subclass something in common with player, maybe create a entity class to contain all the posx,posy,w,h in entity and keep the renderering code in Texture.
// and have player multiple inherit from Texture and Entity.

class Obstacle
{
	public:
		int getPosX();
		int getPosY();
		int getWidth();
		int getHeight();
		SDL_Rect getTopRect();
		SDL_Rect getBotRect();

		void setPosX(int x);
		void setPosY(int y);
		void setWidth(int w);
		void setHeight(int h);
		void setPositions(int x, int y, int w, int h);

		void setTexture(const char*, const char*, SDL_Renderer*);
		void render(SDL_Renderer *renderer);

		Obstacle();
		Obstacle(int x, int y, int w, int h, const char*, const char *);
		Obstacle(int x, int y, int w, int h, const char*, const char*, SDL_Renderer*);
		~Obstacle();

	private:
		int posX;
		int posY;
		int width;
		int height;
		SDL_Rect topRect;
		SDL_Rect botRect;
		Texture topObstacle;
		Texture botObstacle;
};
#endif


