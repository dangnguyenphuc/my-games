#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ECS.hpp"
#include "Component.hpp"
#include "../TextureManager.hpp"
#include "../config.hpp"
#include "Animation.hpp"

class SpriteComponent : public Component{
  public:
    SDL_Rect destRect;
  protected:
    TransformComponent* transform;
    std::vector<SDL_Texture*> texture;
    std::vector<SDL_Rect> srcRect;


    bool animated = false;
    int speed = SPEED;
    int numberOfFrame = 1;

  public:
    std::map<int, Animation> animations;
    int currentAction = 0;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    float rotateDegree = 0.0f;
  public:
    SpriteComponent(){
      this->srcRect.push_back({0,0,0,0});
      this->destRect.h = 0;
      this->destRect.w = 0;
    }

    SpriteComponent(const char* spritePath){
      this->texture.emplace_back(
        std::move(
          TextureManager::loadTexture(spritePath)
        )
      );
      this->animated = false;
    }

    SpriteComponent(const std::vector<std::tuple<const char*, int, int, int>>& sprites, bool isAnimated){
      this->animated = isAnimated;

      for(auto& item : sprites){

        this->texture.emplace_back(
          std::move(
            TextureManager::loadTexture( std::get<0>(item))
          )
        );

        animations.emplace(
          std::get<1>(item),
          Animation(
            std::get<1>(item),
            std::get<2>(item),
            std::get<3>(item)
          )
        );
      }

      // IDLE AS THE DEFAULT STATE
      this->play(std::get<1>(sprites[this->currentAction]));
    }

    void setTexture(const char* spritePath){
      this->texture.clear();
      this->texture.emplace_back(std::move(TextureManager::loadTexture(spritePath)));
      setRect();
    }

    void setRect(){
      SDL_Rect tempRect;
      for(int i = 0; i < (int)this->texture.size(); i+=1){

        SDL_QueryTexture(this->texture[i], nullptr, nullptr, &tempRect.w, &tempRect.h);

        tempRect.x = 0;
        tempRect.y = 0;
        if(this->animated) tempRect.w /= this->animations[i].numberOfFrame;

        this->srcRect.push_back(tempRect);
      }

      this->transform->height = this->srcRect[this->currentAction].h  * this->transform->scale;
      this->transform->width = this->srcRect[this->currentAction].w  * this->transform->scale;

      this->destRect.w =  this->srcRect[this->currentAction].w * this->transform->scale;
      this->destRect.h = this->srcRect[this->currentAction].h * this->transform->scale;
    }

    void setSrcRect(const int& width, const int& height, const int& x=0, const int& y=0, const int& index = 0){
      this->srcRect[index].x = x;
      this->srcRect[index].y = y;
      setSrcRectWidth(width, index);
      setSrcRectHeight(height, index);
    }

    void setRotateDegree(const float& rotateDegree){
      this->rotateDegree = rotateDegree;
    }

    void setSrcRectWidth(const int& width, const int& index = 0){
      this->srcRect[index].w = width;
    }

    void setSrcRectHeight(const int& height, const int& index = 0){
      this->srcRect[index].h = height;
    }

    void setDestRect(const int& width, const int& height){
      setDestRectHeight(height);
      setDestRectWidth(width);
    }

    void setDestRectWidth(const int& width){
      this->destRect.w = width;
    }

    void setDestRectHeight(const int& height){
      this->destRect.h = height;
    }


    void init() override{
      this->transform = &(this->entity)->getComponent<TransformComponent>();
      this->destRect.x = this->transform->position.x;
      this->destRect.y = this->transform->position.y;

      this->setRect();
    }

    void draw() override{
      TextureManager::draw(this->texture[currentAction], this->srcRect[currentAction], this->destRect, this->spriteFlip, this->rotateDegree);
    }

    void update() override{
      if(this->animated){
        this->srcRect[this->currentAction].x = this->srcRect[this->currentAction].w * ((SDL_GetTicks()/this->speed) % this->numberOfFrame);
      }

      this->transform->height = this->srcRect[this->currentAction].h * this->transform->scale;
      this->transform->width = this->srcRect[this->currentAction].w * this->transform->scale;

      this->destRect.w =  this->srcRect[this->currentAction].w * this->transform->scale;
      this->destRect.h = this->srcRect[this->currentAction].h * this->transform->scale;
      this->destRect.x = static_cast<int>(this->transform->position.x) - Game::camera.x;
      this->destRect.y = static_cast<int>(this->transform->position.y) - Game::camera.y;
    }

    void play(const int& animationName){
      this->currentAction = animations[animationName].index;
      this->speed = animations[animationName].speed;
      this->numberOfFrame = animations[animationName].numberOfFrame;
    }

    ~SpriteComponent(){
      for(auto& item : this->texture){
        SDL_DestroyTexture(item);
      }
    }

};

#endif