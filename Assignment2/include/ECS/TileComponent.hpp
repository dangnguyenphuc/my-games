#ifndef TILE_COMPONENT_HPP
#define TILE_COMPONENT_HPP

#pragma once
#include "Component.hpp"
#include "ECS.hpp"
#include "../config.hpp"
#include "../Vector2.hpp"
#include "../TextureManager.hpp"

class TileComponent : public Component{
  public:
    int id;
    TransformComponent* transform;
    SpriteComponent* sprite;

    const char* path;
    float scale;
    Vector2 position;

  private:
    bool isCollider = false;

  public:
    TileComponent(){

    }

    TileComponent(int x, int y, int id = 0 ,float scale = 1.0f){
      this->id = id;
      this->scale = scale;
      this->position.x = float(x);
      this->position.y = float(y);

      switch(id){
        case 0:
          this->path = GRASS_TILE_FILE_PATH;
          break;

        case 1:
          this->path = MUD_TILE_FILE_PATH;
          this->isCollider = true;
          break;

        default:
          break;
      }
    }

    ~TileComponent(){

    }

    void init() override{
      this->entity->addComponent<TransformComponent>(this->position.x, this->position.y, this->scale);
      this->transform = &(this->entity)->getComponent<TransformComponent>();

      this->entity->addComponent<SpriteComponent>(this->path);
      this->sprite = &(this->entity)->getComponent<SpriteComponent>();


      if(this->isCollider)
      {
        this->entity->addComponent<CollisionComponent>("m");
      }
    }

    void update() override{
      this->sprite->destRect.x = this->position.x - Game::camera.x;
      this->sprite->destRect.y = this->position.y - Game::camera.y;
    }

};

#endif