#ifndef BUTTON_CPP_
#define BUTTON_CPP_

#include "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/include/GUI/Textures/Button.hpp"

#include "Font.cpp"
#include "vector2f.cpp"
#include "Texture.cpp"
#include "Colors.cpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

GUI::Button :: Button()
{
	
}

GUI::Button :: Button(SDL_Renderer* renderer, vector2f pos, const char* text, Texture p_tex, Font p_font, SDL_Color p_TextColor, ButtonMode mode = ButtonMode::BUTTON)
{
	ButtonRect.x = pos.x;
    ButtonRect.y = pos.y;
    Bstate = ButtonState::DEFAULT;
	TextColor = p_TextColor;
	tex = p_tex;
	font = p_font;
	currentText = text;
	
	TextFont = font.getFont();
	TextTexture = font.CreateTextTexture(renderer, text, TextColor);
	
	SDL_QueryTexture(TextTexture, nullptr, nullptr, &textWidth, &textHeight);
	
	intializeTexture(renderer, tex, mode);

	TextRect = { ButtonRect.x + (ButtonRect.w - textWidth) / 2,
	             ButtonRect.y + (ButtonRect.h - textHeight) / 2,
	             textWidth,
	             textHeight };
}

GUI::Button :: ~Button()
{
	if (ButtonNormalTexture != nullptr)
	{
		SDL_DestroyTexture(ButtonNormalTexture);
	}
	ButtonNormalTexture = nullptr;
	
	if (ButtonHoverTexture != nullptr)
	{
		SDL_DestroyTexture(ButtonHoverTexture);
	}
	ButtonHoverTexture = nullptr;
	
	if (TextTexture != nullptr)
	{
		SDL_DestroyTexture(TextTexture);
	}
	TextTexture = nullptr;
	
	if (TextFont != nullptr)
	{
		TTF_CloseFont(TextFont);
	}
	TextFont = nullptr;
}

void GUI::Button :: create(SDL_Renderer* renderer, vector2f pos, const char* text, Texture p_tex, Font p_font, SDL_Color p_TextColor, ButtonMode mode = ButtonMode::BUTTON)
{
	ButtonRect.x = pos.x;
    ButtonRect.y = pos.y;
    Bstate = ButtonState::DEFAULT;
	TextColor = p_TextColor;
	tex = p_tex;
	font = p_font;
	currentText = text;
	
	TextFont = font.getFont();
	TextTexture = font.CreateTextTexture(renderer, text, TextColor);
	
	SDL_QueryTexture(TextTexture, nullptr, nullptr, &textWidth, &textHeight);
	
	intializeTexture(renderer, tex, mode);

	TextRect = { ButtonRect.x + (ButtonRect.w - textWidth) / 2,
	             ButtonRect.y + (ButtonRect.h - textHeight) / 2,
	             textWidth,
	             textHeight };
}

void GUI::Button :: destroy()
{
	if (ButtonNormalTexture != nullptr)
	{
		SDL_DestroyTexture(ButtonNormalTexture);
	}
	ButtonNormalTexture = nullptr;
	
	if (ButtonHoverTexture != nullptr)
	{
		SDL_DestroyTexture(ButtonHoverTexture);
	}
	ButtonHoverTexture = nullptr;
	
	if (TextTexture != nullptr)
	{
		SDL_DestroyTexture(TextTexture);
	}
	TextTexture = nullptr;
	
	if (TextFont != nullptr)
	{
		TTF_CloseFont(TextFont);
	}
	TextFont = nullptr;
}

void GUI::Button :: intializeTexture(SDL_Renderer* renderer, Texture tex, ButtonMode mode)
{
	if (mode == ButtonMode::NUM)
	{
	    ButtonNormalTexture = tex.loadTextureFromFile(renderer, "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/res/button_num_normal.png");
	    ButtonHoverTexture = tex.loadTextureFromFile(renderer, "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/res/button_num_hover.png");
	    SDL_QueryTexture(ButtonNormalTexture, nullptr, nullptr, &ButtonRect.w, &ButtonRect.h);
	    return;
	}
	
	ButtonNormalTexture = tex.loadTextureFromFile(renderer, "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/res/button_normal.png");
	ButtonHoverTexture = tex.loadTextureFromFile(renderer, "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/res/button_hover.png");
	SDL_QueryTexture(ButtonNormalTexture, nullptr, nullptr, &ButtonRect.w, &ButtonRect.h);
}

void GUI::Button :: render(SDL_Renderer* renderer)
{
	switch (Bstate)
	{
		case ButtonState::HOVER:
			SDL_RenderCopy(renderer, ButtonHoverTexture, nullptr, &ButtonRect);
			break;
		
		case ButtonState::PRESS:
			SDL_RenderCopy(renderer, ButtonHoverTexture, nullptr, &ButtonRect);
			break;
		
		case ButtonState::DEFAULT:
			SDL_RenderCopy(renderer, ButtonNormalTexture, nullptr, &ButtonRect);
			break;
	}
	SDL_RenderCopy(renderer, TextTexture, nullptr, &TextRect);
}

bool GUI::Button :: isButtonClicked(vector2f pos)
{
    return pos.x >= ButtonRect.x && pos.x <= ButtonRect.x + ButtonRect.w &&
           pos.y >= ButtonRect.y && pos.y <= ButtonRect.y + ButtonRect.h;
}

bool GUI::Button :: isButtonHovering(vector2f pos)
{
    return pos.x >= ButtonRect.x && pos.x <= ButtonRect.x + ButtonRect.w &&
           pos.y >= ButtonRect.y && pos.y <= ButtonRect.y + ButtonRect.h;
}

void GUI::Button :: setButtonState(ButtonState state)
{
	Bstate = state;
}

GUI::ButtonState GUI::Button :: getButtonState() const
{
	return Bstate;
}

SDL_Texture* GUI::Button :: getButtonNormalTexture() const 
{
	return ButtonNormalTexture;
}

SDL_Texture* GUI::Button :: getButtonHoverTexture() const
{
	return ButtonHoverTexture;
}

SDL_Texture* GUI::Button :: getTextTexture() const
{
	return TextTexture;
}

SDL_Rect GUI::Button :: getButtonRect() const
{
	return ButtonRect;
}

SDL_Rect GUI::Button :: getTextRect() const
{
	return TextRect;
}

void GUI::Button :: updateText(SDL_Renderer* renderer, const char* text)
{
	if (strcmp(text, currentText) == 0)
	{
		return;
	}
	
	if (TextTexture != nullptr)
	{
    	SDL_DestroyTexture(TextTexture);
    }
    TextTexture = font.CreateTextTexture(renderer, text, TextColor);
    currentText = text;
}

void GUI::Button :: updateColor(SDL_Renderer* renderer, SDL_Color color)
{
	if (isColorEqual(color, TextColor))
	{
		return;
	}
	TextColor = color;
    if (TextTexture != nullptr)
    {
    	SDL_DestroyTexture(TextTexture);
    }
    TextTexture = font.CreateTextTexture(renderer, currentText, TextColor);
}

void GUI::Button :: updatePos(vector2f buttonPosition)
{
	ButtonRect.x = buttonPosition.x;
    ButtonRect.y = buttonPosition.y;

    TextRect = { ButtonRect.x + (ButtonRect.w - textWidth) / 2,
                 ButtonRect.y + (ButtonRect.h - textHeight) / 2,
                 textWidth,
                 textHeight };
}


#endif