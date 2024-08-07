#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "render_window.cpp"
#include "Font.cpp"
#include "Texture.cpp"
#include "Button.cpp"
#include "Colors.cpp"
#include "Utils.cpp"
#include "vector2f.cpp"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 728;

int updateMultiplier(int score)
{
	if (score > 500)
	{
		 return 4;
	}
	else if (score > 100)
	{
		return 3;
	}
	else if (score > 50)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

int main()
{
	if (!GUI::Utils::Init())
	{
		return 1;
	}
	
	GUI::RenderWindow window("Shape Calculator", WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Window* WINDOW = window.getWindow();
	SDL_Renderer* RENDERER = window.getRenderer();
	
	GUI::Font RobotoFont64("/system/fonts/Roboto-Regular.ttf", 64);
	GUI::Font RobotoFont128("/system/fonts/Roboto-Regular.ttf", 128);
	GUI::Font RobotoFont72("/system/fonts/Roboto-Regular.ttf", 72);
	
	GUI::Texture buttonTex;
	
	GUI::Button Buttons[2] =
	{
		GUI::Button(RENDERER, vector2f(500, 600), "Click!", buttonTex, RobotoFont64, Black),
		GUI::Button(RENDERER, vector2f(500, 600), "FPS", buttonTex, RobotoFont64, Black),
	};
	
	GUI::Button button;
	button.create(RENDERER, vector2f(500, 600), "Click!", buttonTex, RobotoFont64, Black);
	
	SDL_Color Grey = GUI::LerpColor(White, Black, 0.5);
	
	vector2f mousePos;
	int mouseX, mouseY;
	
	SDL_Event event;
	
	bool gameRunning = true;
	int i = 0;
	int multiplier = 1;
	
	const int MAX_FRAME_HISTORY = 10;
		
	float accumulator = 0.00f;
	float frameTimes[MAX_FRAME_HISTORY];
	int currentFrameIndex = 0;
	
	int FPS = 60;
	
	Uint64 previousTime = SDL_GetPerformanceCounter();
	float deltaTime = 1.0f / FPS;
	
	while(gameRunning)
	{
		Uint64 currentTime = SDL_GetPerformanceCounter();
		float elapsedTime = (currentTime - previousTime) / (float)SDL_GetPerformanceFrequency();
		
		previousTime = currentTime;
		accumulator += elapsedTime;
		
		frameTimes[currentFrameIndex] = elapsedTime;
		currentFrameIndex = (currentFrameIndex + 1) % MAX_FRAME_HISTORY;
		if (currentFrameIndex > MAX_FRAME_HISTORY)
		{
			currentFrameIndex = MAX_FRAME_HISTORY;
		}
		
		float averageFrameTime = 0.0f;
    	for (int i = 0; i < MAX_FRAME_HISTORY; ++i)
    	{
      	  averageFrameTime += frameTimes[i];
    	}
   	 averageFrameTime /= MAX_FRAME_HISTORY;

    	int fps = 1.0f / averageFrameTime;
		
		static bool buttonClicked = false;
		
		while (accumulator >= deltaTime)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT:
						gameRunning = true;
						break;
					
					case SDL_MOUSEBUTTONDOWN:
						int mouseX, mouseY;
						SDL_GetMouseState(&mouseX, &mouseY);
						mousePos.x = static_cast<float>(mouseX);
						mousePos.y = static_cast<float>(mouseY);
						if (button.isButtonClicked(mousePos))
						{
							button.setButtonState(GUI::ButtonState::PRESS);
						}
						break;
						
					case SDL_MOUSEMOTION:
						mousePos.x = event.motion.x;
						mousePos.y = event.motion.y;
						if (button.isButtonHovering(mousePos))
						{
							button.setButtonState(GUI::ButtonState::HOVER);
						}
						else
						{
							button.setButtonState(GUI::ButtonState::DEFAULT);
						}
						break;
						
					case SDL_MOUSEBUTTONUP:
						if (button.getButtonState() == GUI::ButtonState::HOVER || button.getButtonState() == GUI::ButtonState::PRESS)
						{
							button.setButtonState(GUI::ButtonState::DEFAULT);
						}
						buttonClicked = false;
				}
			}
			
			accumulator -= deltaTime;
		}
		
		float alpha = accumulator / deltaTime;
		
		if (button.getButtonState() == GUI::ButtonState::PRESS)
		{
			multiplier = updateMultiplier(i);
			if (!buttonClicked)
			{
				i += 1 * multiplier;
			}
			buttonClicked = true;
		}
		
		std::string score = "Points: " + std::to_string(i);
		std::string FPS = "FPS: " + std::to_string(fps);
		
		window.clear();
		
		window.FillScreen(Grey);
		window.drawButton(button);
		
		window.drawText(RobotoFont72, FPS.c_str(), Black, vector2f(1150, 700), GUI::CenteredAlign::YES);
		
		if (i < 1000)
		{
			window.drawText(RobotoFont128, "Reach 1000 to win" , Black, vector2f(640, 100), GUI::CenteredAlign::YES);
		}
		else
		{
			window.drawText(RobotoFont128, "Congrats! You won!" , Black, vector2f(640, 100), GUI::CenteredAlign::YES);
		}
		window.drawText(RobotoFont128, score.c_str(), Black, vector2f(640, 364), GUI::CenteredAlign::YES);
		
		window.present();
		
		if (accumulator > deltaTime)
		{
       	 accumulator = deltaTime;
    	}
    	else 
    	{
       	 float sleepTime = (deltaTime - accumulator) * 1000.0f;
      	  SDL_Delay(static_cast<Uint32>(sleepTime));
    	}
		
	}
	
	window.cleanUp();
	
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	
	return 0;
}