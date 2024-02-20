#include "../include/Map.hpp"
#include "Game.hpp"

Map::Map(){
}

Map::~Map(){
}

void Map::loadMap(int arr[MAP_HEIGHT][MAP_WIDTH]){
  for(int i = 0; i < MAP_HEIGHT; i+=1){
    for(int j = 0; j < MAP_WIDTH; j+=1){
      switch(arr[i][j]){

         case 0:
          Game::addTile(GRASS_TILE_WIDTH_HEIGHT_2_DRAW*j, GRASS_TILE_WIDTH_HEIGHT_2_DRAW*i, 0, 4.0f);
          break;

         default:
          break;
      }
    }
  }
}