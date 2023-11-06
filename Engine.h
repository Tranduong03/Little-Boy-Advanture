#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "TextureManager.h"

class Engine
{
public:
	static Engine* GetInstance();

	bool Init(const char* title, int xpos, int ypos,
		int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	inline SDL_Renderer* GetRenderer() { return renderer; }
	inline SDL_Window* GetWindow() { return window; }
	inline bool running() { return isRunning; };

	void Menu();
	int Input();
	void Tutorial();
	int BeforePlay();
private:
	static Engine* Instance;

	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

};
