#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_image.h>
#include "TextureManager.h"

class Engine
{
public:
	void Init(const char* title, int xpos, int ypos,
		int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; };
private:
	bool isRunning;
	int count = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
