#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#pragma once
#include "Game.hpp"


class TextureManager{
  public:
    static SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
};

#endif