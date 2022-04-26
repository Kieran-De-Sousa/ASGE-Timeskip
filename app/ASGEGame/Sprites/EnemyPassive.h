#ifndef ASGEGAME_ENEMYPASSIVE_H
#define ASGEGAME_ENEMYPASSIVE_H

/// Base Class
#include "Enemy.h"

class EnemyPassive : public Enemy
{
 public:
  EnemyPassive(
    ASGE::Renderer& rendererRef, int health, int attack, Enemy::EnemyType enemy, float patrolPoint1,
    float patrolPoint2);
  virtual ~EnemyPassive() override = default;

  void update(const ASGE::GameTime& us) override;
  void behaviour(const ASGE::GameTime& us) override;
  void updateAnimations(const ASGE::GameTime& us) override;

 protected:
  /// Patrol Points
  float pointA = 0;
  float pointB = 0;
  /// Constants
  float ENEMY_PASSIVE_SPEED = 1.5F;
};

#endif // ASGEGAME_ENEMYPASSIVE_H
