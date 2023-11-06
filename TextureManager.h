#pragma once

#include <string>
#include "Engine.h"
#include "SDL_image.h"
#include <iostream>
#include <map>

using namespace std;

class TextureManager
{
private:
	static TextureManager* s_Instance;
	map<string, SDL_Texture*> listTexture;

public:
	static TextureManager* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
	}
	bool Load(string id, const char* filename);
	SDL_Texture* GetTexture(string id);
	void deleteATexture(string id);
	void Clean();

	void Draw(string id, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
};
