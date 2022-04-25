#include "Enemy.h"

void Enemy::update(const ASGE::GameTime& us)
{
  if (enemyType == EnemyType::PASSIVE)
  {
    if (directionR)
    {
      sprite->setFlipFlags(ASGE::Sprite::NORMAL);
    }
    if (!directionR)
    {
      sprite->setFlipFlags(ASGE::Sprite::FLIP_X);
    }
    if (directionR)
    {
      sprite->xPos(sprite->xPos() + p_speed);
    }
    if (sprite->xPos() > pointB)
    {
      directionR = false;
    }
    if (!directionR)
    {
      sprite->xPos(sprite->xPos() - p_speed);
    }
    if (sprite->xPos() < pointA)
    {
      directionR = true;
    }
  }
  if (enemyType == EnemyType::CHASER)
  {
    if (active)
    {
      sprite->xPos(sprite->xPos() - 3);
    }
  }
  if (enemyType == EnemyType::RANGED)
  {
    if (active)
    {
      shoot();
    }
  }
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
Enemy::Enemy(
  ASGE::Renderer& rendererRef1, int health, int attack, Enemy::EnemyType enemy_type,
  float patrolPoint1, float patrolPoint2) :
  Entity(rendererRef1)
{
  enemyType = enemy_type;
  pointA    = patrolPoint1;
  pointB    = patrolPoint2;
}
Enemy::Enemy(ASGE::Renderer& rendererRef) : Entity(rendererRef) {}

void Enemy::updateAnimations(const ASGE::GameTime& us)
{
  animation_timer += static_cast<float>(us.deltaInSecs());

  if (animation_timer > ANIMATION_FRAME_RATE)
  {
    // player1
    switch (enemyType)
    {
      case EnemyType::PASSIVE:
        animation_index += 1;
        if (animation_index > 3)
          animation_index = 0;
        break;
      case EnemyType::UNDEFINED:
        break;
      case EnemyType::CHASER:
        break;
      case EnemyType::RANGED:
        break;
    }
    // gets the frame according to the animation index
    sprite->srcRect()[0] = static_cast<float>(animation_index) * 16;
    animation_timer      = 0.0f;
  }
}
void Enemy::shoot() {}
