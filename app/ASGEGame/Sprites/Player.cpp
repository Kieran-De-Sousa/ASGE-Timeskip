#include "Player.h"
#include <Engine/Input.hpp>

/// Constructor w/Param
Player::Player(ASGE::Renderer& rendererRef, int id) :
  Entity(rendererRef), playerID(static_cast<PlayerID>(id))
{
  type = ComponentType::PLAYER;
}
/// Default Constructor
Player::Player(ASGE::Renderer& rendererRef) : Entity(rendererRef)
{
  type = ComponentType::PLAYER;
}

void Player::update(const ASGE::GameTime& us)
{
  /// Jump
  if (keymap[ASGE::KEYS::KEY_W] && isGrounded)
  {
    newPos     = sprite->yPos() - JUMP_HEIGHT;
    j_s        = -10.0f;
    isJumping  = true;
    isGrounded = false;
    // gravity = false;
  }
  /// Move left
  if (keymap[ASGE::KEYS::KEY_A])
  {
    sprite->xPos(sprite->xPos() - 5);
    sprite->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);
  }
  /// Move right
  if (keymap[ASGE::KEYS::KEY_D])
  {
    sprite->xPos(sprite->xPos() + 5);
    sprite->setFlipFlags(ASGE::Sprite::FlipFlags::NORMAL);
  }
  // TODO: SHOOTING
  //  if (keymap[ASGE::KEYS::KEY_F])
  //  {
  //    if (sprite->flipFlags() == ASGE::Sprite::FLIP_X)
  //    {
  ////      bullets[bulletCount]->xPos(ship->xPos() - bullets[bulletCount]->width());
  ////      bullets[bulletCount]->yPos(ship->yPos() + ship->height() / 2 -
  /// bullets[bulletCount]->height()); /      directions[bulletCount].position.x = -1;
  //    }
  //    if (getSprite()->flipFlags() == ASGE::Sprite::NORMAL)
  //    {
  ////      bullets[bulletCount]->xPos(ship->xPos() + ship->width());
  ////      bullets[bulletCount]->yPos(
  ////        ship->yPos() + ship->height() / 2 - bullets[bulletCount]->height());
  ////      directions[bulletCount].position.x = 1;
  //    }
  ////    bulletCount++;
  ////    if (bulletCount > 25)
  ////    {
  ////      bulletCount = 0;
  ////    }

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
    gravity = true;
  }
}

void Player::setVelocity(const float& _x, const float& _y)
{
  velocity.x = _x;
  velocity.y = _y;
}
ASGE::Point2D Player::getVelocity() const
{
  return velocity;
}