//
// Created by tpasl on 4/6/2022.
//

#ifndef ASGEGAME_BULLET_H
#define ASGEGAME_BULLET_H

/// Base Class
#include "Sprites/Entity.h"

/// Helper Classes
#include "Components/Vector2.h"

class Bullet : public Entity
{
 public:
  enum class BulletType : int
  {
    UNKNOWN = 0,
    DEFAULT = 1
  };

  explicit Bullet(ASGE::Renderer& rendererRef);
  virtual ~Bullet() override = default;

  Vector2 direction{ 0, 0 };
  float velocity = 0.0F;
};

#endif // ASGEGAME_BULLET_H
