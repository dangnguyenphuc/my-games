#ifndef TIMER_HPP
#define TIMER_HPP
#include "config.hpp"

class Timer{
  public:
    int currentTime = 0;
    int time;
    int flag = false;
    int fps;
  public:
    Timer(int time, int fps = FPS){
      this->time = time*fps;
      this->currentTime = this->time;
      this->fps = fps;
    };
    ~Timer(){};
    void run(){
      this->currentTime -= 1;
      if(this->currentTime <= 0)
      {
        this->flag = true;
      }
    }
    void reset(){
      this->flag = false;
      this->currentTime = time;
    }

    std::string timeToString(){
      return std::to_string((int)this->currentTime/this->fps);
    }
};

#endif