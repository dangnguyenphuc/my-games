#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#pragma once
#include "Game.hpp"

class GameObject{
  public:
    GameObject(const char* spritePath, int x=0, int y=0);
    ~GameObject();

    void update();
    void render();

  private:
    int left;
    int top;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
};


#endif