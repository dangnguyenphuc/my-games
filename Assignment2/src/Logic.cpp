#include "../include/Logic.hpp"

bool Logic::playerTouchBall = false;
bool Logic::playerPassBall = false;

std::vector<Vector2> Logic::player1Position;
std::vector<Vector2> Logic::player2Position;

Entity* Logic::currentFootballer1 = nullptr;
Entity* Logic::currentFootballer2 = nullptr;

Vector2 Logic::ballPosition;

int Logic::player1Score = 0;
int Logic::player2Score = 0;
int Logic::ballState = NONE;

std::vector<SDL_Rect> Logic::zones{
  {0          , 0               , ZONE_WIDTH  , ZONE_HEIGHT+1},
  {ZONE_WIDTH , 0               , ZONE_WIDTH  , ZONE_HEIGHT+1},
  {0          , ZONE_HEIGHT+1   , ZONE_WIDTH  , ZONE_HEIGHT-1},
  {ZONE_WIDTH , ZONE_HEIGHT+1   , ZONE_WIDTH  , ZONE_HEIGHT-1},
  {0          , 2*ZONE_HEIGHT+1 , ZONE_WIDTH  , ZONE_HEIGHT+1},
  {ZONE_WIDTH , 2*ZONE_HEIGHT+1 , ZONE_WIDTH  , ZONE_HEIGHT+1}
};
/* Zone
------ ------
|  1  |  2  |
------ ------
|  3  |  4  |
------ ------
|  5  |  6  |
------ ------
*/

bool Logic::checkBallInZone(const int& index){
  if( ballPosition.x >= zones[index].x &&
      ballPosition.y >= zones[index].y &&
      ballPosition.x < zones[index].x + zones[index].w &&
      ballPosition.y < zones[index].y + zones[index].h)
  {
    return true;
  }
  return false;
}