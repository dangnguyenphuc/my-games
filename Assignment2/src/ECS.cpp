#include "../include/ECS/ECS.hpp"

void Entity::addGroup(Group group){
  this->groupBitSet[group] = true;
  this->manager.addToGroup(this, group);
}