#include "../include/Game.hpp"
#include <stdint.h>

Game *game = nullptr;

int main(){

  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  uint32_t frameStart;
  int frameTime;

  game = new Game();
  game->init("Assignment2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

  while(game->running()){

    frameStart = SDL_GetTicks();

    game->handleEvent();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;
    if(frameDelay > frameTime){
      SDL_Delay(frameDelay - frameTime);
    }

  }
  game->clean();

  return 0;
}