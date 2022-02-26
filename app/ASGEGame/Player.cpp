#include "Player.h"

/// Constructor w/Param
Player::Player(ASGE::Renderer& rendererRef, int id) : Entity(rendererRef), playerID(id) {}
/// Default Constructor
Player::Player(ASGE::Renderer& rendererRef) : Entity(rendererRef) {}
Player::~Player() {}

/// SETTER & GETTER FUNCTIONS
// Player ID
void Player::setPlayerID(int id)
{
  playerID = id;
}
int Player::getPlayerID() const
{
  return playerID;
}
