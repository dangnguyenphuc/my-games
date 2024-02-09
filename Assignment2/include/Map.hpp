#ifndef MAP_H
#define MAP_H
#pragma once
#include "Game.hpp"
#include "TextureManager.hpp"

class Map{
  public:
    Map();
    ~Map();

    void loadMap(int arr[MAP_HEIGHT][MAP_WIDTH]);
    void drawMap();
  private:
    SDL_Rect srcRect, desRect;
    SDL_Texture* grass;
    SDL_Texture* line;
    SDL_RendererFlip flip;

    int map[MAP_HEIGHT][MAP_WIDTH];
};

#endif