#include "../include/Game.hpp"
#include <stdint.h>

Game *game = nullptr;

int main(){

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
    if(FRAME_DELAY > frameTime){
      SDL_Delay(FRAME_DELAY - frameTime);
    }

  }
  game->clean();

  delete game;

  return 0;
}