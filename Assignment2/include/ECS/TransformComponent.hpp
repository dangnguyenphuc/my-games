#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP
#pragma once
#include "ECS.hpp"
#include "../Vector2.hpp"

class TransformComponent : public Component {
  public:
    Vector2 position;

    TransformComponent(){
      this->position.x = 0.0f;
      this->position.y = 0.0f;
    }

    TransformComponent(float x, float y){
      this->position.x = x;
      this->position.y = y;
    }

    ~TransformComponent(){

    };

    void init() override{
      this->position.x = 0.0f;
      this->position.y = 0.0f;
      // printf("Position added completely\n");
    }

    void update() override{

      // printf("Position update() being called\n");
    }

    void setTopLeftPos(int top, int left){
      this->position.x = left;
      this->position.y = top;
    }
};
#endif