#include "../include/TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* filePath){
  SDL_Surface *tempSurface = IMG_Load(filePath);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect){
  SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}