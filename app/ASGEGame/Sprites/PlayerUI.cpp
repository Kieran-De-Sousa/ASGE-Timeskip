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
void PlayerUI::addHealth(int playerChoice)
{
  switch (playerChoice)
  {
    case 1:
      if (p1_health_val <= 2)
      {
        p1_health_val += 1;
      }
      else
      {
        Logging::ERRORS("UI Error 'Overheal' - Cannot have > 3 lives");
      }
      break;
    case 2:
      if (p2_health_val <= 2)
      {
        p2_health_val += 1;
      }
      else
      {
        Logging::ERRORS("UI Error 'Overheal' - Cannot have > 3 lives");
      }
      break;
    default:
      Logging::ERRORS("UI Error 'Mistaken Identity' - No player with that number exists");
      break;
  }
}

void PlayerUI::removeHealth(int playerChoice)
{
  switch (playerChoice)
  {
    case 1:
      if (p1_health_val >= 1)
      {
        p1_health_val -= 1;
      }
      else
      {
        Logging::ERRORS("UI Error 'Already Dead' - Cannot have < 0 lives");
      }
      break;
    case 2:
      if (p2_health_val >= 1)
      {
        p2_health_val -= 1;
      }
      else
      {
        Logging::ERRORS("UI Error 'Already Dead' - Cannot have < 0 lives");
      }
      break;
    default:
      Logging::ERRORS("UI Error 'Mistaken Identity' - No player with that number exists");
      break;
  }
}

void PlayerUI::updateLives()
{
  switch (p1_health_val)
  {
    case 3:
      p1_health_bar->setSprite("data/sprites/3-Lives.png");
      p1_health_bar->setSpriteVariables(100, 15, 9);
      break;

    case 2:
      p1_health_bar->setSprite("data/sprites/2-Lives.png");
      p1_health_bar->setSpriteVariables(100, 15, 9);
      break;

    case 1:
      p1_health_bar->setSprite("data/sprites/1-Life.png");
      p1_health_bar->setSpriteVariables(100, 15, 9);
      break;

    case 0:
      p1_health_bar->setSprite("data/sprites/No-Life.png");
      p1_health_bar->setSpriteVariables(100, 15, 9);
      break;

    default:
      Logging::ERRORS("UI Error 'Rock-Bottom' - Decreasing health more would make it negative.");
      break;
  }

  switch (p2_health_val)
  {
    case 3:
      p2_health_bar->setSprite("data/sprites/3-Lives.png");
      p2_health_bar->setSpriteVariables(100, 15, 11);
      break;

    case 2:
      p2_health_bar->setSprite("data/sprites/2-Lives.png");
      p2_health_bar->setSpriteVariables(100, 15, 11);
      break;

    case 1:
      p2_health_bar->setSprite("data/sprites/1-Life.png");
      p2_health_bar->setSpriteVariables(100, 15, 11);
      break;

    case 0:
      p2_health_bar->setSprite("data/sprites/No-Life.png");
      p2_health_bar->setSpriteVariables(100, 15, 11);
      break;

    default:
      Logging::ERRORS("UI Error 'Rock-Bottom' - Decreasing health more would make it negative.");
      break;
  }
}