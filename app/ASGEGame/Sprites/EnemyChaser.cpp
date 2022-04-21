#include "EnemyChaser.h"

EnemyChaser::EnemyChaser(
  ASGE::Renderer& rendererRef, int health, int attack, Enemy::EnemyType enemy_type) :
  Enemy(rendererRef, health, attack, enemy_type)
{
}

void EnemyChaser::update(const ASGE::GameTime& us)
{
  Enemy::update(us);
}
void EnemyChaser::behaviour(const ASGE::GameTime& us) {}
