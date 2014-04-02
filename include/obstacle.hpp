#ifndef _OBSTACLES_HPP_
#define _OBSTACLES_HPP_

#include "SDL2/SDL.h"

// TODO this class doesn't subclass from Texture. But it should subclass something in common with player, maybe create a entity class to contain all the posx,posy,w,h in entity and keep the renderering code in Texture.
// and have player multiple inherit from Texture and Entity.

class Obstacle
{
	public:
		int getPosX();
		int getPosY();
		int getWidth();
		int getHeight();

		void setPosX(int x);
		void setPosY(int y);
		void setWidth(int w);
		void setHeight(int h); 

		void render(SDL_Renderer *renderer);
		Obstacle(int x, int y, int w, int h);
		~Obstacle();

	private:
		int posX;		
		int posY;
		int width;
		int height;
};
#endif
