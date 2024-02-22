#include "../include/Logic.hpp"

bool Logic::playerTouchBall = false;
bool Logic::playerPassBall = false;

std::vector<Vector2> Logic::player1Position;
std::vector<Vector2> Logic::player2Position;

Entity* Logic::currentFootballer1 = nullptr;

Vector2 Logic::ballPosition;