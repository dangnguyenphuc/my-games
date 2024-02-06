#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#pragma once
#include "Game.hpp"


class TextureManager{
  public:
    static SDL_Texture* loadTexture(const char* filePath);
    static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
    static std::pair<int, int> getTextureWidthHeight(const char* filePath);
    static std::pair<int, int> getSpriteWidthHeight(const char* filePath, int row, int col);
};

#endif