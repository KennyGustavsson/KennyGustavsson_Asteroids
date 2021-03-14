#pragma once
#include "vector2.h"
#include <iostream>

static class DisplayManager
{
public:
	static void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static vector2* screenSize;
};