#ifndef COLLISION_COMPONENT_HPP
#define COLLISION_COMPONENT_HPP

#pragma once
#include "ECS.hpp"
#include "Component.hpp"
#include <SDL2/SDL.h>
#include "../Game.hpp"

class CollisionComponent : public Component{
  public:
    SDL_Rect collider;
    const char* tag;

    TransformComponent* transform;
  public:
    CollisionComponent(){

    }

    CollisionComponent(const char* tag){
      this->tag = tag;
    }

    ~CollisionComponent(){

    }

    void init() override{
      if(!this->entity->hasComponent<TransformComponent>()){
        this->entity->addComponent<TransformComponent>();
      }

      this->transform = &(this->entity)->getComponent<TransformComponent>();
      Game::colliders.push_back(this);
    }

    void update() override{
      this->collider.x = this->transform->position.x;
      this->collider.y = this->transform->position.y;

      this->collider.w = this->transform->width;
      this->collider.h = this->transform->height;
    }

    void draw() override{

    }
};

#endif