#ifndef TILE_COMPONENT_HPP
#define TILE_COMPONENT_HPP

#pragma once
#include "Component.hpp"
#include "ECS.hpp"
#include "../config.hpp"

class TileComponent : public Component{
  public:
    int id;
    TransformComponent* transform;
    SpriteComponent* sprite;

    const char* path;
    float scale;
    int x;
    int y;



  public:
    TileComponent(){

    }

    TileComponent(int x, int y, int id = 0 ,float scale = 1.0f){
      this->id = id;
      this->scale = scale;
      this->x = x;
      this->y = y;

      switch(id){
        case 0:
          this->path = GRASS_TILE_FILE_PATH;
          break;
        default:
          break;
      }
    }

    ~TileComponent(){

    }

    void init() override{
      this->entity->addComponent<TransformComponent>(float(x), float(y), this->scale);
      this->transform = &(this->entity)->getComponent<TransformComponent>();

      this->entity->addComponent<SpriteComponent>(this->path);
      this->sprite = &(this->entity)->getComponent<SpriteComponent>();
    }
};

#endif