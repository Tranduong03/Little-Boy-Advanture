#include "Engine.h"

SDL_Texture* Texture, *Texture2;
SDL_Rect scrR, destR;
int character_x = 0, character_y = 0;
int speed = 5;

void Engine::Init(const char* title, int x, int y, int w, int h, bool fScreen)
{
	bool flag = 0;
	if (fScreen)
	{
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Game is Initialised..." << std::endl;
		window = SDL_CreateWindow(title, x, y, w, h, flag);
		if (window)
		{
			std::cout << "Window is created successfully!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer is created succesfully!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}


	Texture = TextureManager::Load_BG("bg/login0.png", renderer); // load images login
	// Texture2 = IMG_LoadTexture(renderer, "images/idle.gif");
}

void Engine::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			Texture = TextureManager::Load_BG("bg/endGame.jpg", renderer);
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			Texture = TextureManager::Load_BG("bg/endGame.jpg", renderer);
		}
	}
	else if (event.type == SDL_QUIT)
	{
		isRunning = false;
	}
}

void Engine::update()
{
	count++;
	std::cout << count << std::endl;
}

void Engine::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, Texture, NULL, NULL);
	// SDL_Rect Rect = { character_x, character_y, 100, 100 };
	// SDL_RenderCopy(renderer, Texture2, NULL, &Rect);
	SDL_RenderPresent(renderer);
}

void Engine::clean()
{	
	SDL_DestroyTexture(Texture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
	std::cout << "Game is cleaned by System" << std::endl;
}