#include "../include/Logic.hpp"

bool Logic::playerTouchBall = false;
bool Logic::playerPassBall = false;

std::vector<Vector2> Logic::player1Position;
std::vector<Vector2> Logic::player2Position;

Entity* Logic::currentFootballer1 = nullptr;

Vector2 Logic::ballPosition;

int Logic::player1Score = 0;
int Logic::player2Score = 0;
int Logic::scoreState = NONE;

SDL_Rect Logic::zone1 = {0          , 0               , ZONE_WIDTH  , ZONE_HEIGHT+1};
SDL_Rect Logic::zone2 = {ZONE_WIDTH , 0               , ZONE_WIDTH  , ZONE_HEIGHT+1};
SDL_Rect Logic::zone3 = {0          , ZONE_HEIGHT+1   , ZONE_WIDTH  , ZONE_HEIGHT-1};
SDL_Rect Logic::zone4 = {ZONE_WIDTH , ZONE_HEIGHT+1   , ZONE_WIDTH  , ZONE_HEIGHT-1};
SDL_Rect Logic::zone5 = {0          , 2*ZONE_HEIGHT+1 , ZONE_WIDTH  , ZONE_HEIGHT+1};
SDL_Rect Logic::zone6 = {ZONE_WIDTH , 2*ZONE_HEIGHT+1 , ZONE_WIDTH  , ZONE_HEIGHT+1};

/* Zone
------ ------
|  1  |  2  |
------ ------
|  3  |  4  |
------ ------
|  5  |  6  |
------ ------
*/