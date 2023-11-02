#include "Engine.h"
#include "TextureManager.h"

SDL_Texture* Texture, *Texture2;
SDL_Rect scrR, destR;
int character_x = 0, character_y = 0;
int speed = 5;
position pos = { 0,0 };

Engine* Engine::Instance = nullptr;

Engine* Engine::GetInstance() {
	return Instance = (Instance != nullptr) ? Instance : new Engine();
}

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

	TextureManager::GetInstance()->Load("bg1", "bg/login0.png");
	TextureManager::GetInstance()->Load("bg2", "bg/endGame.jpg");

	TextureManager::GetInstance()->Load("quit", "bg/quit.png");
	TextureManager::GetInstance()->Load("quitClick", "bg/quitClick.png");
	
	//Texture = TextureManager::Load_BG("bg/login0.png", renderer); // load images login
	// Texture2 = IMG_LoadTexture(renderer, "images/idle.gif");
}

void Engine::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			//Texture = TextureManager::Load_BG("bg/endGame.jpg", renderer);
			
			pos = GetMousePosition();
			std::cout << pos.x << " " << pos.y << endl;
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
	// std::cout << count << std::endl;
}

void Engine::render()
{
	SDL_RenderClear(renderer);
	
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

void Engine::Menu() {
	int check = MenuChoose();
	while (check != 0) {
		check = MenuChoose();
	}

}

int Engine::MenuChoose() {
	SDL_RenderClear(renderer);
	TextureManager::GetInstance()->Draw("bg2", 0, 0, 1280, 720);
	TextureManager::GetInstance()->Draw("quit", 400, 600, 200, 43);
	SDL_Event e;
	while (1) {
		SDL_PollEvent(&e);
		SDL_Delay(10);
		switch (e.type) {
			case SDL_QUIT:
				clean();
				isRunning = false;
				exit(0);
				return 0;
			case SDL_MOUSEBUTTONUP:
				if (e.button.button == SDL_BUTTON_LEFT) {
					position mouseplace = GetMousePosition();
					if (mouseplace.x >= 400 && mouseplace.x <= 600 && mouseplace.y >= 600 && mouseplace.y <= 643) {
						TextureManager::GetInstance()->Draw("quit", 400, 600, 200, 43);
						exit(0);
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT) {
					position mouseplace = GetMousePosition();
					if (mouseplace.x >= 400 && mouseplace.x <= 600 && mouseplace.y >= 600 && mouseplace.y <= 643) {
						TextureManager::GetInstance()->Draw("quitClick", 400, 600, 200, 43);
					}
				}
				break;
		}
		SDL_RenderPresent(renderer);
	}
}