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
		void resetTexture(const char*, SDL_Renderer*);

		/**
		 * Copies the texture onto the renderer.
		 * @param renderer The renderer to use.
		 * @param x The x coord to render.
		 * @param y The y coord to render.
		 *
		 */
		void render(SDL_Renderer *renderer, int x, int y);

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
		 * Construct a texture with an asset plus initial position.
		 * @param path The file path to the asset.
		 * @param renderer The renderer to render the asset.
		 * @param _x Initial X coordinate
		 * @param _y Initial Y coordinate
		 */
		Texture(const char* path, SDL_Renderer* renderer, int _x, int _y);

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
		bool loadTextureFromFile(const char* path, SDL_Renderer* renderer);
		void zeroAll();

};

#endif
