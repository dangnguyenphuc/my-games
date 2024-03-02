#ifndef KEYBOARD_CONTROLLER_HPP
#define KEYBOARD_CONTROLLER_HPP

#pragma once
#include "ECS.hpp"
#include "../Game.hpp"
#include "Component.hpp"
#include "../Logic.hpp"
#include "../config.hpp"

class KeyboardController : public Component{
  protected:
    TransformComponent* transform;
    SpriteComponent* sprite;
  public:
    void init() override{
      this->transform = &(this->entity)->getComponent<TransformComponent>();
      this->sprite = &(this->entity)->getComponent<SpriteComponent>();
    }
};

class FootballKeyboardController : public KeyboardController{
  public:
    bool enable;
    int id;
    static int currentId;
  private:
    bool teamId;
  private:
    int debounceButton = 2;
  public:
    FootballKeyboardController(const bool& enable=false, const bool& teamId=false) : enable(enable), teamId(teamId){
      this->id = currentId;
      currentId += 1;
    };


    ~FootballKeyboardController(){

    }

    void update() override{
      if(!this->teamId)
      {
        if(this->enable)
        {
          if(Game::event.type == SDL_KEYDOWN)
          {
            switch(Game::event.key.keysym.sym)
            {
              case SDLK_w:
                this->transform->a.y = -1;
                this->sprite->play(WALK_BACK);
                // printf("w\n");
                break;

              case SDLK_s:
                this->transform->a.y =  1;
                this->sprite->play(WALK_FRONT);
                // printf("s\n");
                break;

              case SDLK_a:
                this->transform->a.x = -1;
                this->sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                this->sprite->play(WALK_RIGHT);
                // printf("a\n");
                break;

              case SDLK_d:
                this->transform->a.x = 1;
                this->sprite->play(WALK_RIGHT);
                // printf("d\n");
                break;

              case SDLK_e:
                if(this->debounceButton <= 0){
                  this->debounceButton = 2;
                  this->transform->a.x = 0;
                  this->transform->a.y = 0;
                  this->sprite->play(IDLE);
                  printf("footballer %d is choosing\n", this->id);

                  this->enable = false;
                  Logic::currentFootballer1 =  Game::manager.getGroup(GROUP_PLAYER1)[(this->id+1)%MAX_NUM_OF_PLAYERS];
                  Logic::currentFootballer1->getComponent<FootballKeyboardController>().enable = true;
                  Logic::currentFootballer1->getComponent<TransformComponent>().a.Zero();
                }

                this->debounceButton -= 1;

                // printf("nextPlayer id: %d\n",  this->nextPlayer.getComponent<FootballKeyboardController>().id);
                break;

              default:
                this->debounceButton = 2;
                break;
            }
          }

          if(Game::event.type == SDL_KEYUP)
          {
            switch(Game::event.key.keysym.sym)
            {
              case SDLK_w:
                this->transform->a.y = 0;
                this->sprite->play(IDLE);
                break;
              case SDLK_s:
                this->transform->a.y =  0;
                this->sprite->play(IDLE);
                break;
              case SDLK_a:
                this->transform->a.x = 0;
                this->sprite->spriteFlip = SDL_FLIP_NONE;
                this->sprite->play(IDLE);
                break;
              case SDLK_d:
                this->transform->a.x = 0;
                this->sprite->play(IDLE);
                break;
              case SDLK_e:
                break;
              default:
                break;
            }
          }
        }
      }
      else
      {
        if(this->enable)
        {
          if(Game::event.type == SDL_KEYDOWN)
          {
            switch(Game::event.key.keysym.sym)
            {
              case SDLK_UP:
                this->transform->a.y = -1;
                this->sprite->play(WALK_BACK);
                // printf("w\n");
                break;

              case SDLK_DOWN:
                this->transform->a.y =  1;
                this->sprite->play(WALK_FRONT);
                // printf("s\n");
                break;

              case SDLK_LEFT:
                this->transform->a.x = -1;
                this->sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                this->sprite->play(WALK_RIGHT);
                // printf("a\n");
                break;

              case SDLK_RIGHT:
                this->transform->a.x = 1;
                this->sprite->play(WALK_RIGHT);
                // printf("d\n");
                break;

              case SDLK_RSHIFT:
                if(this->debounceButton <= 0){
                  this->debounceButton = 2;
                  this->transform->a.x = 0;
                  this->transform->a.y = 0;
                  this->sprite->play(IDLE);
                  printf("footballer %d is choosing\n", this->id);

                  this->enable = false;
                  Logic::currentFootballer2 =  Game::manager.getGroup(GROUP_PLAYER2)[(this->id+1)%MAX_NUM_OF_PLAYERS];
                  Logic::currentFootballer2->getComponent<FootballKeyboardController>().enable = true;
                  Logic::currentFootballer2->getComponent<TransformComponent>().a.Zero();
                }

                this->debounceButton -= 1;

                // printf("nextPlayer id: %d\n",  this->nextPlayer.getComponent<FootballKeyboardController>().id);
                break;

              default:
                this->debounceButton = 2;
                break;
            }
          }

          if(Game::event.type == SDL_KEYUP)
          {
            switch(Game::event.key.keysym.sym)
            {
              case SDLK_UP:
                this->transform->a.y = 0;
                this->sprite->play(IDLE);
                break;
              case SDLK_DOWN:
                this->transform->a.y =  0;
                this->sprite->play(IDLE);
                break;
              case SDLK_LEFT:
                this->transform->a.x = 0;
                this->sprite->spriteFlip = SDL_FLIP_NONE;
                this->sprite->play(IDLE);
                break;
              case SDLK_RIGHT:
                this->transform->a.x = 0;
                this->sprite->play(IDLE);
                break;
              default:
                break;
            }
          }
        }
      }
    }

  void goStraight(const int& zone){
    this->transform->a.Zero();
    Vector2 howToMove = Vector2(Logic::zones[zone].x + Logic::zones[zone].w/2, Logic::zones[zone].y + Logic::zones[zone].h/2) - this->transform->position;
    if(howToMove.y > 0.2f)
    {
      this->transform->a.y =  1;
      this->sprite->play(WALK_FRONT);
    }
    else if(howToMove.y < -0.2f)
    {
      this->transform->a.y =  -1;
      this->sprite->play(WALK_BACK);
    }
    else{
      this->transform->a.Zero();
      this->sprite->play(IDLE);
    }
  }

  void goCross(const int& zone){
    Vector2 howToMove = Vector2(Logic::zones[zone].x + Logic::zones[zone].w/2, Logic::zones[zone].y + Logic::zones[zone].h/2) - this->transform->position;
    if(howToMove.x > 0.2f)
    {
      this->transform->a.x =  1;
      this->sprite->play(WALK_RIGHT);
    }
    else if(howToMove.x < -0.2f)
    {
      this->transform->a.x =  -1;
      this->sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
      this->sprite->play(WALK_RIGHT);
    }
  }

  void autoGetBall(){

    if(!Logic::playerTouchBall)
    {
      Vector2 howToMove = Logic::ballPosition - this->transform->position;
      if(howToMove.x > 0.2f)
      {
        this->transform->a.x =  1;
        this->sprite->play(WALK_RIGHT);
      }
      else if(howToMove.x < -0.2f)
      {
        this->transform->a.x =  -1;
        this->sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
        this->sprite->play(WALK_RIGHT);
      }

      if(howToMove.y > 0.2f)
      {
        this->transform->a.y =  1;
        this->sprite->play(WALK_FRONT);
      }
      else if(howToMove.y < -0.2f)
      {
        this->transform->a.y =  -1;
        this->sprite->play(WALK_BACK);
      }
    }
    else
    {
      this->transform->a.Zero();
      this->sprite->play(IDLE);
    }
  }

  void stop(){
    this->transform->a.Zero();
    this->sprite->play(IDLE);
  }

  void returnZone(const int& zone){
    Vector2 howToMove = Vector2(Logic::zones[zone].x + Logic::zones[zone].w/2, Logic::zones[zone].y + Logic::zones[zone].h/2) - this->transform->position;
    if(howToMove.x > 0.2f)
      {
        this->transform->a.x =  1;
        this->sprite->play(WALK_RIGHT);
      }
      else if(howToMove.x < -0.2f)
      {
        this->transform->a.x =  -1;
        this->sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
        this->sprite->play(WALK_RIGHT);
      }

      if(howToMove.y > 0.2f)
      {
        this->transform->a.y =  1;
        this->sprite->play(WALK_FRONT);
      }
      else if(howToMove.y < -0.2f)
      {
        this->transform->a.y =  -1;
        this->sprite->play(WALK_BACK);
      }
  }
};


class BallKeyboardController : public KeyboardController{

  public:
    void update() override{
      if(Logic::ballState==PLAYER1_GETBALL)
      {
        if(Game::event.type == SDL_KEYDOWN)
        {
          switch(Game::event.key.keysym.sym)
          {
            case SDLK_f:
              if(Logic::playerTouchBall && !Logic::playerPassBall)
              {
                this->kickTheBall();
                Logic::playerPassBall = true;
                Logic::playerTouchBall = false;
              }
              break;
            default:
              Logic::playerPassBall = false;
              break;
          }
        }
      }

      else if(Logic::ballState==PLAYER2_GETBALL)
      {
        if(Game::event.type == SDL_KEYDOWN)
        {
          switch(Game::event.key.keysym.sym)
          {
            case SDLK_RETURN:
              if(Logic::playerTouchBall && !Logic::playerPassBall)
              {
                this->kickTheBall();
                Logic::playerPassBall = true;
                Logic::playerTouchBall = false;
              }
              break;
            default:
              Logic::playerPassBall = false;
              break;
          }
        }
      }

      else
      {
        Logic::playerPassBall = false;
        Logic::playerPassBall = false;
      }
    }

    void kickTheBall(){
      // printf("Kick\n");
      if(this->transform->a.y > 0)
      {
        this->transform->position.y += 23;
      }
      else if(this->transform->a.y < 0)
      {
        this->transform->position.y -= 23;
      }

      if(this->transform->a.x > 0)
      {
        this->transform->position.x += 33;
      }
      else if(this->transform->a.x < 0)
      {
        this->transform->position.x -= 33;
      }

      this->transform->a *= 2.2f;
    }
};

#endif