#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "SDL2/SDL.h"
#include "config.hpp"

class Texture {

	public:
		// Getters
		int getWidth();
		int getHeight();
		SDL_Texture* getTexture() const;

		// Setters
		void setWidth(int w);
		void setHeight(int h);
		void resetTexture(const char*, SDL_Renderer*);
		
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
		 * @param w Initial width
		 * @param h Initial height
		 */
		Texture(const char* path, SDL_Renderer* renderer, int w, int h);

		/**
		 * Deallocates the object
		 */
		~Texture();

	protected:
		SDL_Texture* mTexture;
		char mFilename[MAX_PATH_LEN];
		int mWidth, mHeight;
		// Height and width for the texture.


	private:
		bool loadTextureFromFile(const char* path, SDL_Renderer* renderer);
		void zeroAll();

};

#endif
