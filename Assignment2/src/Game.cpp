#include "../include/Game.hpp"
#include "../include/TextureManager.hpp"
#include "../include/ECS/Component.hpp"
#include "../include/Map.hpp"
#include "../include/Collision.hpp"
#include "../include/Logic.hpp"
#include "../include/Player.hpp"
#include "../include/Ball.hpp"
#include <string.h>

// static attributes
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<CollisionComponent*> Game::colliders;
SDL_Rect Game::camera = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};

// Game instances
Manager Game::manager;
Player* player1 = new Player(true, 0);
Player* player2 = new Player(true, 1);
Ball* ball = new Ball();

Entity& line = Game::manager.addEntity();

Entity& wallLeft = Game::manager.addEntity();
Entity& wallRight = Game::manager.addEntity();
Entity& wallBot = Game::manager.addEntity();
Entity& wallTop = Game::manager.addEntity();

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
    line.addComponent<TransformComponent>(-20,0, 0.65f);
    line.addComponent<SpriteComponent>(LINE1_TEXTURE_FILE_PATH);
    line.addComponent<TransformComponent>(-20,1383, 0.65f);
    line.addComponent<SpriteComponent>(LINE2_TEXTURE_FILE_PATH);
    line.addComponent<TransformComponent>(0,0);
    line.addComponent<SpriteComponent>(LINE_TEXTURE_FILE_PATH);
    line.addComponent<TransformComponent>(SCREEN_WIDTH - 20,0);
    line.addComponent<SpriteComponent>(LINE_TEXTURE_FILE_PATH);
    line.addComponent<TransformComponent>(-20, SCREEN_HEIGHT - 20);
    line.addComponent<SpriteComponent>(LINE_H_TEXTURE_FILE_PATH);
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

    /*PLAYERS*/
    player1->init(RiverPlateFootballerSprite);
    player2->init(BocaFootballerSprite);
    /*PLAYERS*/

    /*BALL*/
    ball->init(BALL_TEXTURE_FILE_PATH);
    /*BALL*/
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

  Logic::player2Position.clear();
  for(auto& p : player2->footballers){
    Logic::player2Position.push_back(p->getComponent<TransformComponent>().position);
  }

  Game::manager.refresh();
  Game::manager.update();

  Logic::ballPosition = ball->entity->getComponent<TransformComponent>().position;

  // update camera
  this->updateCamera();

  ball->defaultDecelerator();
  player1->setCurrentFootballer();
  for(auto& i : this->colliders)
  {
    if(i->tag[0] == 'b')
    {
      for(int p = 0; p < MAX_NUM_OF_PLAYERS; p+=1){
        if(Collision::AABB(player1->footballers[p]->getComponent<CollisionComponent>(), *i))
        {
          if(!Logic::playerPassBall)
          {

            ball->entity->getComponent<TransformComponent>().setTopLeftPos(
              Logic::player1Position[p]
            );

            if(player1->footballers[p]->getComponent<TransformComponent>().a == Vector2(0.0f,0.0f))
            {
              ball->entity->getComponent<TransformComponent>().setA(
                Vector2(0.0f, 0.7f)
              );
            }
            else
            {
              ball->entity->getComponent<TransformComponent>().setA(
                player1->footballers[p]->getComponent<TransformComponent>().a
              );
            }

          }
          Logic::currentFootballer1 = player1->footballers[p];
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
      if(Collision::AABB(ball->entity->getComponent<CollisionComponent>(), *i))
      {
        ball->entity->getComponent<TransformComponent>().a *= -1;
        if(i->tag[1] == '1' || i->tag[1] == '4')
        {
          ball->entity->getComponent<TransformComponent>().a.x *= -1;
        }
        else
        {
          ball->entity->getComponent<TransformComponent>().a.y *= -1;
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

}

void Game::render(){
  SDL_RenderClear(this->renderer);

  for(auto& i : tiles)
  {
    i->draw();
  }

  line.draw();

  for(auto& i : player1->footballers)
  {
    i->draw();
  }

  for(auto& i : player2->footballers)
  {
    i->draw();
  }

  ball->entity->draw();

  SDL_RenderPresent(this->renderer);
}

void Game::clean(){
  delete player1;
  delete ball;
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);
  SDL_Quit();
  printf("Game cleaned !\n");
}

void Game::updateCamera(){
  camera.y = ball->entity->getComponent<TransformComponent>().position.y - SCREEN_CENTER_HEIGHT;
  if(camera.y <= 0){
    camera.y = 0;
  }
  if(camera.y >= SCREEN_HEIGHT){
    camera.y = SCREEN_HEIGHT;
  }
}

void Game::addTile(int x, int y, int id, float scale){
  Entity& tile = Game::manager.addEntity();
  tile.addComponent<TileComponent>(x,y,id,scale);
  tile.addGroup(GROUP_MAP);
}