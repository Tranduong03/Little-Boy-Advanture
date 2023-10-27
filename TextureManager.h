#pragma once

#include <string>
#include "Engine.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

class TextureManager
{
public:
	static SDL_Texture* Load_BG(const char* texture, SDL_Renderer* renderer);

};

