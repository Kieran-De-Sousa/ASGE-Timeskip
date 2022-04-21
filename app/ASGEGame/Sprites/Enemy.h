#ifndef ASGEGAME_ENEMY_H
#define ASGEGAME_ENEMY_H

/// Game Engine
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

/// Base Class
#include "Entity.h"

class Enemy : public Entity
{
 public:
  enum class EnemyType : int
  {
    UNDEFINED = 0,
    PASSIVE   = 1,
    CHASER    = 2,
    RANGED    = 3
  };

  Enemy(ASGE::Renderer& rendererRef, int health, int attack, EnemyType enemy_type);
  virtual ~Enemy() override = default;

  virtual void update(const ASGE::GameTime& us) override {}
  virtual void behaviour(const ASGE::GameTime& us) = 0;

 protected:
  EnemyType enemyType = EnemyType::UNDEFINED;
};

#endif // ASGEGAME_ENEMY_H
