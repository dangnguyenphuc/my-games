#include "../include/Game.hpp"
#include "../include/TextureManager.hpp"

SDL_Texture *tempTexture;
SDL_Rect tempDestRect;

Game::Game(){

}

Game::~Game(){

}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen){
  counter = 0;
  int flag = 0;
  if(fullscreen)
  {
    flag = SDL_WINDOW_FULLSCREEN;
  }

  if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    printf("Initialised\n");

    this->window = SDL_CreateWindow(title, xPos, yPos, width, height, flag);
    if(this->window)
    {
      printf("Window created\n");
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);

    if(this->renderer)
    {
      SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
      printf("Renderer created\n");
    }

    this->isRunning = true;

    tempTexture = TextureManager::LoadTexture(TEST_TEXTURE_FILE_PATH, this->renderer);

  }
  else
  {
    this->isRunning = false;
  }
}

void Game::handleEvent(){
  SDL_Event event;
  SDL_PollEvent(&event);

  switch(event.type){

    case SDL_QUIT:
      this->isRunning = false;
      break;

    default:
      break;
  }

}

void Game::update(){
  counter += 1;
  tempDestRect.h = 50;
  tempDestRect.w = 50;

  tempDestRect.x = counter;
  tempDestRect.y = 0;
}

void Game::render(){
  SDL_RenderClear(this->renderer);
  SDL_RenderCopy(this->renderer, tempTexture, NULL, &tempDestRect);
  SDL_RenderPresent(this->renderer);
}

void Game::clean(){
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);
  SDL_Quit();
  printf("Game cleaned !\n");
}