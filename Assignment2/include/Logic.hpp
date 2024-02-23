#ifndef LOGIC_HPP
#define LOGIC_HPP

#pragma once
#include <vector>
#include "Vector2.hpp"
#include <SDL2/SDL.h>
#include "config.hpp"

#define NONE              0
#define PLAYER1_SCORED    1
#define PLAYER2_SCORED    2

class Entity;

class Logic{
  public:
    static Entity* currentFootballer1;
    // static Entity* currentFootballer2;
    static bool playerTouchBall;
    static bool playerPassBall;

    static int player1Score;
    static int player2Score;

    static int scoreState;

    static bool ballTeamId;

    static std::vector<Vector2> player1Position;
    static std::vector<Vector2> player2Position;
    static Vector2 ballPosition;

    static SDL_Rect zone1;
    static SDL_Rect zone2;
    static SDL_Rect zone3;
    static SDL_Rect zone4;
    static SDL_Rect zone5;
    static SDL_Rect zone6;
};

#endif