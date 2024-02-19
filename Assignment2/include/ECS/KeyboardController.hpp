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
    int debounceButton = 2;
  public:
    FootballKeyboardController(bool enable=false) : enable(enable){
      this->id = currentId;
      currentId += 1;
    };


    ~FootballKeyboardController(){

    }

    void update() override{
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
                printf("player %d e\n", this->id);
                this->enable = false;
                Game::manager.getGroup(GROUP_PLAYER1)[(this->id+1)%MAX_NUM_OF_PLAYERS]->getComponent<FootballKeyboardController>().enable = true;
              }

              this->debounceButton -= 1;

              // printf("nextPlayer id: %d\n",  this->nextPlayer.getComponent<FootballKeyboardController>().id);
              break;

            default:
              this->debounceButton = 2;
              break;
          }
        }

        if(Game::event.type == SDL_KEYUP){
          switch(Game::event.key.keysym.sym){
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
};


class BallKeyboardController : public KeyboardController{
  public:
    void update() override{
      if(Game::event.type == SDL_KEYDOWN){
        switch(Game::event.key.keysym.sym){
          case SDLK_SPACE:
            if(Logic::playerTouchBall){
              printf("Space\n");
              this->transform->a *= 2;
              Logic::playerPassBall = true;
              Logic::playerTouchBall = false;
            }
            break;
          default:
            break;
        }
      }

      if(Game::event.type == SDL_KEYUP){
        switch(Game::event.key.keysym.sym){
          case SDLK_SPACE:
            // Logic::playerTouchBall = false;
            Logic::playerPassBall = false;
            break;
          default:
            break;
        }
      }
    }
};

#endif