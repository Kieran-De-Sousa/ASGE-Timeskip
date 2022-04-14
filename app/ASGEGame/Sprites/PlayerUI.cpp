#include "PlayerUI.h"

void PlayerUI::init()
{
  // p1 health stuff
  p1_health_bar->initialiseSprite("data/sprites/green.jpg");
  p1_health_bar->setSpriteVariables(p1_heatlh_val, 10, 3);
  p1_health_bar->setPosition(10, 10);

  // p2 health stuff
  p2_health_bar->initialiseSprite("data/sprites/green.jpg");
  p2_health_bar->setSpriteVariables(p2_health_val, 10, 3);
  p2_health_bar->setPosition(10, 550);
}

void PlayerUI::update_health() {}