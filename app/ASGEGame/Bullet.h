#ifndef ASGEGAME_BULLET_H
#define ASGEGAME_BULLET_H

/// Game Engine
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

/// Base Class
#include "Sprite.h"

class Bullet : public Sprite
{
 public:
  explicit Bullet(ASGE::Renderer& rendererRef) : Sprite(rendererRef){};
  virtual ~Bullet() override = default;

 protected:
 private:
  int damage = 0;
};

#endif // ASGEGAME_BULLET_H
