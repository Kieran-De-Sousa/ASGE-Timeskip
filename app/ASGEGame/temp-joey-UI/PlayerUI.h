#ifndef ASGEGAME_PLAYERUI_H
#define ASGEGAME_PLAYERUI_H

// engine includes

#include <Engine/GameTime.hpp>
#include <Engine/Input.hpp> // temp include - only in so i can forcibly decrease health to test
#include <Engine/Renderer.hpp>

// other includes

#include "Sprites/Sprite.h"

// end of includes

class PlayerUI
{
  void init();
  void update(const ASGE::GameTime& gt);
  void render(const ASGE::GameTime& gt);
  void debug_test(const ASGE::SharedEventData data);

 private:
  float p1_health_val = 100;
  float p2_health_val = 100;
  std::unique_ptr<ASGE::Sprite> p1_health_bar;
  std::unique_ptr<ASGE::Sprite> p2_health_bar;

  std::unique_ptr<ASGE::Renderer> renderer;
};

#endif // ASGEGAME_PLAYERUI_H
