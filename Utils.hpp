#ifndef GUI_UTILS_HPP_
#define GUI_UTILS_HPP_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace GUI
{
	namespace Utils
	{
		
		bool Init()
		{
			// Initialize SDL
			if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
			{
				std::cout << "Error during Initialization [Subsystems]. Error: " << SDL_GetError() << '\n';
				return false;
			}
	
	    	// Initialize SDL_image
			if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF)))
			{
				std::cout << "Error during Initialization [Image]. Error: " << SDL_GetError() << '\n';
				return false;
			}
			
			return true;
		}
		
		inline float hireTimeInSeconds()
		{
			float t = SDL_GetTicks();
			t *= 0.001f;
			return t;
		}
		
	}
}

#endif