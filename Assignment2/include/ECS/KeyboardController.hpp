#ifndef KEYBOARD_CONTROLLER_HPP
#define KEYBOARD_CONTROLLER_HPP

#pragma once
#include "ECS.hpp"
#include "../Game.hpp"
#include "Component.hpp"
#include "../Logic.hpp"

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
    bool enable = false;
  public:
    void update() override{
      if(enable)
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
            default:
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