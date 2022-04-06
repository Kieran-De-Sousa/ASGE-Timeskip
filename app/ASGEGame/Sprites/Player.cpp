#include "Player.h"
#include <Engine/Input.hpp>

/// Constructor w/Param
Player::Player(ASGE::Renderer& rendererRef, int id) :
  Entity(rendererRef), playerID(static_cast<PlayerID>(id)), powerUpTimer(powerUpDuration)
{
}
/// Default Constructor
Player::Player(ASGE::Renderer& rendererRef) : Entity(rendererRef), powerUpTimer(powerUpDuration) {}

void Player::update()
{
  this->getSprite()->xPos(this->getSprite()->xPos() + 5 * velocity.x);
  this->getSprite()->yPos(this->getSprite()->yPos() + 5 * velocity.y);
}

void Player::setVelocity(float _x, float _y)
{
  velocity.x = _x;
  velocity.y = _y;
}
void Player::updatePlayer()
{
  this->getSprite()->xPos(this->getSprite()->xPos() + 5 * velocity.x);
  this->getSprite()->yPos(this->getSprite()->yPos() + 5 * velocity.y);
}
ASGE::Point2D Player::getVelocity()
{
  return velocity;
}