#include "../include/TextureManager.hpp"


SDL_Texture* TextureManager::loadTexture(const char* filePath){
  SDL_Surface* tempSurface = IMG_Load(filePath);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return texture;
}

SDL_Texture* TextureManager::renderText(const char* s, const SDL_Color& color, const int& fontStyle){
  TTF_SetFontStyle(Game::font, fontStyle);
  SDL_Surface* tempSurface = TTF_RenderText_Solid(Game::font, s, color);
  if(!tempSurface)
  {
    printf("Failed to create text surface\n");
    Game::isRunning = false;
    return nullptr;
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  if(!texture)
  {
    printf("Failed to create text texture\n");
    Game::isRunning = false;
    return nullptr;
  }
  // printf("%s being rendered\n", s);
  SDL_FreeSurface(tempSurface);
  return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, const float& rotateDegree){
  SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect, rotateDegree, NULL, flip);
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