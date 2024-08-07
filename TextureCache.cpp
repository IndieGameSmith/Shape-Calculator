#ifndef TEXTURECACHE_CPP_
#define TEXTURECACHE_CPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <map>
#include <string>

namespace GUI
{

struct CachedTexture
{
	SDL_Texture* texture;
};

class TextureCache
{
	
public:
	TextureCache();
	~TextureCache();
	
	SDL_Texture* getTexture(SDL_Renderer* renderer, const std::string& p_path);
	
	void clear();
	
private:
	std::map<std::string, CachedTexture> cache;
};

TextureCache :: TextureCache()
{
	
}

TextureCache :: ~TextureCache()
{
	clear();
}

SDL_Texture* TextureCache :: getTexture(SDL_Renderer* renderer, const std::string& p_path)
{
    auto it = cache.find(p_path);
    if (it != cache.end()) {
        return it->second.texture;
    }

    CachedTexture* texture = new CachedTexture();
    
    SDL_Surface* textureSurface = IMG_Load(p_path.c_str());
	if (textureSurface == nullptr)
	{
		std::cout << "Failded to load surface: " << SDL_GetError() << '\n';
		delete texture;
		return nullptr;
	}
	
    texture->texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
    if (texture->texture == nullptr)
    {   SDL_FreeSurface(textureSurface);
        delete texture;
        return nullptr;
    }
    cache[p_path] = *texture;
    return texture->texture;
}

void TextureCache :: clear()
{
    for (auto& pair : cache) {
        delete &pair.second;
    }
    cache.clear();
}


}

#endif