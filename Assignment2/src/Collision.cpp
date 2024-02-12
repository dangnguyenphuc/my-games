#include "../include/Collision.hpp"

bool Collision::AABB(const SDL_Rect& a, const SDL_Rect& b){
  if(
    a.x + a.w >= b.x &&
    b.x + b.w >= a.x &&
    a.y + a.h >= b.y &&
    b.y + b.h >= a.y
  ){
    return true;
  }
  return false;
}

bool Collision::AABB(const CollisionComponent& a, const CollisionComponent& b){
  if(a.tag == b.tag) return false;
  if(AABB(a.collider, b.collider)){
    printf("%s hit %s\n", a.tag, b.tag);
    return true;
  }
  return false;
}