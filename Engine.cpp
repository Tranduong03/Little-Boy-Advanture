#include "Engine.h"
#include "TextureManager.h"

SDL_Rect scrR, destR;
SDL_Texture* Texture;
int character_x = 0, character_y = 0;

Engine* Engine::Instance = nullptr;

Engine* Engine::GetInstance() {
	return Instance = (Instance != nullptr) ? Instance : new Engine();
}

bool Engine::Init(const char* title, int x, int y, int w, int h, bool fScreen)
{
	bool flag = 0;
	isRunning = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Game is Initialised..." << std::endl;
		// create window
		window = SDL_CreateWindow(title, x, y, w, h, flag);
		if (window)
		{
			std::cout << "Window is created successfully!" << std::endl;
		}
		else {
			return isRunning = false;
		}
		// create renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer is created succesfully!" << std::endl;
		}
		else {
			return isRunning = false;
		}
	}
	else {
		return isRunning = false;
	}

	TextureManager::GetInstance()->Load("bg1", "bg/login0.png");
	TextureManager::GetInstance()->Load("bg2", "bg/endGame.jpg");

	TextureManager::GetInstance()->Load("quit", "bg/quit.png");
	TextureManager::GetInstance()->Load("quitClick", "bg/quitClick.png");

	TextureManager::GetInstance()->Load("play", "bg/play.png");
	TextureManager::GetInstance()->Load("playClick", "bg/playClick.png");

	TextureManager::GetInstance()->Load("tutorial", "bg/tutorial.png");
	TextureManager::GetInstance()->Load("tutorialClick", "bg/tutorialClick.png");

	TextureManager::GetInstance()->Load("BACK", "bg/backIcon.jpg");
	TextureManager::GetInstance()->Load("BACKClick", "bg/backIconClick.jpg");
	TextureManager::GetInstance()->Load("tutorialScreen", "bg/TUTORIALSCR.png");

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
			std::cout << event.button.x << " " << event.button.y << endl;
		}

	}
	else if (event.type == SDL_QUIT)
	{
		isRunning = false;
	}
}

void Engine::update()
{

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
	std::cout << std::endl << "Game is cleaned all by System" << std::endl;
}

void Engine::Menu() {
	// sound.playMusic(ENTER_THE_GAME, 1);
	int check = Input();
	while (check != 0) 
	{
		if (check == 1) {
			Tutorial();
		}
		check = Input();
	}
}

int Engine::Input() {
	SDL_RenderClear(renderer);
	TextureManager::GetInstance()->Draw("bg1", 0, 0, 1280, 720);

	int l_Menu = 300, t_Menu = 240;

	TextureManager::GetInstance()->Draw("play", l_Menu, t_Menu, 200, 43);
	TextureManager::GetInstance()->Draw("tutorial", l_Menu, t_Menu + 80, 200, 43);
	TextureManager::GetInstance()->Draw("quit", l_Menu, t_Menu + 160, 200, 43);

	SDL_Event e;
	while (isRunning) {
		SDL_Delay(10);
		SDL_PollEvent(&e);

		switch (e.type) {
		case SDL_QUIT:
			clean();
			isRunning = false;
			return 0;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT) 
			{
				// play game
				if (e.button.x >= l_Menu && e.button.x <= l_Menu + 200 && e.button.y >= t_Menu && e.button.y <= t_Menu + 43) 
				{
					TextureManager::GetInstance()->Draw("play", l_Menu, t_Menu, 200, 43);
					BeforePlay();
				}
				// tutorial
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + 200 && e.button.y >= t_Menu + 80 && e.button.y <= t_Menu + 123) 
				{
					TextureManager::GetInstance()->Draw("tutorial", l_Menu, t_Menu + 80, 200, 43);
					return 1;

				}
				// quit
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + 200 && e.button.y >= t_Menu + 160 && e.button.y <= t_Menu + 203) 
				{
					TextureManager::GetInstance()->Draw("quit", l_Menu, t_Menu + 160, 200, 43);
					clean();
					isRunning = false;
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT) 
			{
				// play game
				if (e.button.x >= l_Menu && e.button.x <= l_Menu + 200 && e.button.y >= t_Menu && e.button.y <= t_Menu + 43) 
				{
					// sound.playMusic(Click, 1);
					TextureManager::GetInstance()->Draw("playClick", l_Menu, t_Menu, 200, 43);
				}
				// tutorial
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + 200 && e.button.y >= t_Menu + 80 && e.button.y <= t_Menu + 123) 
				{
					// sound.playMusic(Click, 1);
					TextureManager::GetInstance()->Draw("tutorialClick", l_Menu, t_Menu + 80, 200, 43);
				}
				// quit
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + 200 && e.button.y >= t_Menu + 160 && e.button.y <= t_Menu + 203) 
				{
					// sound.playMusic(Click, 1);
					TextureManager::GetInstance()->Draw("quitClick", l_Menu, t_Menu + 160, 200, 43);
				}
			}
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				clean();
				return 0;
			}
			break;
		}
		SDL_RenderPresent(renderer);
	}
}

void Engine::Tutorial() {
	SDL_RenderClear(renderer);

	TextureManager::GetInstance()->Draw("tutorialScreen", 0, 0, 1280, 720);
	TextureManager::GetInstance()->Draw("BACK", 1180, 20, 70, 70);

	SDL_Event e;
	while (1) {
		SDL_PollEvent(&e);
		SDL_Delay(10);
		switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT) 
			{
				if (e.button.x >= 1180 && e.button.x <= 1260 && e.button.y >= 20 && e.button.y <= 100) {
					TextureManager::GetInstance()->Draw("BACKClick", 1180, 20, 70, 70);
					// return;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				if (e.button.x >= 1180 && e.button.x <= 1260 && e.button.y >= 20 && e.button.y <= 100) {
					return;
				}
			}
			break;
		case SDL_QUIT:
			clean();
			isRunning = false;
		}
		SDL_RenderPresent(renderer);
	}
}

int Engine::BeforePlay() {
	SDL_RenderClear(renderer);
	TextureManager::GetInstance()->Draw("bg1", 0, 0, 1280, 720);
	TextureManager::GetInstance()->Draw("easy", 400, 100, 85, 85);
	TextureManager::GetInstance()->Draw("normal", 600, 100, 85, 85);
	TextureManager::GetInstance()->Draw("hard", 800, 100, 85, 85);

	SDL_RenderPresent(renderer);

	SDL_Event e;
	while (1) {
		SDL_PollEvent(&e);
		SDL_Delay(10);
		switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT) {
				if (e.button.x >= 400 && e.button.x <= 485 && e.button.y >= 100 && e.button.y <= 185) {
					return -1;
				}
			}
			break;
		case SDL_QUIT:
			clean();
			isRunning = false;
			exit(0);
		}
		SDL_RenderPresent(renderer);
	}
}