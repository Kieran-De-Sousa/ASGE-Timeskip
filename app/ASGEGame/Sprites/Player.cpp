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

void Player::update() {}

void Player::setVelocity(float _x, float _y)
{
  velocity.x = _x;
  velocity.y = _y;
}
ASGE::Point2D Player::getVelocity()
{
  return velocity;
}