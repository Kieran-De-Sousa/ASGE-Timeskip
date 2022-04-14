#ifndef ASGEGAME_PLAYERUI_H
#define ASGEGAME_PLAYERUI_H

#include "Sprite.h"
#include <Engine/Sprite.hpp>

class PlayerUI
{
 public:
  void init();
  void update_health();
  void render();

 private:
  float p1_heatlh_val;
  float p2_health_val;

  std::unique_ptr<ASGE::Renderer> renderer;
  std::unique_ptr<Sprite> p1_health_bar;
  std::unique_ptr<Sprite> p2_health_bar;
};

#endif // ASGEGAME_PLAYERUI_H
