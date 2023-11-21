#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "TextureManager.h"
#include "GenMap.h"
#include "SDL_ttf.h"
#include "stdrand.h"
#include <sstream>
#include "FileScore.h"

#define SCR_W 1280
#define SCR_H 720
#define PixelSIZE 46

struct position {
	int x;
	int	y;
};

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
	void Score();
	int BeforePlay();
	int FinishGame();
	void RenderText(const char*, int, int, SDL_Color, int);
	void RenderText2(const char*, int, int, SDL_Color, int);
	void restart();
	int InputName();
	void Output_Score();
	void Read_Score();

private:
	static Engine* Instance;
	int stat = 0;
	SDL_Event usingEvent;
	bool isRunning = true;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
