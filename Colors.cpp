#ifndef COLOR_CPP_
#define COLOR_CPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const SDL_Color Red = {255, 0, 0, 255};
const SDL_Color Green = {0, 255, 0, 255};
const SDL_Color Blue = {0, 0, 255, 255};
const SDL_Color White = {255, 255, 255, 255};
const SDL_Color Black = {0, 0, 0, 255};

namespace GUI
{
	SDL_Color LerpColor(const SDL_Color c1, const SDL_Color c2, const float t)
	{
		SDL_Color result;
		result.r = (uint8_t)(c1.r * (1 - t) + c2.r * t);
		result.g = (uint8_t)(c1.g * (1 - t) + c2.g * t);
		result.b = (uint8_t)(c1.b * (1 - t) + c2.b * t);
		result.a = (uint8_t)(c1.a * (1 - t) + c2.a * t);
		
		return result;
	}
	
	bool isColorEqual(const SDL_Color& color1, const SDL_Color& color2) {
    return color1.r == color2.r &&
           color1.g == color2.g &&
           color1.b == color2.b &&
           color1.a == color2.a;
}
}

#endif