#ifndef LOGIC_HPP
#define LOGIC_HPP

#pragma once
#include <vector>
#include "Vector2.hpp"
#include <SDL2/SDL.h>
#include "config.hpp"

// ball states
#define NONE              0
#define PLAYER1_SCORED    1
#define PLAYER2_SCORED    2
#define PLAYER1_GETBALL   3
#define PLAYER2_GETBALL   4

class Entity;

class Logic{
  public:
    static Entity* currentFootballer1;
    static Entity* currentFootballer2;

    static bool playerTouchBall;
    static bool playerPassBall;
    static bool playWithComputer;

    static int player1Score;
    static int player2Score;

    static int ballState;

    static bool ballTeamId;

    static std::vector<Vector2> player1Position;
    static std::vector<Vector2> player2Position;

    static Vector2 ballPosition;

    static std::vector<SDL_Rect> zones;

    static bool checkBallInZone(const int& index);
    static void deceleratorEntities(const float& num, Entity* entity);
};

#endif