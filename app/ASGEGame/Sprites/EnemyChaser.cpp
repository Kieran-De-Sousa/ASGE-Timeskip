#include "EnemyChaser.h"

EnemyChaser::EnemyChaser(
  ASGE::Renderer& rendererRef, int health, int attack, Enemy::EnemyType enemy) :
  Enemy(rendererRef, health, attack, enemy)
{
  speed = ENEMY_CHASER_SPEED;
}

void EnemyChaser::update(const ASGE::GameTime& us)
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

void EnemyChaser::behaviour(const ASGE::GameTime& us)
{
  if (isActive)
  {
    sprite->xPos(sprite->xPos() - speed);
  }
}

void EnemyChaser::updateAnimations(const ASGE::GameTime& us)
{
  animation_timer += static_cast<float>(us.deltaInSecs());

  if (animation_timer > ANIMATION_FRAME_RATE)
  {
    animation_index += 1;
    if (animation_index > total_frames)
    {
      animation_index = 0;
    }

    // gets the frame according to the animation index
    sprite->srcRect()[0] = static_cast<float>(animation_index) * 16;
    animation_timer      = 0.0f;
  }
}
