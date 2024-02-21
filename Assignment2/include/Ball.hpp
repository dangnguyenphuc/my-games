#ifndef BALL_HPP
#define BALL_HPP

#pragma once
#include "ECS/ECS.hpp"
#include "ECS/Component.hpp"

class Ball{
  public:
    Entity* entity;
  public:
    Ball(){
      Entity& ball = Game::manager.addEntity();
      this->entity = std::move(&ball);
    }

    ~Ball(){

    }

    void init(const char* spriteSheet){

      // resize entity to 32x32
      this->entity->addComponent<TransformComponent>(0.0625f);

      this->entity->addComponent<SpriteComponent>(spriteSheet);
      this->entity->addComponent<CollisionComponent>("b");
      this->entity->getComponent<TransformComponent>().setTopLeftPos(
        SCREEN_HEIGHT - 32,
        SCREEN_CENTER_WIDTH - 32
      );
      this->entity->addComponent<BallKeyboardController>();
      this->entity->addGroup(GROUP_BALL);
    }

    void defaultDecelerator(const float& decelerator=0.015){
      if(this->entity->getComponent<TransformComponent>().a.x > 0)
      {
        this->entity->getComponent<TransformComponent>().a.x -= decelerator;
        if(this->entity->getComponent<TransformComponent>().a.x <= 0) this->entity->getComponent<TransformComponent>().a.x = 0;
      }
      else if(this->entity->getComponent<TransformComponent>().a.x < 0)
      {
        this->entity->getComponent<TransformComponent>().a.x += decelerator;
        if(this->entity->getComponent<TransformComponent>().a.x >= 0) this->entity->getComponent<TransformComponent>().a.x = 0;
      }

      if(this->entity->getComponent<TransformComponent>().a.y > 0)
      {
        this->entity->getComponent<TransformComponent>().a.y -= decelerator;
        if(this->entity->getComponent<TransformComponent>().a.y <= 0) this->entity->getComponent<TransformComponent>().a.y = 0;
      }
      else if(this->entity->getComponent<TransformComponent>().a.y < 0)
      {
        this->entity->getComponent<TransformComponent>().a.y += decelerator;
        if(this->entity->getComponent<TransformComponent>().a.y >= 0) this->entity->getComponent<TransformComponent>().a.y = 0;
      }
    }

};

#endif