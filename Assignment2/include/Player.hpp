#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once
#include "ECS/ECS.hpp"
#include "ECS/Component.hpp"
#include "Game.hpp"
#include "Logic.hpp"

#define GET_PLAYER_GROUP ((!teamId)?GROUP_PLAYER1:GROUP_PLAYER2)


class Player{
  private:
    bool isControlled;
    bool teamId;
  public:
    std::vector<std::tuple
      <
        const char*,  // sprite sheet file path
        int,          // id_code for actions such as WALK, IDLE, ...
        int,          // number of frames in sprite sheet
        int           // speed
      >
    > footballerSprite;
    std::vector<Entity*> footballers;
  public:
    Player(bool isControlled, bool teamId=false){

      this->isControlled = isControlled;
      this->teamId = teamId;

      for(int i = 0; i < MAX_NUM_OF_PLAYERS; i+=1){
        Entity& footballer = Game::manager.addEntity();
        this->footballers.emplace_back(std::move(&footballer));
      }
    }

    void init(const std::vector<std::tuple<const char*, int, int, int>>& spriteSheet){
      std::string footballerTag;
      for(int i = 0; i < MAX_NUM_OF_PLAYERS; i+=1){
        this->footballers[i]->addComponent<TransformComponent>(2.0f);
        this->footballers[i]->addComponent<SpriteComponent>(spriteSheet, true);

        footballerTag = "p";                                    // "p"
        footballerTag += std::to_string(this->teamId);          // "pX"
        footballerTag += '.';                                   // "pX."
        footballerTag += static_cast<char>(i);                  // "pX.i"

        this->footballers[i]->addComponent<CollisionComponent>(footballerTag.c_str());
        this->footballers[i]->addGroup(GET_PLAYER_GROUP);
      }

      if(!this->teamId)
      {
        for(int i = 0; i < MAX_NUM_OF_PLAYERS - 1; i+=1){
          this->footballers[i]->addComponent<FootballKeyboardController>();
        }

        this->footballers[MAX_NUM_OF_PLAYERS - 1]->addComponent<FootballKeyboardController>(true, this->teamId);
        Logic::currentFootballer1 = this->footballers[MAX_NUM_OF_PLAYERS - 1];

      }
      else
      {
        for(int i = 0; i < MAX_NUM_OF_PLAYERS - 1; i+=1){
          this->footballers[i]->addComponent<FootballKeyboardController>(false, this->teamId);
        }

        this->footballers[MAX_NUM_OF_PLAYERS - 1]->addComponent<FootballKeyboardController>(true, this->teamId);
        Logic::currentFootballer2 = this->footballers[MAX_NUM_OF_PLAYERS - 1];
      }
    }

    void setCurrentFootballer(){
      for(int i = 0; i < MAX_NUM_OF_PLAYERS; i+=1)
      {
        this->footballers[i]->getComponent<FootballKeyboardController>().enable = false;
      }
      if(!this->teamId)
      {
        Logic::currentFootballer1->getComponent<FootballKeyboardController>().enable = true;
      }
      // else
      // {

      // }
    }

    void resetPlayerPosition(){
      if(!this->teamId)
      {
        this->footballers[0]->getComponent<TransformComponent>().setTopLeftPos(
          Logic::zones[0].h/2 - 32,
          Logic::zones[0].w/2 - 32
        );

        this->footballers[1]->getComponent<TransformComponent>().setTopLeftPos(
          Logic::zones[1].h/2 - 32,
          Logic::zones[0].w + Logic::zones[1].h/2 - 32
        );
      }
      else
      {
        this->footballers[0]->getComponent<TransformComponent>().setTopLeftPos(
          Logic::zones[0].h + Logic::zones[2].h + Logic::zones[4].h/2 - 32,
          Logic::zones[0].w/2 - 32
        );

        this->footballers[1]->getComponent<TransformComponent>().setTopLeftPos(
          Logic::zones[0].h + Logic::zones[2].h + Logic::zones[4].h/2 - 32,
          Logic::zones[0].w + Logic::zones[1].h/2 - 32
        );
      }

      for(auto& i : this->footballers){
        i->getComponent<TransformComponent>().a.Zero();
      }

    }

    void resetPlayer1CFPosition(){
        this->footballers[2]->getComponent<TransformComponent>().setTopLeftPos(
          Logic::zones[0].h + 100 - 32,
          SCREEN_CENTER_WIDTH - 32
        );

    }

    void setPlayerCFWithBall(){
      this->footballers[2]->getComponent<TransformComponent>().setTopLeftPos(
          SCREEN_HEIGHT - 32,
          SCREEN_CENTER_WIDTH - 32
      );
    }

    void resetPlayer2CFPosition(){
        this->footballers[2]->getComponent<TransformComponent>().setTopLeftPos(
          SCREEN_HEIGHT*2 - Logic::zones[0].h - 100 - 32,
          SCREEN_CENTER_WIDTH - 32
        );
    }

    void controlFootballers(){
      if(!this->teamId)
      {
        if(Logic::ballState != PLAYER1_GETBALL)
        {
          if(Logic::checkBallInZone(0))
          {
            if(!getFootballerEnable(0)){
              this->footballers[0]->getComponent<FootballKeyboardController>().autoGetBall();
            }
            if(!getFootballerEnable(1)){
              this->footballers[1]->getComponent<FootballKeyboardController>().returnZone(1);
            }
            if(!getFootballerEnable(2)){
              this->footballers[2]->getComponent<FootballKeyboardController>().returnZone(2);
            }
          }
          else if(Logic::checkBallInZone(1))
          {
            if(!getFootballerEnable(0)){
              this->footballers[0]->getComponent<FootballKeyboardController>().returnZone(0);
            }
            if(!getFootballerEnable(1)){
              this->footballers[1]->getComponent<FootballKeyboardController>().autoGetBall();
            }
            if(!getFootballerEnable(2)){
              this->footballers[2]->getComponent<FootballKeyboardController>().returnZone(2);
            }
          }
          else if(Logic::checkBallInZone(2))
          {
            if(!getFootballerEnable(0)){
              this->footballers[0]->getComponent<FootballKeyboardController>().returnZone(1);
            }
            if(!getFootballerEnable(1)){
              this->footballers[1]->getComponent<FootballKeyboardController>().returnZone(2);
            }
            if(!getFootballerEnable(2)){
              this->footballers[2]->getComponent<FootballKeyboardController>().autoGetBall();
            }
          }
          else if(Logic::checkBallInZone(3))
          {
            if(!getFootballerEnable(0)){
              this->footballers[0]->getComponent<FootballKeyboardController>().returnZone(0);
            }
            if(!getFootballerEnable(1)){
              this->footballers[1]->getComponent<FootballKeyboardController>().autoGetBall();
            }
            if(!getFootballerEnable(2)){
              this->footballers[2]->getComponent<FootballKeyboardController>().returnZone(5);
            }
          }
          else if(Logic::checkBallInZone(4))
          {
            if(!getFootballerEnable(0)){
              this->footballers[0]->getComponent<FootballKeyboardController>().returnZone(2);
            }
            if(!getFootballerEnable(1)){
              this->footballers[1]->getComponent<FootballKeyboardController>().returnZone(3);
            }
            if(!getFootballerEnable(2)){
              this->footballers[2]->getComponent<FootballKeyboardController>().autoGetBall();
            }
          }
          else
          {
            if(!getFootballerEnable(0)){
              this->footballers[0]->getComponent<FootballKeyboardController>().returnZone(3);
            }
            if(!getFootballerEnable(1)){
              this->footballers[1]->getComponent<FootballKeyboardController>().returnZone(4);
            }
            if(!getFootballerEnable(2)){
              this->footballers[2]->getComponent<FootballKeyboardController>().autoGetBall();
            }
          }
        }
        else
        {
          if(!getFootballerEnable(0)){
              this->footballers[0]->getComponent<FootballKeyboardController>().stop();
          }
          if(!getFootballerEnable(1)){
              this->footballers[1]->getComponent<FootballKeyboardController>().stop();
          }
          if(!getFootballerEnable(2)){
              this->footballers[2]->getComponent<FootballKeyboardController>().stop();
          }
          // if(Logic::ballPosition.x < Logic::zones[0].x + Logic::zones[0].w && Logic::ballPosition.y < Logic::zones[0].y + Logic::zones[0].h){
          //   if(!){
          //     this->footballers[0]->getComponent<FootballKeyboardController>().autoGetBall();
          //     Logic::ballState = PLAYER1_GETBALL;
          //   }
          // }

          // if(!this->footballers[0]->getComponent<FootballKeyboardController>().enable){
          //   this->footballers[0]->getComponent<FootballKeyboardController>().returnZone(3);
          // }

        }
      }
    }

    bool getFootballerEnable(const int& index){
      return this->footballers[index]->getComponent<FootballKeyboardController>().enable;
    }


    ~Player(){
      footballers.clear();
    }
};


#endif