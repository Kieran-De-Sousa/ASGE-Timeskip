#ifndef ASGEGAME_ENEMYCHASER_H
#define ASGEGAME_ENEMYCHASER_H

/// Base Class
#include "Enemy.h"

class EnemyChaser : public Enemy
{
 public:
  EnemyChaser(ASGE::Renderer& rendererRef, int health, int attack, Enemy::EnemyType enemy);
  virtual ~EnemyChaser() override = default;

  void update(const ASGE::GameTime& us) override;
  void behaviour(const ASGE::GameTime& us) override;
  void updateAnimations(const ASGE::GameTime& us) override;

  void setActive(const bool& active) { isActive = active; }

 protected:
  bool isActive         = false;
  float detectionRadius = 50.0f;
  /// Constants
  float ENEMY_CHASER_SPEED = 2.5F;
};

#endif // ASGEGAME_ENEMYCHASER_H
