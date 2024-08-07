#include "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/include/GUI/Rendering/render_window.hpp"

#include "Texture.cpp"
#include "Font.cpp"
#include "vector2f.cpp"
#include "Button.cpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>

GUI::RenderWindow ::RenderWindow(const char* p_title, int p_width, int p_height) : window(nullptr), renderer(nullptr)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_width, p_height, SDL_WINDOW_SHOWN);
	if(window == nullptr)
	{
		std::cout << "Window creation failed. Due to: " << SDL_GetError();
	}
		
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "Renderer creation failed. Due to: " << SDL_GetError();
	}
		
}

//RENDERING RELATED FUNCTIONS
void GUI::RenderWindow :: FillScreen(SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    
	SDL_Rect FillRect = {0, 0, windowWidth, windowHeight};
	SDL_RenderFillRect(renderer, &FillRect);
}

void GUI::RenderWindow :: drawTexture(Texture& p_tex,vector2f pos, double angle = 0.00, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = p_tex.getWidth();
	src.h = p_tex.getHeight();

	SDL_Rect dst;
	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopyEx(renderer, p_tex.getSDLtexture(), &src, &dst, angle, center, flip);
}

void GUI::RenderWindow :: drawText(Font& p_font, const char* p_text, SDL_Color color, vector2f pos, GUI::CenteredAlign CAlign = GUI::CenteredAlign::NO)
{
	SDL_Texture* texture = p_font.CreateTextTexture(renderer, p_text, color);
	if (texture == nullptr)
	{
		std::cout << "Failded to load Texture: " << SDL_GetError() << '\n';
		return;
	}
	
	int textWidth, textHeight;
	SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);
	
	SDL_Rect dest;
    dest.w = textWidth;
    dest.h = textHeight;
    
	switch (CAlign)
	{
		case GUI::CenteredAlign::YES:
		    dest.x = pos.x - textWidth / 2;
		    dest.y = pos.y - textHeight / 2;
		    break;
		case GUI::CenteredAlign::NO:
			dest.x = pos.x;
			dest.y = pos.y;
			break;
	}
    
    SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0.00, nullptr, SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
    
}


//Entity type Rendering
void GUI::RenderWindow :: drawButton(Button& button)
{
	SDL_Rect buttonRect = button.getButtonRect();
	
	switch (button.getButtonState())
	{
		case ButtonState::HOVER:
			SDL_RenderCopy(renderer, button.getButtonHoverTexture(), nullptr, &buttonRect);
			break;
		
		case ButtonState::PRESS:
			SDL_RenderCopy(renderer, button.getButtonHoverTexture(), nullptr, &buttonRect);
			break;
		
		case ButtonState::DEFAULT:
			SDL_RenderCopy(renderer, button.getButtonNormalTexture(), nullptr, &buttonRect);
			break;
	}
	SDL_Rect textRect = button.getTextRect();
	SDL_RenderCopy(renderer, button.getTextTexture(), nullptr, &textRect);
}

void GUI::RenderWindow :: clear()
{
	SDL_RenderClear(renderer);
}

void GUI::RenderWindow :: present()
{
	SDL_RenderPresent(renderer);
}

void GUI::RenderWindow :: cleanUp()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

SDL_Window* GUI::RenderWindow :: getWindow() const
{
	return window;
}

SDL_Renderer* GUI::RenderWindow :: getRenderer() const
{
	return renderer;
}

int GUI::RenderWindow :: getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}