#ifndef TEXTURE_CPP_
#define TEXTURE_CPP_

#include "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/include/GUI/Textures/Texture.hpp"
#include "vector2f.cpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

GUI::Texture :: Texture(){}

GUI::Texture :: Texture(SDL_Renderer* p_renderer, const char* p_path)
{
	SDL_Surface* textureSurface = IMG_Load(p_path);
	if (textureSurface == nullptr)
	{
		std::cout << "Failded to load surface: " << SDL_GetError() << '\n';
		texture = nullptr;
	}
	
	texture = SDL_CreateTextureFromSurface(p_renderer, textureSurface);
	if (texture == nullptr)
	{
		std::cout << "Failded to load surface: " << SDL_GetError() << '\n';
		SDL_FreeSurface(textureSurface);
		texture = nullptr;
	}
	
	if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0)
	{
        std::cerr << "Failed to query texture dimensions: " << SDL_GetError() << std::endl;
        texture = nullptr;
        return;
    }
}

GUI::Texture :: Texture(SDL_Texture* p_tex)
{
	texture = p_tex;
	if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0)
	{
        std::cerr << "Failed to query texture dimensions: " << SDL_GetError() << std::endl;
        return;
    }
}

GUI::Texture :: ~Texture()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}
	texture = nullptr;
}

void GUI::Texture :: loadFromFile(SDL_Renderer* p_renderer, const char* p_path)
{
	SDL_Surface* textureSurface = IMG_Load(p_path);
	if (textureSurface == nullptr)
	{
		std::cout << "Failded to load surface: " << SDL_GetError() << '\n';
		texture = nullptr;
	}
	
	texture = SDL_CreateTextureFromSurface(p_renderer, textureSurface);
	if (texture == nullptr)
	{
		std::cout << "Failded to load surface: " << SDL_GetError() << '\n';
		SDL_FreeSurface(textureSurface);
		texture = nullptr;
	}
	
	if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0)
	{
        std::cerr << "Failed to query texture dimensions: " << SDL_GetError() << std::endl;
        texture = nullptr;
        return;
    }
}

void GUI::Texture :: loadTexture(SDL_Texture* p_tex)
{
	texture = p_tex;
	if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0)
	{
        std::cerr << "Failed to query texture dimensions: " << SDL_GetError() << std::endl;
        return;
    }
}

void GUI::Texture :: unload()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}
	texture = nullptr;
}

SDL_Texture* GUI::Texture :: loadTextureFromFile(SDL_Renderer* p_renderer, const char* p_path)
{
	SDL_Surface* textureSurface = IMG_Load(p_path);
	if (textureSurface == nullptr)
	{
		std::cout << "Failded to load surface: " << SDL_GetError() << '\n';
		texture = nullptr;
	}
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface(p_renderer, textureSurface);
	if (tex == nullptr)
	{
		std::cout << "Failded to load surface: " << SDL_GetError() << '\n';
		SDL_FreeSurface(textureSurface);
		texture = nullptr;
	}
	
	return tex;
}

int GUI::Texture :: getWidth()
{
	return width;
}

int GUI::Texture :: getHeight()
{
	return height;
}

SDL_Texture* GUI::Texture :: getSDLtexture()
{
	return texture;
}

void GUI::Texture :: render(SDL_Renderer* renderer, vector2f pos, double angle = 0.00, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = width;
	src.h = height;
	
	SDL_Rect dst;
	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = src.w;
	dst.h = src.h;
	
	SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, center, flip);
}

#endif