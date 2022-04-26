#include "EnemyPassive.h"

EnemyPassive::EnemyPassive(
  ASGE::Renderer& rendererRef, int health, int attack, Enemy::EnemyType enemy, float patrolPoint1,
  float patrolPoint2) :
  Enemy(rendererRef, health, attack, enemy),
  pointA(patrolPoint1), pointB(patrolPoint2)
{
  speed = ENEMY_PASSIVE_SPEED;
}

void EnemyPassive::update(const ASGE::GameTime& us)
{
  behaviour(us);
  updateAnimations(us);

  if (gravity)
  {
    j_s += 0.3f;
    if (j_s > 10.0f)
    {
      j_s = 10.0f;
    }
    sprite->yPos(sprite->yPos() + j_s);
    if (sprite->yPos() < newPos)
    {
      isJumping    = false;
      isJumpPeaked = true;
    }
  }
  if ((!isGrounded || isJumpPeaked) && !isJumping)
  {
    // gravity = true;
  }
}
void EnemyPassive::behaviour(const ASGE::GameTime& us)
{
  if (sprite->xPos() > pointB)
  {
    directionR = false;
  }
  if (sprite->xPos() < pointA)
  {
    directionR = true;
  }
  if (directionR)
  {
    sprite->setFlipFlags(ASGE::Sprite::NORMAL);
    sprite->xPos(sprite->xPos() + speed);
  }
  else if (!directionR)
  {
    sprite->setFlipFlags(ASGE::Sprite::FLIP_X);
    sprite->xPos(sprite->xPos() - speed);
  }
}

void EnemyPassive::updateAnimations(const ASGE::GameTime& us)
{
  animation_timer += static_cast<float>(us.deltaInSecs());

  if (animation_timer > ANIMATION_FRAME_RATE)
  {
    animation_index += 1;
    if (animation_index > 3)
    {
      animation_index = 0;
    }

    // gets the frame according to the animation index
    sprite->srcRect()[0] = static_cast<float>(animation_index) * 16;
    animation_timer      = 0.0f;
  }
}
