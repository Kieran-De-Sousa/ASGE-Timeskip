#ifndef ASGEGAME_PLAYERUI_H
#define ASGEGAME_PLAYERUI_H

#include "Sprite.h"
#include <Engine/Sprite.hpp>

class PlayerUI
{
 public:
  // initialisation stuff
  explicit PlayerUI(ASGE::Renderer& rendererRef);
  virtual ~PlayerUI() = default;

  void init();

  // sprite stuff
  ASGE::Sprite* getP1HealthBar();
  ASGE::Sprite* getP2HealthBar();
  ASGE::Sprite* getP1Portrait();
  ASGE::Sprite* getP2Portrait();

  // health stuff
  void removeHealth(int playerChoice, float amount);
  void addHealth(int playerChoice, float amount);

  // Position stuff
  // Nothing here yet.

 private:
  // random vars
  float p1_health_val = 100;
  float p2_health_val = 100;
  std::unique_ptr<Sprite> p1_health_bar;
  std::unique_ptr<Sprite> p2_health_bar;
  std::unique_ptr<Sprite> p1_portrait;
  std::unique_ptr<Sprite> p2_portrait;

  // renderer
  std::unique_ptr<ASGE::Renderer> renderer;
};

#endif // ASGEGAME_PLAYERUI_H
