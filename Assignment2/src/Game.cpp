#include "../include/Game.hpp"
#include "../include/TextureManager.hpp"
#include "../include/ECS/Component.hpp"
#include "../include/Map.hpp"
#include "../include/Collision.hpp"
#include "../include/Logic.hpp"
#include "../include/Player.hpp"
#include <string.h>

// static attributes
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<CollisionComponent*> Game::colliders;
SDL_Rect Game::camera = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};

// Game instances
Manager Game::manager;
Player* player1 = new Player(true, 1);

Entity& ball = Game::manager.addEntity();

Entity& wallLeft = Game::manager.addEntity();
Entity& wallRight = Game::manager.addEntity();
Entity& wallBot = Game::manager.addEntity();
Entity& wallTop = Game::manager.addEntity();

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

    /*  Map   */
    Map::loadMap(defaultMap);
    /*  Map   */

    /*  Colliders  */
    wallTop.addComponent<TransformComponent>(0,0,SCREEN_WIDTH,0);
    wallTop.addComponent<CollisionComponent>("w1");

    wallLeft.addComponent<TransformComponent>(0,0,0,SCREEN_HEIGHT*2);
    wallLeft.addComponent<CollisionComponent>("w2");

    wallRight.addComponent<TransformComponent>(SCREEN_WIDTH,0,0,SCREEN_HEIGHT*2);
    wallRight.addComponent<CollisionComponent>("w3");

    wallBot.addComponent<TransformComponent>(0,SCREEN_HEIGHT*2,SCREEN_WIDTH,0);
    wallBot.addComponent<CollisionComponent>("w4");
    /*  Colliders  */

    std::vector<std::tuple<const char*, int, int, int>> ArgentinaFootballerSprite {
      std::make_tuple(ARGENTINA_IDLE, IDLE, 4, 100),
      std::make_tuple(ARGENTINA_WALK, WALK_RIGHT, 4, 100),
      std::make_tuple(ARGENTINA_FRONT, WALK_FRONT, 4, 100),
      std::make_tuple(ARGENTINA_BACK, WALK_BACK, 4, 100)
    };

    /*PLAYERS*/
    player1->init(ArgentinaFootballerSprite);
    /*PLAYERS*/

    ball.addComponent<TransformComponent>(0.0625f);
    ball.addComponent<SpriteComponent>(BALL_TEXTURE_FILE_PATH);
    ball.addComponent<CollisionComponent>("b");
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

std::vector<Entity*>& tiles = Game::manager.getGroup(GROUP_MAP);


void Game::update(){

  Logic::player1Position.clear();
  for(auto& p : player1->footballers){
    Logic::player1Position.push_back(p->getComponent<TransformComponent>().position);
  }

  Game::manager.refresh();
  Game::manager.update();

  camera.y = ball.getComponent<TransformComponent>().position.y - SCREEN_CENTER_HEIGHT;
  if(camera.y <= 0){
    camera.y = 0;
  }
  if(camera.y >= 800){
    camera.y = 800;
  }

  // printf("Camera x: %d, Camera y: %d\n", camera.x, camera.y);

  for(auto& i : this->colliders)
  {
    if(i->tag[0] == 'b')
    {
      for(int p = 0; p < MAX_NUM_OF_PLAYERS; p+=1){
        if(Collision::AABB(player1->footballers[p]->getComponent<CollisionComponent>(), *i) && !Logic::playerPassBall)
        {
          ball.getComponent<TransformComponent>().setTopLeftPos(
            Logic::player1Position[p]
          );

          ball.getComponent<TransformComponent>().setA(
            player1->footballers[p]->getComponent<TransformComponent>().a
          );

          Logic::playerTouchBall = true;
          break;
        }
        else
        {
          Logic::playerTouchBall = false;
        }
      }
    }

    if(i->tag[0] == 'w')
    {
      // ball collided with wall
      if(Collision::AABB(ball.getComponent<CollisionComponent>(), *i))
      {
        ball.getComponent<TransformComponent>().a *= -1;
        if(i->tag[1] == '1' || i->tag[1] == '4')
        {
          ball.getComponent<TransformComponent>().a.x *= -1;
        }
        else
        {
          ball.getComponent<TransformComponent>().a.y *= -1;
        }

      }

      // footballers collided with wall
      for(int p = 0; p < MAX_NUM_OF_PLAYERS; p+=1){
        if(Collision::AABB(player1->footballers[p]->getComponent<CollisionComponent>(), *i))
        {
          player1->footballers[p]->getComponent<TransformComponent>().position = Logic::player1Position[p];
        }
      }
    }
  }

  // if(Logic::playerTouchBall)
  // {
  //   // ball.getComponent<TransformComponent>().setTopLeftPos(
  //   //   Player1_1.getComponent<TransformComponent>().position
  //   // );

  //   // ball.getComponent<TransformComponent>().setA(
  //   //   Player1_1.getComponent<TransformComponent>().a
  //   // );
  // }



}

// std::vector<Entity*>& collider = manager.getGroup(GROUP_COLLIDER);

void Game::render(){
  SDL_RenderClear(this->renderer);

  for(auto& i : tiles)
  {
    i->draw();
  }

  for(auto& i : player1->footballers)
  {
    i->draw();
  }

  ball.draw();

  SDL_RenderPresent(this->renderer);
}

void Game::clean(){
  delete player1;
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