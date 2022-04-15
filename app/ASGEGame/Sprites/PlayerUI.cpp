#include "PlayerUI.h"

void PlayerUI::init(std::unique_ptr<Sprite> sprite, float health_val, float y_val)
{
  // UI initialisation
  sprite->initialiseSprite("data/sprites/green.jpg");
  sprite->setSpriteVariables(health_val, 10, 3);
  sprite->setPosition(10, y_val);
}