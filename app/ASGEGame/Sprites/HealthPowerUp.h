#ifndef ASGEGAME_HEALTHPOWERUP_H
#define ASGEGAME_HEALTHPOWERUP_H

#include "Entity.h"
#include <Engine/Sprite.hpp>

class HealthPowerUp : public Entity
{
 public:
  // initialisation
  explicit HealthPowerUp(ASGE::Renderer& rendererRef);

  // health
  void updateHealth();

 private:
};

#endif // ASGEGAME_HEALTHPOWERUP_H
