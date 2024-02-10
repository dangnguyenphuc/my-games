#include "../include/Game.hpp"
#include "../include/TextureManager.hpp"
#include "../include/ECS/Component.hpp"
#include "../include/Map.hpp"
#include "../include/Collision.hpp"

// static attributes
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

// Game instances
Manager manager;
Entity& newPlayer = manager.addEntity();
Entity& wall = manager.addEntity();
// Map* map;

Game::Game(){}
Game::~Game(){}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen){
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

    // map = new Map();

    std::vector<std::tuple<const char*, int, int, int, int>> ArgentinaFootballerSprite;
    ArgentinaFootballerSprite.push_back(std::make_tuple(ARGENTINA_IDLE, IDLE, 0, 4, 100));
    ArgentinaFootballerSprite.push_back(std::make_tuple(ARGENTINA_WALK, WALK_RIGHT, 1, 4, 100));
    ArgentinaFootballerSprite.push_back(std::make_tuple(ARGENTINA_FRONT, WALK_FRONT, 2, 4, 100));
    ArgentinaFootballerSprite.push_back(std::make_tuple(ARGENTINA_BACK, WALK_BACK, 3, 4, 100));

    newPlayer.addComponent<TransformComponent>(2.0f);
    newPlayer.addComponent<SpriteComponent>(ArgentinaFootballerSprite, true);
    newPlayer.addComponent<FootballKeyboardController>();
    newPlayer.addComponent<CollisionComponent>("player");


    wall.addComponent<TransformComponent>(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT,4.0f);
    wall.addComponent<SpriteComponent>(GRASS_TILE_FILE_PATH);
    wall.addComponent<CollisionComponent>("wall");

  }
  else
  {
    this->isRunning = false;
  }
}

void Game::handleEvent(){

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
  manager.refresh();
  manager.update();

  if(Collision::AABB(newPlayer.getComponent<CollisionComponent>().collider, wall.getComponent<CollisionComponent>().collider)){
    printf("PLAYER hits WALL\n");
  }

}

void Game::render(){
  SDL_RenderClear(this->renderer);
  // map->drawMap();
  manager.draw();
  SDL_RenderPresent(this->renderer);
}

void Game::clean(){
  // delete map;
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);
  SDL_Quit();
  printf("Game cleaned !\n");
}