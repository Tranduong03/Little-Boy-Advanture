#pragma once

#include <SDL.h>
#include "Engine.h"

class ImageLayer {
public:
    ImageLayer(SDL_Renderer* renderer);
    ~ImageLayer();

    void AddImage(const char* fileName, int x, int y);
    void Render(SDL_Renderer* renderer);

private:
    struct Image {
        SDL_Texture* texture;
        int x, y;
    };

    SDL_Renderer* renderer;
    std::vector<Image> images;
};