#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ECS.hpp"
#include "../TextureManager.hpp"

class SpriteComponent : public Component{
  private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    // bool animated = false;

  public:
    SpriteComponent(){
      this->srcRect.h = 0;
      this->srcRect.w = 0;
      this->destRect.h = 0;
      this->destRect.w = 0;
    };

    SpriteComponent(const char* spritePath, float scale = 1){
      this->texture = TextureManager::loadTexture(spritePath);
      setRect(scale);
    }

    void setTexture(const char* spritePath, float scale = 1){
      this->texture = TextureManager::loadTexture(spritePath);
      setRect(scale);
    }

    void setRect(float scale = 1){
      SDL_QueryTexture(this->texture, nullptr, nullptr, &this->srcRect.w, &this->srcRect.h);

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
      TextureManager::draw(this->texture, srcRect, destRect);
    }

    void update() override{
      this->destRect.x = this->transform->position.x;
      this->destRect.y = this->transform->position.y;
    }

    ~SpriteComponent(){
    }

};

#endif