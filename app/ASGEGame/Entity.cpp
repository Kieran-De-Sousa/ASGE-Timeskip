#include "Entity.h"

/// Constructor w/Param
Entity::Entity(ASGE::Renderer& rendererRef, int health, int attack) :
  Sprite(rendererRef), entityHealth(health), entityAttack(attack)
{
}
/// Default Constructor
Entity::Entity(ASGE::Renderer& rendererRef) : Sprite(rendererRef) {}
Entity::~Entity() {}

/// SETTER & GETTER FUNCTIONS
// Health
void Entity::setHealth(int health)
{
  entityHealth = health;
}
int Entity::getHealth()
{
  return entityHealth;
}
// Attack
void Entity::setAttack(int attack)
{
  entityAttack = attack;
}
int Entity::getAttack() const
{
  return entityAttack;
}
