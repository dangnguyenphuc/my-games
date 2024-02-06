#include "../include/TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* filePath){
  SDL_Surface* tempSurface = IMG_Load(filePath);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip){
  SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect, NULL, NULL, flip);
}


// auto [width, height] = TextureManager::getTextureWidthHeight(TEST_TEXTURE_FILE_PATH);
std::pair<int, int> TextureManager::getTextureWidthHeight(const char* filePath){
  SDL_Texture* texture = loadTexture(filePath);

  int width, height;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);

  SDL_DestroyTexture(texture);
  return std::make_pair(width,height);
}

// auto [width, height] = TextureManager::getSpriteWidthHeight("../assets/image/Free_Assets/Footballers/Argentina/walk.png", 1 , 4);
std::pair<int, int> TextureManager::getSpriteWidthHeight(const char* filePath, int row, int col){
  auto [width, height] = getTextureWidthHeight(filePath);
  return std::make_pair(width/col,height/row);
}