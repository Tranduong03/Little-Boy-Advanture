#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "TextureManager.h"
struct position{
	int x, y;
};

class Engine
{
public:
	static Engine* GetInstance();

	void Init(const char* title, int xpos, int ypos,
		int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();



	position GetMousePosition() {
		position pos;
		int x, y;
		SDL_GetMouseState(&x, &y);
		pos.x = x;
		pos.y = y;
		return pos;
	}

	inline SDL_Renderer* GetRenderer() { return renderer; }
	inline bool running() { return isRunning; };
	inline SDL_Window* GetWindow() { return window; }

	void Menu();
	int MenuChoose();
private:
	static Engine* Instance;

	bool isRunning;
	int count = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
