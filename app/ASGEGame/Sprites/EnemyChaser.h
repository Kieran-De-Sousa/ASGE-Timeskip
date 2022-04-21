#ifndef ASGEGAME_ENEMYCHASER_H
#define ASGEGAME_ENEMYCHASER_H

/// Base Class
#include "Enemy.h"

class EnemyChaser : public Enemy
{
 public:
  EnemyChaser(ASGE::Renderer& rendererRef, int health, int attack, EnemyType enemy_type);
  virtual ~EnemyChaser() override = default;

  void update(const ASGE::GameTime& us) override;
  void behaviour(const ASGE::GameTime& us) override;

 protected:
};

#endif // ASGEGAME_ENEMYCHASER_H
