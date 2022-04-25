#include "HealthPowerUp.h"

HealthPowerUp::HealthPowerUp(ASGE::Renderer& rendererRef) : renderer(&rendererRef) {}

void HealthPowerUp::init()
{
  pHealthPowerUp = std::make_unique<Sprite>(*renderer);
  pHealthPowerUp->initialiseSprite("data/sprites/Heatlh.png");
  pHealthPowerUp->setSpriteVariables(100, 15, 9);
  pHealthPowerUp->setPosition(100, 240);
}
// Sprite stuff
ASGE::Sprite* HealthPowerUp::getHealthPowerUp()
{
  return pHealthPowerUp->getSprite();
}
