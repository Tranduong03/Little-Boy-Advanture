#include "Engine.h"
#include "TextureManager.h"

SDL_Rect scrR, destR;
SDL_Texture* Texture;
int character_x = 0, character_y = 0;
position mousePos;
int cur_Score, time_elapsed;

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
		if (TTF_Init() == -1) {
			std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
			return isRunning = false;
		}
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

	TTF_Font* font = TTF_OpenFont("font/fonts.ttf", 72);
	if (!font)
	{
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
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

	TextureManager::GetInstance()->Load("BACK", "bg/backIcon.png");
	TextureManager::GetInstance()->Load("BACKClick", "bg/backIconClick.png");
	TextureManager::GetInstance()->Load("tutorialScreen", "bg/TUTORIALSCR.png");

	TextureManager::GetInstance()->Load("pixel", "bg/play/pixel.jpg");

	TextureManager::GetInstance()->Load("easy", "bg/beforePlay/Easy.jpg");
	TextureManager::GetInstance()->Load("nor", "bg/beforePlay/Normal.jpg");
	TextureManager::GetInstance()->Load("hard", "bg/beforePlay/Advanced.jpg");

	TextureManager::GetInstance()->Load("playingBG", "bg/play/playing_bg.jpg");
	TextureManager::GetInstance()->Load("endBoardBG", "bg/play/khungEnd.jpg");
	TextureManager::GetInstance()->Load("BoomClick", "bg/play/bomb_active.png");
	TextureManager::GetInstance()->Load("restart", "bg/play/playagain.png");
	TextureManager::GetInstance()->Load("home", "bg/play/home.png");
	//Map::GetInstance(12,25,2);

}

void Engine::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	SDL_Delay(10);

	mousePos = { 0, 0 };
	
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		

	}
	else if (event.type == SDL_QUIT)
	{
		isRunning = false;
	}
	usingEvent = event;
	time_elapsed += 10;
}

void Engine::update()
{
	Map::GetInstance()->UpdateMap(mousePos, usingEvent);
	cur_Score = Map::GetInstance()->score();
}

void Engine::render()
{
	SDL_RenderClear(renderer);
	TextureManager::GetInstance()->Draw("playingBG", 0, 0, 1280, 720);

	stringstream ss, s_mine, s_time;
	ss << cur_Score;
	string score = "Score:" + ss.str();
	RenderText(score.c_str(), 250, 640, { 255,255,0 }, 48 );

	int boom = Map::GetInstance()->getBoom();
	s_mine << boom;
	TextureManager::GetInstance()->DrawFrame("pixel", 1050, 640, 50, 50, 0, 9, 50);
	string mine = s_mine.str();
	RenderText(mine.c_str(), 1120, 641, { 255,255,0 }, 48);

	
	s_time << time_elapsed / 500;
	string time = "Time:" + s_time.str();
	RenderText(time.c_str(), 700, 640, { 255,255,0 }, 48);


	Map::GetInstance()->DrawPixel();
	stat = Map::GetInstance()->CheckMap();
	if (stat==0) {
		//Xử lý thua
		position BoomAct = Map::GetInstance()->getcell_locate(mousePos.x, mousePos.y);
		Map::GetInstance()->MapLoseOpen();
		Map::GetInstance()->DrawPixel();
		int rows = Map::GetInstance()->getRows();
		TextureManager::GetInstance()->DrawFrame("BoomClick", (SCR_W - PixelSIZE * rows) / 2 + PixelSIZE * (BoomAct.x), 10 + PixelSIZE * (BoomAct.y), 162, 162, 0, 0, PixelSIZE);
		SDL_RenderPresent(renderer);
		SDL_Delay(2500);
		isRunning = false;
	}
	else if (stat == 1) {
		//Xử lý win
		Map::GetInstance()->MapWinOpen();
		Map::GetInstance()->DrawPixel();
		SDL_RenderPresent(renderer);
		SDL_Delay(2500);
		isRunning = false;
	}
	
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

	SDL_RenderPresent(renderer);
	cout << "Get Event in Input Now" << endl;
	SDL_Event e;
	int m_second = 0;
	while (isRunning) {
		SDL_Delay(10);
		m_second += 10;
		if (m_second % 1000 == 0) cout << m_second/1000 << "s ";
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
					return BeforePlay();
				}
				// tutorial
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + 200 && e.button.y >= t_Menu + 80 && e.button.y <= t_Menu + 123)
				{
					TextureManager::GetInstance()->Draw("tutorial", l_Menu, t_Menu + 160, 200, 43);
					return 1;
				}
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + 200 && e.button.y >= t_Menu + 160 && e.button.y <= t_Menu + 203) 
				{
					TextureManager::GetInstance()->Draw("quit", l_Menu, t_Menu + 160, 200, 43);
					clean();
					exit(0);
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
				cout << "In Input(), mouse Click in:" << e.button.x << " " << e.button.y << endl;
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
	cout << "Event khong nhan duoc, xay ra error" << endl;
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
			TextureManager::GetInstance()->Clean();
			isRunning = false;
			return;
		}
		SDL_RenderPresent(renderer);
	}
}

int Engine::BeforePlay() {
	SDL_RenderClear(renderer);
	TextureManager::GetInstance()->Draw("bg1", 0, 0, 1280, 720);
	TextureManager::GetInstance()->Draw("easy", 400, 100, 85, 85);

	TextureManager::GetInstance()->Draw("nor", 600, 100, 85, 85);

	TextureManager::GetInstance()->Draw("hard", 800, 100, 85, 85);

	SDL_RenderPresent(renderer);
	Map::GetInstance();
	cur_Score = 0;
	time_elapsed = 0;

	SDL_Event e;
	while (true) {
		SDL_PollEvent(&e);
		SDL_Delay(10);
		switch (e.type) {
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT) {
				if (e.button.x >= 400 && e.button.x <= 485 && e.button.y >= 100 && e.button.y <= 185) {

					Map::GetInstance(9,9, 0);
					stat = 2;
					return 0;
				}
				else if (e.button.x >= 600 && e.button.x <= 685 && e.button.y >= 100 && e.button.y <= 185) {
					Map::GetInstance(12,16,1);
					stat = 2;
					return 0;
				}
				else if (e.button.x >= 800 && e.button.x <= 885 && e.button.y >= 100 && e.button.y <= 185) {
					Map::GetInstance(12, 25, 3);
					stat = 2;
					return 0;
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

void Engine::RenderText(const char* text, int x, int y, SDL_Color textColor, int fontSize) {
	TTF_Font* adjustedFont = TTF_OpenFont("font/fonts.ttf", fontSize);
	if (!adjustedFont)
	{
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid(adjustedFont, text, textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect destRect = { x, y, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);

	// Giải phóng bộ nhớ
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(adjustedFont);
}

int Engine::FinishGame() {
	//SDL_RenderClear(renderer);
	stringstream ss,s_time;
	ss << cur_Score;
	s_time << time_elapsed/500;
	string score = "Score:"+ss.str();
	string time = "Time:" + s_time.str();

	TextureManager::GetInstance()->Draw("endBoardBG", 340, 170, 600, 387);
	TextureManager::GetInstance()->Draw("restart", 496, 380, 64, 64);
	TextureManager::GetInstance()->Draw("home", 596, 380, 64, 64);

	if (stat == 0) {
		RenderText("YOU LOSE", 450, 250, { 255,0,0 }, 72);
	}
	else if (stat == 1) {
		RenderText("YOU WON", 430, 250, { 0,255,255 }, 72);
	}
	RenderText(score.c_str(), 420, 330, { 0,0,255 }, 36);
	RenderText(time.c_str(), 700, 330, { 0,0,255 }, 36);

	SDL_Event e;
	while (true) {
		SDL_PollEvent(&e);
		SDL_Delay(10);
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				if (e.button.x >= 496 && e.button.x <= 560 && e.button.y >= 380 && e.button.y <= 444) {
					
					return 2;
					break;
				}
				else if (e.button.x >= 596 && e.button.x <= 640 && e.button.y >= 380 && e.button.y <= 444) {
					return 1;
					break;
				}
			}
			cout << e.button.x << " " << e.button.y << endl;
		
		}
		/*else if (e.type == SDL_MOUSEMOTION) {
			if (e.button.x >= 496 && e.button.x <= 560 && e.button.y >= 380 && e.button.y <= 444) {
				RenderText("Restart", 600, 460, { 240,160,80 }, 36);
			}
			else if (e.button.x >= 596 && e.button.x <= 640 && e.button.y >= 380 && e.button.y <= 444) {
				RenderText("Main Menu", 590, 460, { 240,160,80 }, 36);
			}
		}*/

		else if (e.type == SDL_QUIT)
		{
			return 0;
			break;
		}
		SDL_RenderPresent(renderer);
	}
}