#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP
#pragma once
#include "ECS.hpp"

class PositionComponent : public Component {
  private:
    int top;
    int left;

  public:
    int getTop() { return this->top; }
    int getLeft() { return this->left; }

    void init() override{
      this->top = 0;
      this->left = 0;
      printf("Position added completely\n");
    }

    void update() override{
      this->top += 1;
      this->left += 1;
      printf("Position update() being called\n");
    }

    void setTopLeftPos(int top, int left){
      this->top = top;
      this->left = left;
    }
};
#endif