#include "TextureManager.h"

SDL_Texture* TextureManager::Load_BG(const char* fileName, SDL_Renderer* renderer)
{
	SDL_Surface* Surface = IMG_Load(fileName);
	SDL_Texture* text = IMG_LoadTexture(renderer, fileName);
	SDL_FreeSurface(Surface);

	return text;
}
