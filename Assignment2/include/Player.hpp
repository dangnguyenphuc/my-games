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

      if(GET_PLAYER_GROUP == GROUP_PLAYER1)
      {
        this->footballers[0]->getComponent<TransformComponent>().setTopLeftPos(
          SCREEN_HEIGHT - 200,
          100
        );

        this->footballers[1]->getComponent<TransformComponent>().setTopLeftPos(
          SCREEN_HEIGHT - 200,
          SCREEN_CENTER_WIDTH - 32
        );

        this->footballers[2]->getComponent<TransformComponent>().setTopLeftPos(
          SCREEN_HEIGHT - 200,
          SCREEN_WIDTH - 32 - 100
        );

        this->footballers[0]->addComponent<FootballKeyboardController>(true);
        Logic::currentFootballer1 = this->footballers[0];

        for(int i = 1; i < MAX_NUM_OF_PLAYERS; i+=1){
          this->footballers[i]->addComponent<FootballKeyboardController>();
        }
      }
      else
      {
        this->footballers[0]->getComponent<TransformComponent>().setTopLeftPos(
          SCREEN_HEIGHT + 200,
          100
        );

        this->footballers[1]->getComponent<TransformComponent>().setTopLeftPos(
          SCREEN_HEIGHT + 200,
          SCREEN_CENTER_WIDTH - 32
        );

        this->footballers[2]->getComponent<TransformComponent>().setTopLeftPos(
          SCREEN_HEIGHT + 200,
          SCREEN_WIDTH - 32 - 100
        );

        // this->footballers[0]->addComponent<FootballKeyboardController>(true);

        // for(int i = 1; i < MAX_NUM_OF_PLAYERS; i+=1){
        //   this->footballers[i]->addComponent<FootballKeyboardController>();
        // }
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



    ~Player(){
      footballers.clear();
    }
};


#endif