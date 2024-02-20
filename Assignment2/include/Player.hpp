#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once
#include "ECS/ECS.hpp"
#include "ECS/Component.hpp"
#include "Game.hpp"

#define GET_PLAYER_GROUP ((teamId)?GROUP_PLAYER1:GROUP_PLAYER2)


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
        footballerTag += std::to_string(this->teamId);  // "pX"
        footballerTag += '.';                                   // "pX."
        footballerTag += static_cast<char>(i);                   // "pX.i"

        this->footballers[i]->addComponent<CollisionComponent>(footballerTag.c_str());
        this->footballers[i]->addGroup(GET_PLAYER_GROUP);
      }

      this->footballers[0]->getComponent<TransformComponent>().setTopLeftPos(
        300,
        0
      );

      this->footballers[1]->getComponent<TransformComponent>().setTopLeftPos(
        300,
        SCREEN_CENTER_WIDTH - 32
      );

      this->footballers[2]->getComponent<TransformComponent>().setTopLeftPos(
        300,
        SCREEN_WIDTH - 32
      );

      this->footballers[0]->addComponent<FootballKeyboardController>(true);

      for(int i = 1; i < MAX_NUM_OF_PLAYERS; i+=1){
        this->footballers[i]->addComponent<FootballKeyboardController>();
      }

    }

    ~Player(){
      footballers.clear();
    }
};


#endif