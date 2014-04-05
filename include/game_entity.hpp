#include "SDL2/SDL.h"

class GameEntity {
	public: 
		// Initiation
		GameEntity();
		~GameEntity();

		// Getters & Setters
		int getPosX(){return mPosX;}
		int getPosY(){return mPosY;}
		int getWidth(){return mWidth;}
		int getHeight(){return mHeight;}
		void setPosX(int x){mPosX = x;}
		void setPosY(int y){mPosY = y;}
		void setWidth(int w){mWidth = w;}
		void setHeight(int h){mHeight = h;}

	protected:		
		int mPosX, mPosY, mWidth, mHeight;
		SDL_Renderer* mRenderer;

};

