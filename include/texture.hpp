#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "SDL2/SDL.h"
#include "config.hpp"

class Texture {

	public:
		SDL_Texture* getTexture();
		void setTexture(const char*, SDL_Renderer*);

		int getWidth();
		void setWidth(int w);

		int getHeight();
		void setHeight(int h);

		int getPosX();
		int getPosY();
		void setPosX(int x);
		void setPosY(int y);

		/**
		 * Renders the texture onto the screen.
		 * @param renderer The renderer to use.
		 *
		 */
		void render(SDL_Renderer *renderer);

		/**
		 * Default constructor.
		 */ 
		Texture();

		/**
		 * Construct a texture with an asset.
		 * @param path The file path to the asset.
		 * @param renderer The renderer to render the asset.
		 */
		Texture(const char* path, SDL_Renderer* renderer);
		~Texture();

	protected:
		SDL_Texture* texture;
		char filename[MAX_PATH_LEN];
		// Height and width for the texture.
		int width;
		int height;
		int positionX;
		int positionY;
	private:
		void loadTextureFromFile(const char* path, SDL_Renderer* renderer);

};

#endif
