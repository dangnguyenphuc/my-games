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
Manager Game::manager;
Entity& Player1_1 = Game::manager.addEntity();
Entity& Player1_2 = Game::manager.addEntity();
Entity& Player1_3 = Game::manager.addEntity();
// Entity& Player1_1 = manager.addEntity();
Entity& ball = Game::manager.addEntity();


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

    Player1_1.addComponent<TransformComponent>(2.0f);
    Player1_1.addComponent<SpriteComponent>(ArgentinaFootballerSprite, true);
    Player1_1.addComponent<CollisionComponent>("player1.1");
    Player1_1.addGroup(GROUP_PLAYER1);

    Player1_2.addComponent<TransformComponent>(2.0f);
    Player1_2.addComponent<SpriteComponent>(ArgentinaFootballerSprite, true);
    Player1_2.addComponent<CollisionComponent>("player1.2");
    Player1_2.addGroup(GROUP_PLAYER1);
    Player1_2.getComponent<TransformComponent>().setTopLeftPos(
      0,
      SCREEN_CENTER_WIDTH
    );

    Player1_3.addComponent<TransformComponent>(2.0f);
    Player1_3.addComponent<SpriteComponent>(ArgentinaFootballerSprite, true);
    Player1_3.addComponent<CollisionComponent>("player1.3");
    Player1_3.addGroup(GROUP_PLAYER1);
    Player1_3.getComponent<TransformComponent>().setTopLeftPos(
      0,
      SCREEN_WIDTH - 32
    );

    Player1_1.addComponent<FootballKeyboardController>(true);
    Player1_2.addComponent<FootballKeyboardController>();
    Player1_3.addComponent<FootballKeyboardController>();

    ball.addComponent<TransformComponent>(0.0625f);
    ball.addComponent<SpriteComponent>(BALL_TEXTURE_FILE_PATH);
    ball.addComponent<CollisionComponent>("ball");
    ball.getComponent<TransformComponent>().setTopLeftPos(
      SCREEN_CENTER_HEIGHT,
      SCREEN_CENTER_WIDTH
    );

    ball.addComponent<BallKeyboardController>();
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
  Game::manager.refresh();
  Game::manager.update();

  // printf("player1.1 enable: %d, player1.2 enable: %d\n",
  //  Player1_1.getComponent<FootballKeyboardController>().enable,
  //  Player1_2.getComponent<FootballKeyboardController>().enable);

  camera.y = Player1_1.getComponent<TransformComponent>().position.y - SCREEN_CENTER_HEIGHT;
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
      if(Collision::AABB(Player1_1.getComponent<CollisionComponent>(), *i) && Logic::playerPassBall == false)
      {
        Logic::playerTouchBall = true;
      }


      else if(Collision::AABB(Player1_2.getComponent<CollisionComponent>(), *i) && Logic::playerPassBall == false)
      {
        Logic::playerTouchBall = true;
      }

      else Logic::playerTouchBall = false;


    }
  }

  if(Logic::playerTouchBall)
  {
    ball.getComponent<TransformComponent>().setTopLeftPos(
      Player1_1.getComponent<TransformComponent>().position
    );

    ball.getComponent<TransformComponent>().setA(
      Player1_1.getComponent<TransformComponent>().a
    );
  }



}

std::vector<Entity*>& tiles = Game::manager.getGroup(GROUP_MAP);
std::vector<Entity*>& players = Game::manager.getGroup(GROUP_PLAYER1);
std::vector<Entity*>& balls = Game::manager.getGroup(GROUP_BALL);
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
  Entity& tile = Game::manager.addEntity();
  tile.addComponent<TileComponent>(x,y,id,scale);
  tile.addGroup(GROUP_MAP);
}