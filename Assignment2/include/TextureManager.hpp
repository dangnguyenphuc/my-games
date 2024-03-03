#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#pragma once
#include "Game.hpp"
#include "config.hpp"
#include <vector>


class TextureManager{
  public:
    static SDL_Texture* loadTexture(const char* filePath);
    // static SDL_Texture* renderText(const char* s, const SDL_Color& color = {255,255,255,255}, const int& fontStyle = TTF_STYLE_NORMAL);
    static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip = SDL_FLIP_NONE, const float& rotateDegree = 0.0f);
    static std::pair<int, int> getTextureWidthHeight(const char* filePath);
    static std::pair<int, int> getSpriteWidthHeight(const char* filePath, int row, int col);
};

#endif