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

  if(!player1->loadTexture("/data/img/mario-luigi-bordered.png"))
  {
    Logging::ERRORS("init::Failed to load mario");

    return false;
  }

  for(int i = 0; i < 4; i ++)
  {
    //animation_frames[i].x = 80 + i * 17;
    animation_frames[i].y = 1;
  }

  /// animation_index 0 is for idle state, whereas 1, 2, and 3 are for running state
  player1->srcRect()[0] = animation_frames[animation_index].x;
  player1->srcRect()[1] = animation_frames[animation_index].y;
  player1->srcRect()[2] = 16;
  player1->srcRect()[3] = 32;

  player1->xPos(10);
  player1->yPos(175);
  player1->width(16);
  player1->height(32);
  player1->setGlobalZOrder(2);
  player1->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);

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