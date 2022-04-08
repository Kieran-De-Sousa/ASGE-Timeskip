#include "PlayerUI.h"

void PlayerUI::init()
{
  // p1 health
  p1_health_bar = renderer->createUniqueSprite();
  p1_health_bar->loadTexture("data/sprites/health_square.png");
  p1_health_bar->xPos(10);
  p1_health_bar->yPos(20);
  p1_health_bar->width(p1_health_val);
  p1_health_bar->height(10);
  p1_health_bar->setGlobalZOrder(10);

  // p2 health
  p2_health_bar = renderer->createUniqueSprite();
  p2_health_bar->loadTexture("data/sprites/health_square.png");
  p2_health_bar->xPos(10);
  p2_health_bar->yPos(520);
  p2_health_bar->width(p2_health_val);
  p2_health_bar->height(10);
  p2_health_bar->setGlobalZOrder(10);
}

void PlayerUI::update(const ASGE::GameTime& gt) {}

void PlayerUI::render(const ASGE::GameTime& gt)
{
  renderer->render(*p1_health_bar);
  renderer->render(*p2_health_bar);
}

// TESTING STUFF BELOW

void PlayerUI::debug_test(const ASGE::SharedEventData data)
{
  const auto* key_event = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  // auto action = key_event->action;
  auto key = key_event->key;

  if (key == ASGE::KEYS::KEY_MINUS)
  {
    p1_health_val -= 10;
  }
}