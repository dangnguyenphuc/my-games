#include "../include/Game.hpp"
#include "../include/TextureManager.hpp"
#include "../include/ECS/Component.hpp"
#include "../include/Map.hpp"
#include "../include/Collision.hpp"
#include "../include/Logic.hpp"
#include "../include/Player.hpp"
#include "../include/Ball.hpp"
#include <string.h>
#include <stdlib.h>
#include <time.h>

void drawActiveStar();
void drawUnactiveStar();

// static attributes
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<CollisionComponent*> Game::colliders;
SDL_Rect Game::camera = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};

// Game instances
Manager Game::manager;
Player* player1 = new Player(true, 0);
Player* player2 = new Player(true, 1);
Ball* Game::ball = new Ball();

Entity& line = Game::manager.addEntity();
Entity& wall = Game::manager.addEntity();
Entity& goal1 = Game::manager.addEntity();
Entity& goal2 = Game::manager.addEntity();
Entity& activeStar = Game::manager.addEntity();
Entity& unactiveStar = Game::manager.addEntity();

void resetPlayerFootballerPositions(){
  player1->resetPlayerPosition();
  player2->resetPlayerPosition();
  if(Logic::ballState == PLAYER1_SCORED)
  {
    player2->setPlayerCFWithBall();
    player1->resetPlayer1CFPosition();
  }
  else if(Logic::ballState == PLAYER2_SCORED)
  {
    player1->setPlayerCFWithBall();
    player2->resetPlayer2CFPosition();
  }
}

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
    line.addComponent<TransformComponent>(-10,0, 0.65f);
    line.addComponent<SpriteComponent>(LINE1_TEXTURE_FILE_PATH);
    line.addComponent<TransformComponent>(-10,1383, 0.65f);
    line.addComponent<SpriteComponent>(LINE2_TEXTURE_FILE_PATH);
    line.addComponent<TransformComponent>(0,0);
    line.addComponent<SpriteComponent>(LINE_TEXTURE_FILE_PATH);
    line.addComponent<TransformComponent>(SCREEN_WIDTH - 20,0);
    line.addComponent<SpriteComponent>(LINE_TEXTURE_FILE_PATH);
    line.addComponent<TransformComponent>(-20, SCREEN_HEIGHT - 20);
    line.addComponent<SpriteComponent>(LINE_H_TEXTURE_FILE_PATH);
    /*  Map   */

    /*  Colliders  */

    //wall
      // TOP
    wall.addComponent<TransformComponent>(0,0,390,0);
    wall.addComponent<CollisionComponent>("w1.1");
    goal2.addComponent<TransformComponent>(390,0,SCREEN_WIDTH-390*2,0);
    goal2.addComponent<CollisionComponent>("g2");
    wall.addComponent<TransformComponent>(SCREEN_WIDTH-390,0,SCREEN_WIDTH-390,0);
    wall.addComponent<CollisionComponent>("w1.2");

      // RIGHT
    wall.addComponent<TransformComponent>(0,0,0,SCREEN_HEIGHT*2);
    wall.addComponent<CollisionComponent>("w2");

      // LEFT
    wall.addComponent<TransformComponent>(SCREEN_WIDTH,0,0,SCREEN_HEIGHT*2);
    wall.addComponent<CollisionComponent>("w3");

      // BOT
    wall.addComponent<TransformComponent>(0,SCREEN_HEIGHT*2,390,0);
    wall.addComponent<CollisionComponent>("w4.1");
    goal1.addComponent<TransformComponent>(390,SCREEN_HEIGHT*2,SCREEN_WIDTH-390*2,0);
    goal1.addComponent<CollisionComponent>("g1");
    wall.addComponent<TransformComponent>(SCREEN_WIDTH-390,SCREEN_HEIGHT*2,SCREEN_WIDTH-390,0);
    wall.addComponent<CollisionComponent>("w4.2");
    /*  Colliders  */

    /*PLAYERS*/
    player1->init(RiverPlateFootballerSprite);
    player2->init(BocaFootballerSprite);

    activeStar.addComponent<TransformComponent>(
      Logic::currentFootballer1->getComponent<TransformComponent>().position.x - 5,
      Logic::currentFootballer1->getComponent<TransformComponent>().position.y - 25,
      0.25f
    );
    activeStar.addComponent<SpriteComponent>(PLAYER1_STAR);

    unactiveStar.addComponent<TransformComponent>(
      Logic::currentFootballer2->getComponent<TransformComponent>().position.x + 5,
      Logic::currentFootballer2->getComponent<TransformComponent>().position.y - 25,
      1.0f
    );
    unactiveStar.addComponent<SpriteComponent>(PLAYER2_STAR);

    srand(time(NULL));

    int randomNumber = rand();
    Logic::ballState = randomNumber % 2 + 1;

    resetPlayerFootballerPositions();

    Logic::ballState = NONE;
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
  player2->setCurrentFootballer();

  // check player1 collide with ball
  for(int p = 0; p < MAX_NUM_OF_PLAYERS; p+=1)
  {
    if(
      Collision::AABB(player1->footballers[p]->getComponent<CollisionComponent>(),
      ball->entity->getComponent<CollisionComponent>())
    )
    {
      if(!Logic::playerPassBall)
      {
        if(player1->footballers[p]->getComponent<TransformComponent>().a.y>=0)
        {
          ball->entity->getComponent<TransformComponent>().setTopLeftPos(
            Logic::player1Position[p].y + 10, Logic::player1Position[p].x
          );
        }
        else{
          ball->entity->getComponent<TransformComponent>().setTopLeftPos(
            Logic::player1Position[p].y - 10, Logic::player1Position[p].x
          );
        }

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
        Logic::ballState = PLAYER1_GETBALL;
        Logic::currentFootballer1 = player1->footballers[p];
        Logic::playerTouchBall = true;
        break;
      }
    }
    else
    {
      Logic::playerTouchBall = false;
      Logic::ballState = NONE;
    }
  }

  // check player2 collide with ball
  for(int p = 0; p < MAX_NUM_OF_PLAYERS; p+=1)
  {
    if(
      Collision::AABB(player2->footballers[p]->getComponent<CollisionComponent>(),
      ball->entity->getComponent<CollisionComponent>())
    )
    {
      if(!Logic::playerPassBall)
      {
        if(player2->footballers[p]->getComponent<TransformComponent>().a.y>=0)
        {
          ball->entity->getComponent<TransformComponent>().setTopLeftPos(
            Logic::player2Position[p].y + 10, Logic::player2Position[p].x
          );
        }
        else{
          ball->entity->getComponent<TransformComponent>().setTopLeftPos(
            Logic::player2Position[p].y - 10, Logic::player2Position[p].x
          );
        }

        if(player2->footballers[p]->getComponent<TransformComponent>().a == Vector2(0.0f,0.0f))
        {
          ball->entity->getComponent<TransformComponent>().setA(
            Vector2(0.0f, -0.7f)
          );
        }
        else
        {
          ball->entity->getComponent<TransformComponent>().setA(
            player2->footballers[p]->getComponent<TransformComponent>().a
          );
        }
        Logic::ballState = PLAYER2_GETBALL;
        Logic::currentFootballer2 = player2->footballers[p];
        Logic::playerTouchBall = true;
        break;
      }
    }
  }

  // other colliders
  for(auto& i : this->colliders)
  {
    // printf("%s\n", i->tag);
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

      // footballers collided with wall
      for(int p = 0; p < MAX_NUM_OF_PLAYERS; p+=1){
        if(Collision::AABB(player2->footballers[p]->getComponent<CollisionComponent>(), *i))
        {
          player2->footballers[p]->getComponent<TransformComponent>().position = Logic::player2Position[p];
        }
      }
    }

    if((i->tag[0] == 'g' && i->tag[1] == '1') || (i->tag[0] == 'g' && i->tag[1] == '2') )
    {
      // ball collided with goal
      if(Collision::AABB(ball->entity->getComponent<CollisionComponent>(), *i))
      {
        ball->setBallDefaultPosition();
        if(i->tag[1] == '1')
        {
          Logic::player1Score += 1;
          Logic::ballState = PLAYER1_SCORED;
        }
        else
        {
          Logic::player2Score += 1;
          Logic::ballState = PLAYER2_SCORED;
        }
        resetPlayerFootballerPositions();
    }
    }

    // if ball hits mud
    if(i->tag[0] == 'm')
    {
      if(Collision::AABB(ball->entity->getComponent<CollisionComponent>(), *i)){
        Logic::deceleratorEntities(0.05f, ball->entity);
      }
    }
  }

  player1->controlFootballers();

  activeStar.getComponent<TransformComponent>().setTopLeftPos(
    Logic::currentFootballer1->getComponent<TransformComponent>().position.y - 25,
    Logic::currentFootballer1->getComponent<TransformComponent>().position.x - 5
  );

  unactiveStar.getComponent<TransformComponent>().setTopLeftPos(
    Logic::currentFootballer2->getComponent<TransformComponent>().position.y - 25,
    Logic::currentFootballer2->getComponent<TransformComponent>().position.x + 5
  );

}

void Game::render(){
  SDL_RenderClear(this->renderer);

  for(auto& i : tiles)
  {
    i->draw();
  }

  line.draw();

  std::vector<Entity*> allEntities(player1->footballers.begin(), player1->footballers.end());
  allEntities.insert(allEntities.end(), player2->footballers.begin(), player2->footballers.end());
  allEntities.push_back(ball->entity);

  std::sort(allEntities.begin(), allEntities.end(), [](Entity* a, Entity* b){
    return a->getComponent<TransformComponent>().position.y < b->getComponent<TransformComponent>().position.y;
  });

  for(auto& i : allEntities)
  {
    i->draw();
  }

  drawActiveStar();
  drawUnactiveStar();

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

void drawActiveStar(){
  if(activeStar.getComponent<TransformComponent>().position.y < Game::camera.y)
  {
    activeStar.getComponent<TransformComponent>().position.y =  Game::camera.y;
  }
  else if(activeStar.getComponent<TransformComponent>().position.y > Game::camera.y + Game::camera.h){
    activeStar.getComponent<TransformComponent>().position.y = Game::camera.y + Game::camera.h - 20;
  }
  activeStar.draw();
}

void drawUnactiveStar(){
  if(unactiveStar.getComponent<TransformComponent>().position.y< Game::camera.y)
  {
    unactiveStar.getComponent<TransformComponent>().position.y =  Game::camera.y;
  }
  else if(unactiveStar.getComponent<TransformComponent>().position.y > Game::camera.y + Game::camera.h){
    unactiveStar.getComponent<TransformComponent>().position.y = Game::camera.y + Game::camera.h - 20;
  }
  unactiveStar.draw();
}