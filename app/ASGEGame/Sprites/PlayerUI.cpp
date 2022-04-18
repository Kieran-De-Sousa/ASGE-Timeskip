#include "PlayerUI.h"

PlayerUI::PlayerUI(ASGE::Renderer& rendererRef) : renderer(&rendererRef) {}

void PlayerUI::init()
{
  // UI initialisation
  p1_health_bar = std::make_unique<Sprite>(*renderer);
  p1_health_bar->initialiseSprite("data/sprites/green.jpg");
  p1_health_bar->setSpriteVariables(p1_health_val, 10, 11);
  p1_health_bar->setPosition(10, 150);

  p2_health_bar = std::make_unique<Sprite>(*renderer);
  p2_health_bar->initialiseSprite("data/sprites/green.jpg");
  p2_health_bar->setSpriteVariables(p2_health_val, 10, 11);
  p2_health_bar->setPosition(10, 550);
}

ASGE::Sprite* PlayerUI::getP1HealthBar()
{
  return p1_health_bar->getSprite();
}

ASGE::Sprite* PlayerUI::getP2HealthBar()
{
  return p2_health_bar->getSprite();
}