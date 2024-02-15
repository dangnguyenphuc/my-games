#include "../include/Game.hpp"
#include "../include/TextureManager.hpp"
#include "../include/ECS/Component.hpp"
#include "../include/Map.hpp"
#include "../include/Collision.hpp"
#include "../include/Logic.hpp"
#include <string.h>

// static attributes
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<CollisionComponent*> Game::colliders;
SDL_Rect Game::camera = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};

// Game instances
enum groupLables : std::size_t {
    GROUP_MAP,
    GROUP_PLAYER,
    GROUP_COLLIDER,
    GROUP_BALL
};

Manager manager;
Entity& newPlayer = manager.addEntity();
Entity& ball = manager.addEntity();


// Map* map;
int defaultMap[MAP_HEIGHT][MAP_WIDTH] = {
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

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
    Map::loadMap(defaultMap);

    std::vector<std::tuple<const char*, int, int, int, int>> ArgentinaFootballerSprite;
    ArgentinaFootballerSprite.push_back(std::make_tuple(ARGENTINA_IDLE, IDLE, 0, 4, 100));
    ArgentinaFootballerSprite.push_back(std::make_tuple(ARGENTINA_WALK, WALK_RIGHT, 1, 4, 100));
    ArgentinaFootballerSprite.push_back(std::make_tuple(ARGENTINA_FRONT, WALK_FRONT, 2, 4, 100));
    ArgentinaFootballerSprite.push_back(std::make_tuple(ARGENTINA_BACK, WALK_BACK, 3, 4, 100));

    newPlayer.addComponent<TransformComponent>(2.0f);
    newPlayer.addComponent<SpriteComponent>(ArgentinaFootballerSprite, true);
    newPlayer.addComponent<FootballKeyboardController>();
    newPlayer.addComponent<CollisionComponent>("player");
    newPlayer.addGroup(GROUP_PLAYER);

    ball.addComponent<TransformComponent>(0.0625f);
    ball.addComponent<SpriteComponent>(BALL_TEXTURE_FILE_PATH);
    ball.addComponent<CollisionComponent>("ball");
    ball.getComponent<TransformComponent>().setTopLeftPos(
      SCREEN_CENTER_WIDTH,
      SCREEN_CENTER_HEIGHT
    );
    ball.addGroup(GROUP_BALL);

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

  camera.y = newPlayer.getComponent<TransformComponent>().position.y - SCREEN_CENTER_HEIGHT;
  if(camera.y <= 0){
    camera.y = 0;
  }
  if(camera.y >= SCREEN_CENTER_HEIGHT){
    camera.y = SCREEN_CENTER_HEIGHT;
  }

  // printf("Camera x: %d, Camera y: %d\n", camera.x, camera.y);

  for(auto& i : this->colliders)
  {
    if(strcmp (i->tag,"ball") == 0)
    {
      if(Collision::AABB(newPlayer.getComponent<CollisionComponent>(), *i))
      {
        Logic::playerTouchBall = true;
      }
    }
  }

  if(Logic::playerTouchBall)
  {
    ball.getComponent<TransformComponent>().setTopLeftPos(
      newPlayer.getComponent<TransformComponent>().position
    );
  }

}

std::vector<Entity*>& tiles = manager.getGroup(GROUP_MAP);
std::vector<Entity*>& players = manager.getGroup(GROUP_PLAYER);
std::vector<Entity*>& balls = manager.getGroup(GROUP_BALL);
// std::vector<Entity*>& collider = manager.getGroup(GROUP_COLLIDER);

void Game::render(){
  SDL_RenderClear(this->renderer);

  for(auto& i : tiles)
  {
    i->draw();
  }

  for(auto& i : players)
  {
    i->draw();
  }

  for(auto& i : balls)
  {
    i->draw();
  }

  // for(auto& i : collider)
  // {
  //   i->draw();
  // }

  SDL_RenderPresent(this->renderer);
}

void Game::clean(){
  // delete map;
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);
  SDL_Quit();
  printf("Game cleaned !\n");
}

void Game::addTile(int x, int y, int id, float scale){
  Entity& tile = manager.addEntity();
  tile.addComponent<TileComponent>(x,y,id,scale);
  tile.addGroup(GROUP_MAP);
}