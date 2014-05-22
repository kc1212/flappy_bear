#include "SDL2/SDL.h"
#ifndef _GAME_ENTITY_HPP_
#define _GAME_ENTITY_HPP_


class GameEntity {
	public: 
		// Initiation
		GameEntity();
		virtual ~GameEntity();

		// Getters
		SDL_Rect getRect() { return mRect; }
		int getPosX(){ return mRect.x; }
		int getPosY(){ return mRect.y; }
		int getWidth(){ return mRect.w; }
		int getHeight(){ return mRect.h; }

		// setters
		void setPosX(int x){ mRect.x = x; }
		void setPosY(int y){ mRect.y = y; }
		void setWidth(int w){ mRect.w = w; }
		void setHeight(int h){ mRect.h = h; }
		void setRect(SDL_Rect r){ mRect = r; }

		virtual void render() const = 0;


	protected:
		SDL_Rect mRect;
		SDL_Renderer* mRenderer;

};

#endif

