#ifndef _BACKGROUND_HPP_
#define _BACKGROUND_HPP_

#include "texture.hpp"

class Background : public Texture {
	public:
		Background();
		Background(const char*, SDL_Renderer*);
		~Background();
	private:
		bool shaded;
};

#endif
