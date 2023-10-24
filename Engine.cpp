#include "Engine.h"

SDL_Texture* playerTexture;

void Engine::Init(const char* title, int x, int y, int w, int h, bool fScreen)
{
	bool flag = 0;
	if (fScreen)
	{
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "System is Initialised..." << std::endl;
		window = SDL_CreateWindow(title, x, y, w, h, flag);
		if (window)
		{
			std::cout << "Window is created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer is created!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	SDL_Surface* Surface = IMG_Load("bg/download1.jpg");
	if (!Surface)
	{
		std::cout << "Can't load image!" << std::endl;
	}
	playerTexture = SDL_CreateTextureFromSurface(renderer, Surface);
	SDL_FreeSurface(Surface);
}

void Engine::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Engine::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, playerTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Engine::update()
{
	count++;
	std::cout << count << std::endl;
}

void Engine::clean()
{	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game is cleaned by System" << std::endl;
}