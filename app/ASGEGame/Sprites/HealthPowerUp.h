#ifndef ASGEGAME_PLAYERUI_H
#define ASGEGAME_PLAYERUI_H

#include "Sprite.h"
#include <Engine/Sprite.hpp>

class HealthPowerUp
{
 public:
  // initialisation stuff
  explicit HealthPowerUp(ASGE::Renderer& rendererRef);
  virtual ~HealthPowerUp() = default;

  void init();

  // sprite stuff
  ASGE::Sprite* getHealthPowerUp();

  // health stuff
  void addHealth(int playerChoice);

  void updateHealth();

 private:
  std::unique_ptr<Sprite> pHealthPowerUp;

  // renderer
  std::unique_ptr<ASGE::Renderer> renderer;
};

#endif // ASGEGAME_HEALTHPOWERUP_H
