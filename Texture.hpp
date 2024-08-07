#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/include/GUI/Utilities/vector2f.hpp"

namespace GUI
{
class Texture
{
public:
	Texture();
	Texture(SDL_Renderer* p_renderer, const char* p_path);
	Texture(SDL_Texture* p_tex);
	~Texture();
	
	void loadFromFile(SDL_Renderer* p_renderer, const char* p_path);
	void loadTexture(SDL_Texture* p_tex);
	void unload();
	
	SDL_Texture* loadTextureFromFile(SDL_Renderer* p_renderer, const char* p_path);
	
	int getWidth();
	int getHeight();
	SDL_Texture* getSDLtexture();
	
	void render(SDL_Renderer* rederer, vector2f pos, double angle, SDL_Point* center, SDL_RendererFlip flip);
	
private:
	SDL_Texture* texture;
	int width, height;
};
}

#endif