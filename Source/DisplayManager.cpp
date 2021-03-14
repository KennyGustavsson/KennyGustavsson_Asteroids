#include "displayManager.h"

SDL_Window* DisplayManager::window = nullptr;
SDL_Renderer* DisplayManager::renderer = nullptr;
vector2* DisplayManager::screenSize = nullptr;

void DisplayManager::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	screenSize = new vector2(width, height);

	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING == -1)) 
	{
		std::cout << SDL_GetError() << std::endl;
	}

	window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
	if (window == nullptr) 
	{
		std::cout << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) 
	{
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
