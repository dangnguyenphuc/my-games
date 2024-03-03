#include "../include/Game.hpp"
#include "../include/TextureManager.hpp"
#include "../include/ECS/Component.hpp"
#include "../include/Map.hpp"
#include "../include/Collision.hpp"
#include "../include/Logic.hpp"
#include "../include/Player.hpp"
#include "../include/Ball.hpp"
#include "../include/Timer.hpp"
#include "../include/UI.hpp"
#include <string.h>
#include <stdlib.h>
#include <time.h>

// static attributes
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<CollisionComponent*> Game::colliders;
SDL_Rect Game::camera = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
TTF_Font* Game::font = nullptr;
int Game::gameState = EXIT;

// Game instances
Timer timeToPlay(TIME_TO_PLAY);
Timer timeToKick(2);
Manager Game::manager;
Player* player1 = new Player(0);
Player* player2 = new Player(1);
Ball* Game::ball = new Ball();

Entity& line = Game::manager.addEntity();
Entity& wall = Game::manager.addEntity();
Entity& activeStar = Game::manager.addEntity();
Entity& unactiveStar = Game::manager.addEntity();
Entity& timer = Game::manager.addEntity();
Entity& timerValue = Game::manager.addEntity();
Entity& scoreBorder = Game::manager.addEntity();
Entity& score = Game::manager.addEntity();

void drawActiveStar();
void drawUnactiveStar();
void resetPlayerFootballerPositions();
void checkPlayer1withBall();
void checkPlayer2withBall();
void runGame();
void buttonPvPClicked();
void buttonPvCClicked();
void buttonReplayClicked();
void buttonReturnClicked();
void setGameStartPosition();


Button* pvpButton = new Button(buttonPvPClicked);
Button* pvcButton = new Button(buttonPvCClicked);
Button* replayButton = new Button(buttonReplayClicked);
Button* returnButton = new Button(buttonReturnClicked);
Menu* startMenu = new Menu();
Menu* endMenu = new Menu();


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
    this->gameState = ACTIVE_START;

    // font
    TTF_Init();
    Game::font = TTF_OpenFont(JETBRAINSMONO_FONT_FILE_PATH, 25);
    if (Game::font == nullptr) {
      printf("Cannot load font\n");
      this->gameState = EXIT;
    }

    // button
    pvpButton->init(START_MENU_P1_BUTTON, SCREEN_CENTER_WIDTH - 140, SCREEN_CENTER_HEIGHT);
    pvcButton->init(START_MENU_P2_BUTTON, SCREEN_CENTER_WIDTH - 140, SCREEN_CENTER_HEIGHT + 100);
    startMenu->init(START_MENU_BACKGROUND, 0.8f);
    startMenu->addButton(pvpButton);
    startMenu->addButton(pvcButton);

    replayButton->init(END_MENU_REPLAY_BUTTON, SCREEN_CENTER_WIDTH - 100, SCREEN_CENTER_HEIGHT + 100);
    returnButton->init(END_MENU_RETURN_BUTTON, SCREEN_CENTER_WIDTH - 100, SCREEN_CENTER_HEIGHT + 200);
    endMenu->init(END_MENU_BACKGROUND, 0.8f);
    endMenu->addButton(replayButton);
    endMenu->addButton(returnButton);
    /*
    timer
    */
    timer.addComponent<TransformComponent>();
    timer.addComponent<SpriteComponent>(TIMER_BORDER_TEXTURE_FILE_PATH);
    timer.getComponent<TransformComponent>().position.x = SCREEN_WIDTH - 142;
    timer.addComponent<CollisionComponent>("bo1");

    timerValue.addComponent<TransformComponent>();
    timerValue.addComponent<SpriteComponent>();
    timerValue.getComponent<SpriteComponent>().setDefaultTextTexture(timeToPlay.timeToString().c_str());
    timerValue.getComponent<TransformComponent>().position.x = SCREEN_WIDTH - 65;

    scoreBorder.addComponent<TransformComponent>();
    scoreBorder.addComponent<SpriteComponent>(SCORE_BORDER_TEXTURE_FILE_PATH);
    scoreBorder.getComponent<TransformComponent>().position.x = 0;
    scoreBorder.addComponent<CollisionComponent>("bo2");

    score.addComponent<TransformComponent>();
    score.addComponent<SpriteComponent>();
    score.getComponent<SpriteComponent>().setDefaultTextTexture((std::to_string(Logic::player1Score) + ":" + std::to_string(Logic::player2Score)).c_str());
    score.getComponent<TransformComponent>().position.x = 25;
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
    wall.addComponent<TransformComponent>(390,0,SCREEN_WIDTH-390*2,0);
    wall.addComponent<CollisionComponent>("g2");
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
    wall.addComponent<TransformComponent>(390,SCREEN_HEIGHT*2,SCREEN_WIDTH-390*2,0);
    wall.addComponent<CollisionComponent>("g1");
    wall.addComponent<TransformComponent>(SCREEN_WIDTH-390,SCREEN_HEIGHT*2,SCREEN_WIDTH-390,0);
    wall.addComponent<CollisionComponent>("w4.2");
    /*  Colliders  */

    /*PLAYERS*/
    player1->init(ArgentinaFootballerSprite);
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

    // positions
    setGameStartPosition();

    /*BALL*/
    ball->init(BALL_TEXTURE_FILE_PATH);

    printf("init completed with state %d\n", Game::gameState);
  }
  else
  {
    this->gameState = EXIT;
  }
}

void Game::handleEvent(){

  SDL_PollEvent(&event);

  switch(event.type){

    case SDL_QUIT:
      this->gameState = EXIT;
      break;

    default:
      break;
  }

}

std::vector<Entity*>& tiles = Game::manager.getGroup(GROUP_MAP);

void Game::update(){
  switch(Game::gameState){
    case ACTIVE_START:
      Game::manager.refresh();
      Game::manager.update();
      startMenu->update();
      break;
    case IS_RUNNING_VS_COMPUTER:
      player2->disableAllFootballer();
      if(Logic::ballState == PLAYER2_GETBALL){
        timeToKick.run();
        if(timeToKick.flag)
        {
          timeToKick.reset();
          ball->kick();
        }
      }
      else
      {
        timeToKick.reset();
      }
    case IS_RUNNING:
      runGame();
      if(timeToPlay.flag)
      {
        timeToPlay.reset();
        Game::gameState = ACTIVE_END;
        Game::camera.y = 0;
      }
      break;
    case ACTIVE_END:
      score.getComponent<TransformComponent>().position.y = SCREEN_CENTER_HEIGHT - 150;
      score.getComponent<TransformComponent>().position.x = SCREEN_CENTER_WIDTH - 250;
      score.getComponent<SpriteComponent>().setDefaultTextTexture(("PLAYER 1: " + std::to_string(Logic::player1Score) + "          PLAYER 2:" + std::to_string(Logic::player2Score)).c_str());
      ball->setBallDefaultPosition();
      Game::manager.refresh();
      Game::manager.update();
      endMenu->update();
      break;
    default:
      break;
  }
}

void Game::render(){
  SDL_RenderClear(this->renderer);

  switch(Game::gameState){
    case ACTIVE_START:
      startMenu->draw();
      break;
    case IS_RUNNING_VS_COMPUTER:

    case IS_RUNNING:
      drawGameWhileRunning();
      break;
    case ACTIVE_END:
      endMenu->draw();
      score.draw();
      break;
    default:
      break;
  }

  SDL_RenderPresent(this->renderer);
}

void Game::clean(){
  delete player1;
  delete player2;
  delete ball;
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);
  // TTF_CloseFont(Game::font);
  SDL_Quit();
  // TTF_Quit();
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
  timer.getComponent<TransformComponent>().position.y = camera.y;
  timerValue.getComponent<TransformComponent>().position.y = camera.y + 10;

  scoreBorder.getComponent<TransformComponent>().position.y = camera.y;
  score.getComponent<TransformComponent>().position.y = camera.y + 10;
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

void resetPlayerFootballerPositions(){
  player1->resetPlayerPosition();
  player2->resetPlayerPosition();
  if(Logic::ballState == PLAYER1_SCORED)
  {
    Logic::player1Score += 1;
    player2->setPlayerCFWithBall();
    player1->resetPlayer1CFPosition();
  }
  else if(Logic::ballState == PLAYER2_SCORED)
  {
    Logic::player2Score += 1;
    player1->setPlayerCFWithBall();
    player2->resetPlayer2CFPosition();
  }
  Logic::ballState = NONE;
  Logic::playerTouchBall = false;
  Logic::playerPassBall = false;
  Logic::currentFootballer1 = player1->footballers[MAX_NUM_OF_PLAYERS - 1];
  Logic::currentFootballer2 = player2->footballers[MAX_NUM_OF_PLAYERS - 1];
}

void checkPlayer1withBall(){
  for(int p = 0; p < MAX_NUM_OF_PLAYERS; p+=1)
  {
    if(
      Collision::AABB(player1->footballers[p]->getComponent<CollisionComponent>(),
      Game::ball->entity->getComponent<CollisionComponent>())
    )
    {
      if(!Logic::playerPassBall)
      {
        if(player1->footballers[p]->getComponent<TransformComponent>().a.y>=0)
        {
          Game::ball->entity->getComponent<TransformComponent>().setTopLeftPos(
            Logic::player1Position[p].y + 15, Logic::player1Position[p].x
          );
        }
        else{
          Game::ball->entity->getComponent<TransformComponent>().setTopLeftPos(
            Logic::player1Position[p].y - 15, Logic::player1Position[p].x
          );
        }

        if(player1->footballers[p]->getComponent<TransformComponent>().a == Vector2(0.0f,0.0f))
        {
          Game::ball->entity->getComponent<TransformComponent>().setA(
            Vector2(0.0f, 0.8f)
          );
        }
        else
        {
          Game::ball->entity->getComponent<TransformComponent>().setA(
            player1->footballers[p]->getComponent<TransformComponent>().a
          );
        }
        Logic::ballState = PLAYER1_GETBALL;
        Logic::currentFootballer1 = player1->footballers[p];
        Logic::playerTouchBall = true;
        break;
      }
    }
    else if(Logic::ballState == PLAYER2_GETBALL)
    {
      continue;
    }
    else
    {
      Logic::playerTouchBall = false;
      Logic::ballState = NONE;
    }
  }
}

void checkPlayer2withBall(){
  for(int p = 0; p < MAX_NUM_OF_PLAYERS; p+=1)
  {
    if(
      Collision::AABB(player2->footballers[p]->getComponent<CollisionComponent>(),
      Game::ball->entity->getComponent<CollisionComponent>())
    )
    {
      if(!Logic::playerPassBall)
      {
        if(player2->footballers[p]->getComponent<TransformComponent>().a.y>0)
        {
          Game::ball->entity->getComponent<TransformComponent>().setTopLeftPos(
            Logic::player2Position[p].y + 15, Logic::player2Position[p].x
          );
        }
        else{
          Game::ball->entity->getComponent<TransformComponent>().setTopLeftPos(
            Logic::player2Position[p].y - 15, Logic::player2Position[p].x
          );
        }

        if(player2->footballers[p]->getComponent<TransformComponent>().a == Vector2(0.0f,0.0f))
        {
          Game::ball->entity->getComponent<TransformComponent>().setA(
            Vector2(0.0f, -0.7f)
          );
        }
        else
        {
          Game::ball->entity->getComponent<TransformComponent>().setA(
            player2->footballers[p]->getComponent<TransformComponent>().a
          );
        }
        Logic::ballState = PLAYER2_GETBALL;
        Logic::currentFootballer2 = player2->footballers[p];
        Logic::playerTouchBall = true;
        break;
      }
    }
    else if(Logic::ballState == PLAYER1_GETBALL)
    {
      continue;
    }
    else
    {
      Logic::playerTouchBall = false;
      Logic::ballState = NONE;
    }
  }
}

void Game::runGame(){
  //update time
  timerValue.getComponent<SpriteComponent>().setDefaultTextTexture(timeToPlay.timeToString().c_str());
  score.getComponent<SpriteComponent>().setDefaultTextTexture((std::to_string(Logic::player1Score) + ":" + std::to_string(Logic::player2Score)).c_str());

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

  if(Game::gameState == IS_RUNNING)
  {
    player2->setCurrentFootballer();
  }
  else
  {
    player2->disableAllFootballer();
  }

  if(Logic::ballState == PLAYER1_GETBALL)
  {
    // check player1 collide with ball
    checkPlayer1withBall();
    // check player2 collide with ball
    checkPlayer2withBall();
  }
  else
  {
    // check player2 collide with ball
    checkPlayer2withBall();
    // check player1 collide with ball
    checkPlayer1withBall();
  }

  player1->controlFootballers();
  player2->controlFootballers();


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

    if(i->tag[0] == 'b' && i->tag[1] == 'o')
    {
      // footballers
      for(int p = 0; p < MAX_NUM_OF_PLAYERS; p+=1){
        if(Collision::AABB(player1->footballers[p]->getComponent<CollisionComponent>(), *i))
        {
          player1->footballers[p]->getComponent<TransformComponent>().position = Logic::player1Position[p];
        }
        if(Collision::AABB(player2->footballers[p]->getComponent<CollisionComponent>(), *i))
        {
          player2->footballers[p]->getComponent<TransformComponent>().position = Logic::player2Position[p];
        }
      }

      // ball
      if(Collision::AABB(ball->entity->getComponent<CollisionComponent>(), *i))
      {
        ball->entity->getComponent<TransformComponent>().a *= -1;
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
          Logic::ballState = PLAYER1_SCORED;
        }
        else
        {
          Logic::ballState = PLAYER2_SCORED;
        }
        resetPlayerFootballerPositions();
      }

      // footballers
      for(int p = 0; p < MAX_NUM_OF_PLAYERS; p+=1){
        if(Collision::AABB(player1->footballers[p]->getComponent<CollisionComponent>(), *i))
        {
          player1->footballers[p]->getComponent<TransformComponent>().position = Logic::player1Position[p];
        }
        if(Collision::AABB(player2->footballers[p]->getComponent<CollisionComponent>(), *i))
        {
          player2->footballers[p]->getComponent<TransformComponent>().position = Logic::player2Position[p];
        }
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

  activeStar.getComponent<TransformComponent>().setTopLeftPos(
    Logic::currentFootballer1->getComponent<TransformComponent>().position.y - 25,
    Logic::currentFootballer1->getComponent<TransformComponent>().position.x - 5
  );

  if(Logic::currentFootballer2)
  {
    unactiveStar.getComponent<TransformComponent>().setTopLeftPos(
      Logic::currentFootballer2->getComponent<TransformComponent>().position.y - 25,
      Logic::currentFootballer2->getComponent<TransformComponent>().position.x + 5
    );
  }

  timeToPlay.run();

}

void Game::drawGameWhileRunning(){
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
  timer.draw();
  timerValue.draw();

  scoreBorder.draw();
  score.draw();
}

void buttonPvPClicked(){
  printf("PvP\n");
  Game::gameState = IS_RUNNING;
  Logic::playWithComputer = false;
}

void buttonPvCClicked(){
  printf("PvC\n");
  Game::gameState = IS_RUNNING_VS_COMPUTER;
  Logic::playWithComputer = true;
}

void buttonReplayClicked(){
  printf("Replay\n");
  Game::gameState = (Logic::playWithComputer)? IS_RUNNING_VS_COMPUTER : IS_RUNNING;
  timeToPlay.reset();
  Logic::currentFootballer1 = nullptr;
  Logic::currentFootballer2 = nullptr;
  setGameStartPosition();
}

void buttonReturnClicked(){
  printf("Return Start\n");
  Game::gameState = ACTIVE_START;
}

void setGameStartPosition(){
  srand(time(NULL));
  int randomNumber = rand();
  Logic::ballState = randomNumber % 2 + 1;
  resetPlayerFootballerPositions();
  Logic::player1Score = 0;
  Logic::player2Score = 0;
  Logic::ballState = NONE;
}