#include "Player.h"
#include <Engine/Input.hpp>

/// Constructor w/Param
Player::Player(ASGE::Renderer& rendererRef, int id) :
  Entity(rendererRef), playerID(static_cast<PlayerID>(id)), keyboard(static_cast<PlayerID>(id)),
  controller(static_cast<PlayerID>(id))
{
  type = ComponentType::PLAYER;
  createBullets();
}
/// Default Constructor
Player::Player(ASGE::Renderer& rendererRef) :
  Entity(rendererRef), keyboard(PlayerID::UNKNOWN), controller(PlayerID::UNKNOWN)
{
  type = ComponentType::PLAYER;
  createBullets();
}

void Player::update(const ASGE::GameTime& us)
{
  /// Update player animations & state machine
  updateAnimations(us);
  /// Update bullet positions
  updateBullets(us);

  /// Jump
  if ((keymap[keyboard.MOVE_UP] || (gamepad.buttons[controller.MOVE_UP] != 0u)) && isGrounded)
  {
    newPos     = sprite->yPos() - JUMP_HEIGHT;
    j_s        = -10.0f;
    isJumping  = true;
    isGrounded = false;
  }
  /// Move left
  if (keymap[keyboard.MOVE_LEFT] || (gamepad.buttons[controller.MOVE_LEFT] != 0u))
  {
    sprite->xPos(sprite->xPos() - 5);
    sprite->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);

    if (isGrounded)
    {
      player1 = PlayerState::RUNNING;
    }
  }
  /// Move right
  if (keymap[keyboard.MOVE_RIGHT] || (gamepad.buttons[controller.MOVE_RIGHT] != 0u))
  {
    sprite->xPos(sprite->xPos() + 5);
    sprite->setFlipFlags(ASGE::Sprite::FlipFlags::NORMAL);

    if (isGrounded)
    {
      player1 = PlayerState::RUNNING;
    }
  }

  /// Shooting
  if (keymap[keyboard.SHOOT] || (gamepad.buttons[controller.SHOOT] != 0u))
  {
    shootBullet(us);
  }

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

void Player::createBullets()
{
  /// Bullets
  for (unsigned int i = 0; i < MAXIMUM_BULLETS; ++i)
  {
    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(*renderer);
    bullet->initialiseSprite("data/sprites/bulletSprite.png");
    bullet->setSpriteVariables(8, 8, 6);
    bullet->setPosition(-200, -200);
    bullets.emplace_back(std::move(bullet));
  }
}

void Player::updateAnimations(const ASGE::GameTime& us)
{
  animation_timer += static_cast<float>(us.deltaInSecs());

  if (animation_timer > ANIMATION_FRAME_RATE)
  {
    // player1
    switch (player1)
    {
      case PlayerState::RUNNING:
        animation_index += 1;
        if (animation_index > 3)
          animation_index = 0;
        break;
      case PlayerState::IDLE:
        animation_index = 4;
        break;
      case PlayerState::JUMPING:
        animation_index = 5;
        break;
    }
    // gets the frame according to the animation index
    sprite->srcRect()[0] = static_cast<float>(animation_index) * 32;
    animation_timer      = 0.0f;
  }
  if (isGrounded)
  {
    player1 = PlayerState::IDLE;
  }
  if (!isGrounded)
  {
    player1 = PlayerState::JUMPING;
  }
}

void Player::updateBullets(const ASGE::GameTime& us)
{
  for (auto& bullet : bullets)
  {
    bullet->setPosition(
      bullet->getSprite()->xPos() + DEFAULT_BULLET_VELOCITY * bullet->direction.position.x,
      bullet->getSprite()->yPos() + DEFAULT_BULLET_VELOCITY * bullet->direction.position.y);
  }
}

void Player::shootBullet(const ASGE::GameTime& us)
{
  if (sprite->flipFlags() == ASGE::Sprite::FLIP_X)
  {
    bullets[bulletCount]->setPosition(
      sprite->xPos() - bullets[bulletCount]->getSprite()->width(),
      sprite->yPos() + sprite->height() / 2 - bullets[bulletCount]->getSprite()->height());
    bullets[bulletCount]->direction.position.x = -1;
  }
  else if (sprite->flipFlags() == ASGE::Sprite::NORMAL)
  {
    bullets[bulletCount]->setPosition(
      sprite->xPos() + bullets[bulletCount]->getSprite()->width(),
      sprite->yPos() + sprite->height() / 2 - bullets[bulletCount]->getSprite()->height());
    bullets[bulletCount]->direction.position.x = 1;
  }
  bulletCount++;
  if (bulletCount > magSize)
  {
    bulletCount = 0;
  }
}