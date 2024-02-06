#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ECS.hpp"
#include "Component.hpp"
#include "../TextureManager.hpp"
#include "../config.hpp"

class SpriteComponent : public Component{
  private:
    TransformComponent* transform;
    std::vector<SDL_Texture*> texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int speed = SPEED;
    int numberOfFrame = 1;

  public:
    int currentIndex = 0;
    // std::map<

  public:
    SpriteComponent(){
      this->srcRect.h = 0;
      this->srcRect.w = 0;
      this->destRect.h = 0;
      this->destRect.w = 0;
    };

    SpriteComponent(const char* spritePath, float scale = 1){
      this->texture.emplace_back(std::move(TextureManager::loadTexture(spritePath)));
      setRect(scale);
    }

    SpriteComponent(const std::vector<const char*> spritePaths, int numberOfFrame, int speed, float scale = 1){
      this->animated = true;
      this->speed = speed;
      this->numberOfFrame = numberOfFrame;

      for(auto& item : spritePaths){
        this->texture.emplace_back(std::move(TextureManager::loadTexture(item)));
      }

      setRect(scale, numberOfFrame);
    }

    void setTexture(const char* spritePath, float scale = 1){
      this->texture.emplace_back(std::move(TextureManager::loadTexture(spritePath)));
      setRect(scale);
    }

    void setRect(float scale = 1, int col = 1, int row = 1, int index = 0){
      SDL_QueryTexture(this->texture[index], nullptr, nullptr, &this->srcRect.w, &this->srcRect.h);

      this->srcRect.x = 0;
      this->srcRect.y = 0;
      this->srcRect.w /= col;
      this->srcRect.h /= row;

      this->destRect.w =  this->srcRect.w * scale;
      this->destRect.h = this->srcRect.h * scale;
    }

    void setSrcRect(int width, int height, int scale = 1){
      this->srcRect.w = width;
      this->srcRect.h = height;

      this->destRect.h = height*scale;
      this->destRect.w = width*scale;
    }

    void setDestRect(int width, int height){
      this->destRect.h = height;
      this->destRect.w = width;
    }

    void init() override{
      this->transform = &(this->entity)->getComponent<TransformComponent>();
      this->destRect.x = this->transform->position.x;
      this->destRect.y = this->transform->position.y;
    }

    void draw() override{
      TextureManager::draw(this->texture[currentIndex], srcRect, destRect);
    }

    void update() override{
      if(this->animated){
        this->srcRect.x = this->srcRect.w * ((SDL_GetTicks()/this->speed) % this->numberOfFrame);
      }

      this->srcRect.y = this->currentIndex * this->srcRect.w;


      this->destRect.x = static_cast<int>(this->transform->position.x);
      this->destRect.y = static_cast<int>(this->transform->position.y);
    }

    ~SpriteComponent(){
      for(auto& item : this->texture){
        SDL_DestroyTexture(item);
      }

    }

};

#endif