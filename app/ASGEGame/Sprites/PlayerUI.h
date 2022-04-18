#ifndef ASGEGAME_PLAYERUI_H
#define ASGEGAME_PLAYERUI_H

#include "Sprite.h"
#include <Engine/Sprite.hpp>

class PlayerUI
{
 public:
  explicit PlayerUI(ASGE::Renderer& rendererRef);
  virtual ~PlayerUI() = default;

  void init();
  // void update_health();
  ASGE::Sprite* getP1HealthBar();
  ASGE::Sprite* getP2HealthBar();

 private:
  // joey UI stuff
  float p1_health_val = 100;
  float p2_health_val = 100;
  std::unique_ptr<Sprite> p1_health_bar;
  std::unique_ptr<Sprite> p2_health_bar;

  // renderer
  std::unique_ptr<ASGE::Renderer> renderer;
};

#endif // ASGEGAME_PLAYERUI_H
