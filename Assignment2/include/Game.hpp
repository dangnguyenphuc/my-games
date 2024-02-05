#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "config.hpp"

class Game{
  public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

    void handleEvent();
    void update();
    void render();
    void clean();

    bool running(){
      return this->isRunning;
    };

  private:
    bool isRunning;
    SDL_Window* window;

  public:
    static SDL_Renderer *renderer;
};

#endif