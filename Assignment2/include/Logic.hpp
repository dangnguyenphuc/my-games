#ifndef LOGIC_HPP
#define LOGIC_HPP

#pragma once
#include <vector>
#include "Vector2.hpp"

class Entity;

class Logic{
  public:
    static Entity* currentFootballer1;
    static bool playerTouchBall;
    static bool playerPassBall;

    static std::vector<Vector2> player1Position;
    static std::vector<Vector2> player2Position;
    static Vector2 ballPosition;
};

#endif