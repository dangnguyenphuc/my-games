#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP
#pragma once
#include "ECS.hpp"
#include "../Vector2.hpp"

class TransformComponent : public Component {
  public:
    Vector2 position;
    Vector2 a;
    float scale = 1;

    int height;
    int width;
    int speed = 3;
    float decelerator = 0.0f;

    TransformComponent(){
      this->position.Zero();
    }

    TransformComponent(float scale){
      this->position.Zero();
      this->scale = scale;
    }

    TransformComponent(float x, float y, float scale = 1){
      this->position.x = x;
      this->position.y = y;
      this->scale = scale;
    }

    TransformComponent(float x, float y, int width, int height, float scale = 1){
      this->position.x = x;
      this->position.y = y;
      this->scale = scale;
      this->width = width;
      this->height = height;
    }

    ~TransformComponent(){

    };

    void init() override{
      this->a.Zero();
      // printf("Position added completely\n");
    }

    void update() override{
      this->position.x = this->position.x + this->a.x * this->speed;
      this->position.y = this->position.y + this->a.y * this->speed;
      // printf("Position update() being called\n");
    }

    void setTopLeftPos(int top, int left){
      this->position.x = left;
      this->position.y = top;
    }

    void setTopLeftPos(Vector2 position){
      this->position.x = position.x;
      this->position.y = position.y;
    }

    void setA(Vector2 a){
      this->a.x = a.x;
      this->a.y = a.y;
    }

};

#endif