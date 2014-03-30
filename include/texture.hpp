#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "SDL2/SDL.h"
#include "config.hpp"

class Texture {

	public:
		// Getters
		int getWidth();
		int getHeight();
		int getPosX();
		int getPosY();
		SDL_Texture* getTexture();

		// Setters
		void setWidth(int w);
		void setHeight(int h);
		void setPosX(int x);
		void setPosY(int y);
		void setTexture(const char*, SDL_Renderer*);

		/**
		 * Copies the texture onto the renderer.
		 * @param renderer The renderer to use.
		 *
		 */
		void renderCopy(SDL_Renderer *renderer);

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

		/**
	     * Deallocates the object
	     */
		~Texture();

	protected:
		SDL_Texture* texture;
		char filename[MAX_PATH_LEN];
		// Height and width for the texture.
		int width;
		int height;
		int posX;
		int posY;
	private:
		void loadTextureFromFile(const char* path, SDL_Renderer* renderer);
		void zeroAll();

};

#endif
