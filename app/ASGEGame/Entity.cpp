#include "Entity.h"

/// Constructor w/Param
Entity::Entity(ASGE::Renderer& rendererRef, int health, int attack) :
  Sprite(rendererRef), entityHealth(health), entityAttack(attack)
{
}
/// Default Constructor
Entity::Entity(ASGE::Renderer& rendererRef) : Sprite(rendererRef) {}
Entity::~Entity() {}

bool Entity::entityPlayer()
{
  player1 = renderer->createUniqueSprite();

  if(!player1->loadTexture("/data/sprites/player1.png"))
  {
    Logging::ERRORS("init::Failed to load player1");

    return false;
  }


  return true;
}


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
/*
// get state
int Entity::getState()
{
  return entityState;
}
//set state
void Entity::setState(int state)
{
  entityState = state;
}
 */
// Attack
void Entity::setAttack(int attack)
{
  entityAttack = attack;
}
int Entity::getAttack() const
{
  return entityAttack;
}

void Entity::update(const ASGE::GameTime& us)
{
  ///Animation
  /*
  if (entityState == RUNNING)
  {
    animation_timer += static_cast<float>(us.deltaInSecs());

    if (animation_timer > ANIMATION_FRAME_RATE)
    {
      animation_index ++;

      if(animation_index == 4) animation_index = 1;

      animation_timer = 0.0f;
    }
  }
  else
  {
    animation_index = 0;
  }
  player1->srcRect()[0] = animation_frames[animation_index].x;
  player1->srcRect()[1] = animation_frames[animation_index].y;
   */
}