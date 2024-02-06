#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#pragma once

struct Animation{
  int index;
  int numberOfFrame;
  int speed;

  Animation(){

  }

  Animation(int i, int f, int s){
    index = i;
    numberOfFrame = f;
    speed = s;
  }

};

#endif