#include "Engine.h"
#include <fstream>

using namespace std;

SDL_Rect scrR, destR;
SDL_Texture* Texture;

position mousePos;

int cur_Score, time_elapsed;
string name = "";

File List;

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
	TextureManager::GetInstance()->Load("bg2", "bg/score.jpg");

	TextureManager::GetInstance()->Load("quit", "bg/quit.png");
	TextureManager::GetInstance()->Load("quitClick", "bg/quitClick.png");

	TextureManager::GetInstance()->Load("play", "bg/play.png");
	TextureManager::GetInstance()->Load("playClick", "bg/playClick.png");

	TextureManager::GetInstance()->Load("tutorial", "bg/tutorial.png");
	TextureManager::GetInstance()->Load("tutorialClick", "bg/tutorialClick.png");

	TextureManager::GetInstance()->Load("score", "bg/score.png");
	TextureManager::GetInstance()->Load("scoreClick", "bg/scoreClick.png");

	TextureManager::GetInstance()->Load("BACK", "bg/backIcon.png");
	TextureManager::GetInstance()->Load("BACKClick", "bg/backIconClick.png");
	TextureManager::GetInstance()->Load("tutorialScreen", "images/TUTORIALSCR.png");

	TextureManager::GetInstance()->Load("pixel", "images/pixel.jpg");

	TextureManager::GetInstance()->Load("easy", "bg/beforePlay/Easy.png");
	TextureManager::GetInstance()->Load("nor", "bg/beforePlay/normal.png");
	TextureManager::GetInstance()->Load("hard", "bg/beforePlay/hard.png");

	TextureManager::GetInstance()->Load("playingBG", "images/playing_bg.jpg");
	TextureManager::GetInstance()->Load("endBoardBG", "images/khungEnd.jpg");
	TextureManager::GetInstance()->Load("BoomClick", "images/bomb_active.png");

	TextureManager::GetInstance()->Load("restart", "bg/play/playagain.png");
	TextureManager::GetInstance()->Load("home", "bg/play/home.png");

	TextureManager::GetInstance()->Load("inNameBG", "bg/InputName.png");
	TextureManager::GetInstance()->Load("enter", "bg/ENTER.png");
	TextureManager::GetInstance()->Load("enterClick", "bg/enterClick.png");

	TextureManager::GetInstance()->Load("Champion", "bg/champion.png");
	TextureManager::GetInstance()->Load("input", "bg/input.png");

	return true;
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
		clean();
		exit(0);
	}
	usingEvent = event;
	time_elapsed += 10;
}

void Engine::restart()
{
	isRunning = true;
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
		SDL_Delay(1500);
		isRunning = false;
	}
	else if (stat == 1) {
		//Xử lý win
		Map::GetInstance()->MapWinOpen();
		Map::GetInstance()->DrawPixel();
		SDL_RenderPresent(renderer);
		SDL_Delay(1500);
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
		if (check == 1) 
		{
			Tutorial();
		}
		else if (check == 2)
		{
			Score();
			cout << "Menu Score" << endl;
		}
		check = Input();
	}
}

int Engine::Input() {
	SDL_RenderClear(renderer);
	TextureManager::GetInstance()->Draw("bg1", 0, 0, 1280, 720);

	int l_Menu = 190, t_Menu = 150, size = 109;
	int s_x = 169, s_y = 89;

	TextureManager::GetInstance()->Draw("play", l_Menu, t_Menu, s_x, s_y);
	TextureManager::GetInstance()->Draw("tutorial", l_Menu, t_Menu + size, s_x, s_y);
	TextureManager::GetInstance()->Draw("score", l_Menu, t_Menu + 2*size, s_x, s_y);
	TextureManager::GetInstance()->Draw("quit", l_Menu, t_Menu + 3*size, s_x, s_y);

	SDL_RenderPresent(renderer);
	cout << "Get Event in Input Now" << endl;
	SDL_Event e;
	int m_second = 0;
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
				if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu && e.button.y <= t_Menu + 90)
				{
					TextureManager::GetInstance()->Draw("play", l_Menu, t_Menu, s_x, s_y);
					//return BeforePlay();
					return InputName();
				}
				// tutorial
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu + size && e.button.y <= t_Menu + size + 90)
				{
					TextureManager::GetInstance()->Draw("tutorial", l_Menu, t_Menu + size, s_x, s_y);
					return 1;
				}
				// score
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu + 2*size && e.button.y <= t_Menu + 2*size + 90)
				{
					TextureManager::GetInstance()->Draw("score", l_Menu, t_Menu + 2 * size, s_x, s_y);
					return 2;
				}
				// quit
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu + 3 * size && e.button.y <= t_Menu + 3 * size + 90)
				{
					TextureManager::GetInstance()->Draw("quit", l_Menu, t_Menu + 3 * size, s_x, s_y);
					clean();
					exit(0);
					isRunning = false;
				}
			}
		case SDL_MOUSEMOTION:
			if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu && e.button.y <= t_Menu + 90)
			{
				TextureManager::GetInstance()->Draw("playClick", l_Menu, t_Menu, s_x, s_y);
			}
			else if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu + size && e.button.y <= t_Menu + size + 90) {
				TextureManager::GetInstance()->Draw("tutorialClick", l_Menu, t_Menu + size, s_x, s_y);
			}
			else if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu + 2 * size && e.button.y <= t_Menu + 2 * size + 90) {
				TextureManager::GetInstance()->Draw("scoreClick", l_Menu, t_Menu + 2 * size, s_x, s_y);
			}
			else if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu + 3 * size && e.button.y <= t_Menu + 3 * size + 90) {
				TextureManager::GetInstance()->Draw("quitClick", l_Menu, t_Menu + 3 * size, s_x, s_y);
			}
			else {
				TextureManager::GetInstance()->Draw("bg1", 0, 0, 1280, 720);
				TextureManager::GetInstance()->Draw("play", l_Menu, t_Menu, s_x, s_y);
				TextureManager::GetInstance()->Draw("tutorial", l_Menu, t_Menu + size, s_x, s_y);
				TextureManager::GetInstance()->Draw("score", l_Menu, t_Menu + 2 * size, s_x, s_y);
				TextureManager::GetInstance()->Draw("quit", l_Menu, t_Menu + 3 * size, s_x, s_y);
			}
		case SDL_MOUSEBUTTONDOWN:

			if (e.button.button == SDL_BUTTON_LEFT) 
			{
				// play game
				if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu && e.button.y <= t_Menu + 90)
				{
					// sound.playMusic(Click, 1);
					TextureManager::GetInstance()->Draw("playClick", l_Menu, t_Menu, s_x, s_y);
				}
				// tutorial
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu + size && e.button.y <= t_Menu + size + 90)
				{
					// sound.playMusic(Click, 1);
					TextureManager::GetInstance()->Draw("tutorialClick", l_Menu, t_Menu + size, s_x, s_y);
				}
				// score
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu + 2 * size && e.button.y <= t_Menu + 2 * size + 90)
				{
					TextureManager::GetInstance()->Draw("scoreClick", l_Menu, t_Menu + 2 * size, s_x, s_y);
				}
				// quit
				else if (e.button.x >= l_Menu && e.button.x <= l_Menu + s_x && e.button.y >= t_Menu + 3 * size && e.button.y <= t_Menu + 3 * size + 90)
				{
					TextureManager::GetInstance()->Draw("quitClick", l_Menu, t_Menu + 3 * size, s_x, s_y);
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

void Engine::Tutorial() 
{
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
					TextureManager::GetInstance()->Draw("BACKClick", 1179, 17, 75, 75);
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
			clean();
			exit(0);
			return;
		}
		SDL_RenderPresent(renderer);
	}
}

void Engine::Score()
{
	SDL_RenderClear(renderer);

	cout << "Score" << endl;
	
	TextureManager::GetInstance()->Draw("bg2", 0, 0, 1280, 720);
	TextureManager::GetInstance()->Draw("Champion", 470, 30, 86, 75);
	TextureManager::GetInstance()->Draw("Champion", 700, 30, 86, 75);
	TextureManager::GetInstance()->Draw("input", 525, 600, 245, 75);
	TextureManager::GetInstance()->Draw("BACK", 1179, 17, 75, 75);

	List.write();

	SDL_Event e;
	while (1) {

		Node* i = List.Head();
		RenderText2("B X H", 570, 30, { 30, 255, 20 }, 70);
		
		for (int count = 0; count < 10; count++)
		{
			string s_i = to_string(count+1) + ".";
			RenderText2(s_i.c_str(), 180, count * 35 + 140, { 25, 250, 20 }, 45);
			RenderText2(i->name.c_str(), 235, count * 35 + 140, { 50, 250, 20 }, 45);
			string s_score = to_string(i->score);
			RenderText2(s_score.c_str(), 450, count * 35 + 140, { 25, 250, 20 }, 45);
			i = i->next;
		}

		for (int count = 10; count < 20; count++)
		{
			string s_i = to_string(count+1) + ".";
			RenderText2(s_i.c_str(), 700, (count-10) * 35 + 140, { 255, 255, 255 }, 45);
			RenderText2(i->name.c_str(), 765, (count - 10) * 35 + 140, { 255, 255, 255 }, 45);
			string s_score = to_string(i->score);
			RenderText2(s_score.c_str(), 970, (count - 10) * 35 + 140, { 255, 255, 255 }, 45);
			i = i->next;
		}

		SDL_PollEvent(&e);
		SDL_Delay(10);
		switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				if (e.button.x >= 1180 && e.button.x <= 1260 && e.button.y >= 20 && e.button.y <= 100) {
					TextureManager::GetInstance()->Draw("BACKClick", 1179, 17, 75, 75);
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
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				if (e.button.x >= 525 && e.button.y <= 770 && e.button.y >= 600 && e.button.y <= 675)
				{
					search_Score();
					SDL_RenderClear(renderer);
					TextureManager::GetInstance()->Draw("bg2", 0, 0, 1280, 720);
					TextureManager::GetInstance()->Draw("Champion", 470, 30, 86, 75);
					TextureManager::GetInstance()->Draw("Champion", 700, 30, 86, 75);
					TextureManager::GetInstance()->Draw("input", 525, 600, 245, 75);
					TextureManager::GetInstance()->Draw("BACK", 1179, 17, 75, 75);
				}
			}
			break;
		case SDL_QUIT:
			clean();
			TextureManager::GetInstance()->Clean();
			isRunning = false;
			clean();
			exit(0);
		}
		SDL_RenderPresent(renderer);
	}
}

void Engine::search_Score()
{
	cout << "search" << endl;

	SDL_RenderClear(renderer);
	TextureManager::GetInstance()->Draw("bg2", 0, 0, 1280, 720);
	TextureManager::GetInstance()->Draw("BACK", 1180, 20, 70, 70);
	TextureManager::GetInstance()->Draw("Champion", 470, 30, 86, 75);
	TextureManager::GetInstance()->Draw("Champion", 700, 30, 86, 75);
	TextureManager::GetInstance()->Draw("input", 525, 600, 245, 75);

	string search_name = "";

	SDL_Event e;
	SDL_StartTextInput();

	while (1) {
		SDL_RenderClear(renderer);
		TextureManager::GetInstance()->Draw("bg2", 0, 0, 1280, 720);
		TextureManager::GetInstance()->Draw("BACK", 1180, 20, 70, 70);
		TextureManager::GetInstance()->Draw("Champion", 470, 30, 86, 75);
		TextureManager::GetInstance()->Draw("Champion", 700, 30, 86, 75);
		TextureManager::GetInstance()->Draw("input", 525, 600, 245, 75);

		RenderText2("B X H", 570, 30, { 30, 255, 20 }, 70);

		SDL_PollEvent(&e);
		SDL_Delay(10);
		switch (e.type) {
		case SDL_KEYDOWN:
		case SDL_TEXTINPUT:
			if (e.key.keysym.scancode == SDL_SCANCODE_BACKSPACE && search_name.length() > 0)
			{
				search_name = search_name.substr(0, search_name.length() - 1);
			}
			else if (e.type == SDL_TEXTINPUT)
			{
				if (search_name.length() <= 12)
				{
					search_name += e.text.text;
				}
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				if (e.button.x >= 1180 && e.button.x <= 1260 && e.button.y >= 20 && e.button.y <= 100) {
					TextureManager::GetInstance()->Draw("BACKClick", 1179, 17, 75, 75);
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
			clean();
			exit(0);
		}

		if (search_name.compare("") != 0)
		{
			RenderText2(search_name.c_str(), 555, 615, { 255, 255, 255, 255 }, 38);
		}

		Node* i = List.Head();
		int count = 1;

		/*string s_i = to_string(count + 1) + ".";
		RenderText2(s_i.c_str(), 180, count * 35 + 140, { 25, 250, 20 }, 45);
		RenderText2(i->name.c_str(), 235, count * 35 + 140, { 50, 250, 20 }, 45);
		string s_score = to_string(i->score);
		RenderText2(s_score.c_str(), 450, count * 35 + 140, { 25, 250, 20 }, 45);
		i = i->next;*/

		while (i != NULL)
		{
			if (i->name.find(search_name) != string::npos && (search_name.length() != 0))
			{
				string s_i = to_string(count + 1) + ".";
				RenderText2(s_i.c_str(), 180, count * 30 + 50, { 25, 250, 20 }, 30);
				RenderText2(i->name.c_str(), 235, count * 35 + 140, { 50, 250, 20 }, 45);
				string s_score = to_string(i->score);
				RenderText2(s_score.c_str(), 450, count * 35 + 140, { 25, 250, 20 }, 45);
				
			}
			i = i->next;
			count++;
		}
		delete i;
		SDL_RenderPresent(renderer);
	}
}

int Engine::BeforePlay() {
	SDL_RenderClear(renderer);

	TextureManager::GetInstance()->Draw("bg1", 0, 0, 1280, 720);
	TextureManager::GetInstance()->Draw("easy", 400, 100, 162, 85);
	TextureManager::GetInstance()->Draw("nor", 600, 100, 141, 85);
	TextureManager::GetInstance()->Draw("hard", 800, 100, 167, 85);

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
				if (e.button.x >= 400 && e.button.x <= 562 && e.button.y >= 100 && e.button.y <= 185) {
					Map::GetInstance(9,9, 0);
					stat = 2;
					return 0;
				}
				else if (e.button.x >= 600 && e.button.x <= 741 && e.button.y >= 100 && e.button.y <= 185) {
					Map::GetInstance(12,16,1);
					stat = 2;
					return 0;
				}
				else if (e.button.x >= 800 && e.button.x <= 967 && e.button.y >= 100 && e.button.y <= 185) {
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

void Engine::RenderText2(const char* text, int x, int y, SDL_Color textColor, int fontSize) {
	TTF_Font* adjustedFont = TTF_OpenFont("font/m5x7.ttf", fontSize);
	if (!adjustedFont)
	{
		cerr << "Failed to load font: " << TTF_GetError() << endl;
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

	stringstream ss,s_time;
	ss << cur_Score;
	s_time << time_elapsed/1000;
	string score = "Score:"+ss.str();
	string time = "Time:" + s_time.str();

	TextureManager::GetInstance()->Draw("endBoardBG", 340, 170, 600, 387);
	TextureManager::GetInstance()->Draw("restart", 526, 380, 87, 64);
	TextureManager::GetInstance()->Draw("home", 680, 380, 79, 64);

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
				if (e.button.x >= 525 && e.button.x <= 610 && e.button.y >= 380 && e.button.y <= 444) 
				{
					return 2;
					break;
				}
				else if (e.button.x >= 675 && e.button.x <= 760 && e.button.y >= 380 && e.button.y <= 444) 
				{
					return 1;
					break;
				}
			}
		}
		else if (e.type == SDL_MOUSEMOTION) {
			if (e.button.x >= 520 && e.button.x <= 610 && e.button.y >= 380 && e.button.y <= 444) {
				RenderText("[Restart]", 555, 460, { 255,255,0 }, 36);
			}
			else if (e.button.x >= 675 && e.button.x <= 760 && e.button.y >= 380 && e.button.y <= 444) {
				RenderText("[Main Menu]", 525, 460, { 255,255,0 }, 36);
			}
			else {
				TextureManager::GetInstance()->Draw("endBoardBG", 340, 170, 600, 387);
				TextureManager::GetInstance()->Draw("restart", 526, 380, 87, 64);
				TextureManager::GetInstance()->Draw("home", 680, 380, 79, 64);

				if (stat == 0) {
					RenderText("YOU LOSE", 450, 250, { 255,0,0 }, 80);
				}
				else if (stat == 1) {
					RenderText("YOU WON", 430, 250, { 0,255,255 }, 80);
				}
				RenderText(score.c_str(), 420, 330, { 0,0,255 }, 36);
				RenderText(time.c_str(), 700, 330, { 0,0,255 }, 36);
			}
		}
		else if (e.type == SDL_QUIT)
		{
			clean();
			exit(0);
			break;
		}
		SDL_RenderPresent(renderer);
	}
}

int Engine::InputName() {
	name = "Name Player";

	TextureManager::GetInstance()->Draw("enter", 565, 300, 150, 60);
	SDL_Event ev;
	SDL_StartTextInput();

	while (running()) {
		SDL_Delay(10);
		SDL_PollEvent(&ev);

		switch (ev.type)
		{
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
		case SDL_TEXTINPUT:
			if (ev.key.keysym.scancode == SDL_SCANCODE_BACKSPACE && name.length() > 0)
			{
				name = name.substr(0, name.length() - 1);
			}
			else if (ev.type == SDL_TEXTINPUT)
			{
				if (name.length() <= 12)
				{
					name += ev.text.text;
				}
			}
			else if (ev.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				SDL_StopTextInput();

				if (name.compare("") == 0) name = "Name Player";
				return BeforePlay();
			}

			break;
		case SDL_MOUSEBUTTONUP:
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				if (ev.button.x >= 565 && ev.button.x <= 715 &&
					ev.button.y >= 270 && ev.button.y <= 320)
				{
					TextureManager::GetInstance()->Draw("enterClick", 565, 270, 150, 60);
					SDL_RenderPresent(renderer);
					SDL_StopTextInput();
					if (name.compare("") == 0) name = "Name Player";

					return BeforePlay();
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				if (ev.button.x >= 565 && ev.button.x <= 715 &&
					ev.button.y >= 270 && ev.button.y <= 320)
				{
					TextureManager::GetInstance()->Draw("enterClick", 565, 270, 150, 60);
					SDL_RenderPresent(renderer);
				}
			}
			break;
		}
		string name_out = " " + name;	// vì hàm RenderText bị lỗi khi in xâu rỗng
		SDL_RenderClear(renderer);
		TextureManager::GetInstance()->Draw("inNameBG", 0, 0, 1280, 720);
		TextureManager::GetInstance()->Draw("enter", 565, 270, 150, 60);
		RenderText(name_out.c_str(), 530, 200, {238,0,0,255}, 30);
		SDL_RenderPresent(renderer);
	}
}

void Engine::Output_Score()
{
	ofstream outfile;
	outfile.open("output.txt", ios_base::app);
	// outfile << name << " " << cur_Score << " " << time_elapsed << endl;
	outfile << cur_Score << " " << name << endl;
	outfile.close();
	List.addNode(cur_Score, name);
	List.write();
}

void Engine::Read_Score()
{
	List.read();
	List.write();
}

