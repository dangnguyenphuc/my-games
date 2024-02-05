#include "../include/GameObject.hpp"
#include "../include/TextureManager.hpp"

GameObject::GameObject(const char* spritePath, int x, int y){
  this->left = x;
  this->top = y;
  this->texture = TextureManager::loadTexture(spritePath);

  this->srcRect = {0,0,0,0};

  this->destRect.h = 128; //this->srcRect.h*3;
  this->destRect.w = 128; //this->srcRect.w*3;
  this->destRect.x = x;
  this->destRect.y = y;
}

GameObject::~GameObject(){

}

void GameObject::update(){
  this->left++;
  this->top++;

  this->destRect.x = this->left++;
  this->destRect.y = this->top++;
}

void GameObject::render(){
  switch(this->srcRect.h){
    case 0:
      SDL_RenderCopy(Game::renderer, this->texture, NULL, &destRect);
      break;
    default:
      SDL_RenderCopy(Game::renderer, this->texture, &srcRect, &destRect);
      break;
  }
}
