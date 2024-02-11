#ifndef MAP_H
#define MAP_H

#pragma once
#include "config.hpp"

class Map{
  public:
    Map();
    ~Map();
    static void loadMap(int arr[MAP_HEIGHT][MAP_WIDTH]);
};

#endif