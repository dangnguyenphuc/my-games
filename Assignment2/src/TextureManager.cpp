#include "../include/TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* filePath, SDL_Renderer* renderer){
  SDL_Surface *tempSurface = IMG_Load(filePath);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return texture;
}