#ifndef COLLISION_HPP
#define COLLISION_HPP

#pragma once
#include <SDL2/SDL.h>
#include "ECS/CollisionComponent.hpp"

// class CollisionComponent;

class Collision{
  public:
    static bool AABB(const SDL_Rect& a, const SDL_Rect& b);
    static bool AABB(const CollisionComponent& a, const CollisionComponent& b);
};

#endif