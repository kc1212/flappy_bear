#ifndef _BACKGROUND_HPP_
#define _BACKGROUND_HPP_

#include "SDL2/SDL.h"
#include "utils.hpp"

class Background {

	public:
		SDL_Texture* getBG();
		void setBG(const char*, SDL_Renderer*);

		Background();
		Background(const char*, SDL_Renderer*);

		~Background();

	private:
		SDL_Texture* bg;
};

#endif
