#include "PlayerUI.h"

PlayerUI::PlayerUI(ASGE::Renderer& rendererRef) : renderer(&rendererRef) {}

void PlayerUI::init()
{
  // UI initialisation
  p1_health_bar = std::make_unique<Sprite>(*renderer);
  p1_health_bar->initialiseSprite("data/sprites/3-Lives.png");
  p1_health_bar->setSpriteVariables(100, 15, 9);
  p1_health_bar->setPosition(50, 182.5);

  p2_health_bar = std::make_unique<Sprite>(*renderer);
  p2_health_bar->initialiseSprite("data/sprites/3-Lives.png");
  p2_health_bar->setSpriteVariables(100, 15, 11);
  p2_health_bar->setPosition(50, 150);

  p1_portrait = std::make_unique<Sprite>(*renderer);
  p1_portrait->initialiseSprite("data/sprites/Player1Portrait.png");
  p1_portrait->setSpriteVariables(35, 35, 9);
  p1_portrait->setPosition(12.5, 182.5);

  p2_portrait = std::make_unique<Sprite>(*renderer);
  p2_portrait->initialiseSprite("data/sprites/Player2Portrait.png");
  p2_portrait->setSpriteVariables(35, 35, 9);
  p2_portrait->setPosition(12.5, 150);
}

// Sprite stuff
ASGE::Sprite* PlayerUI::getP1HealthBar()
{
  return p1_health_bar->getSprite();
}

ASGE::Sprite* PlayerUI::getP2HealthBar()
{
  return p2_health_bar->getSprite();
}

ASGE::Sprite* PlayerUI::getP1Portrait()
{
  return p1_portrait->getSprite();
}

ASGE::Sprite* PlayerUI::getP2Portrait()
{
  return p2_portrait->getSprite();
}

// Health stuff
// might not be needed but its here for now
void PlayerUI::addHealth(int playerChoice, float amount)
{
  switch (playerChoice)
  {
    case 1:
      p1_health_val += amount;
      break;
    case 2:
      p2_health_val += amount;
      break;
    default:
      Logging::ERRORS("PLAYER CHOICE INVALID");
      break;
  }
}

void PlayerUI::removeHealth(int playerChoice, float amount)
{
  switch (playerChoice)
  {
    case 1:
      p1_health_val -= amount;
      break;
    case 2:
      p2_health_val -= amount;
      break;
    default:
      Logging::ERRORS("PLAYER CHOICE INVALID");
      break;
  }
}