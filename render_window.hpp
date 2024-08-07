#ifndef RENDER_WINDOW_HPP
#define RENDER_WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/include/GUI/Textures/Texture.hpp"
#include "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/include/GUI/Textures/Font.hpp"
#include "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/include/GUI/Textures/Button.hpp"
#include "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/include/GUI/Utilities/vector2f.hpp"


namespace GUI
{
class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_width, int p_height);
	
	void FillScreen(SDL_Color color);
	void drawTexture(Texture& p_tex, vector2f pos, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void drawText(Font& p_font, const char* p_text, SDL_Color color, vector2f pos, GUI::CenteredAlign CAlign);
	void drawButton(Button& button);
	
	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;
	int getRefreshRate();
	
	void clear();
	void present();
	void cleanUp();
		
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
}

#endif