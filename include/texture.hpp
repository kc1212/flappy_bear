#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "SDL2/SDL.h"
#include "config.hpp"

class Texture {

	public:
		SDL_Texture* getTexture();
		void setTexture(const char*, SDL_Renderer*);

		Texture();
		Texture(const char*, SDL_Renderer*);
		~Texture();

	protected:
		SDL_Texture* texture;
		char filename[MAX_PATH_LEN];
};

#endif
