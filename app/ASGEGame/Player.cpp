#include "Player.h"

/// Constructor w/Param
Player::Player(ASGE::Renderer& rendererRef, int id) :
  Entity(rendererRef), playerID(id), powerUpTimer(powerUpDuration)
{
}
/// Default Constructor
Player::Player(ASGE::Renderer& rendererRef) : Entity(rendererRef), powerUpTimer(powerUpDuration) {}