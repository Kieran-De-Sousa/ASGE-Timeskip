//
// Created by ali on 24/04/2022.
//

#ifndef ASGEGAME_HEALTHPOWERUP_H
#define ASGEGAME_HEALTHPOWERUP_H

#include "Entity.h"

class HealthPowerUp : public Sprite
{
 public:
  explicit HealthPowerUp(ASGE::Renderer& rendererRef);
  ~HealthPowerUp() override = default;

  virtual void update(const ASGE::GameTime& us) override;

 private:
};

#endif // ASGEGAME_HEALTHPOWERUP_H
