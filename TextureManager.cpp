#include "TextureManager.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(string id, const char* path) {
	SDL_Surface* surface = IMG_Load(path);
	if (surface == nullptr) {
		SDL_Log("can't load texture: %s, %s", path, SDL_GetError());
		return 0;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
	if (texture == nullptr) {
		SDL_Log("can't load texture: %s, %s", path, SDL_GetError());
		return 0;
	}
	SDL_FreeSurface(surface);
	listTexture[id] = texture;
}

SDL_Texture* TextureManager::GetTexture(string id)
{
	return listTexture[id];
}

void TextureManager::deleteATexture(string id)
{
	SDL_DestroyTexture(listTexture[id]);
	listTexture.erase(id);
}

void TextureManager::Clean() {
	map<string, SDL_Texture*>::iterator it;
	for (it = listTexture.begin(); it != listTexture.end(); it++) {
		SDL_DestroyTexture(it->second);
	}
	listTexture.clear();
}

void TextureManager::Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect srcR = { 0, 0, width, height }, destR = { x, y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), listTexture[id], &srcR, &destR, 0, nullptr, flip);
}

void TextureManager::DrawFrame(string id, int x, int y, int width, int height, int row, int frame, int size, SDL_RendererFlip flip, float _Angle)
{
	SDL_Rect srcRect = { width * frame, height * row, width, height };
	SDL_Rect dstRect = { x, y, size==NULL ? width : size, size==NULL ? height : size };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), listTexture[id], &srcRect, &dstRect, _Angle, nullptr, flip);
}
