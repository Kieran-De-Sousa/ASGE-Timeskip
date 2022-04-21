#include "Enemy.h"

Enemy::Enemy(
  ASGE::Renderer& rendererRef, int health = 0, int attack = 0,
  EnemyType enemy_type = EnemyType::UNDEFINED) :
  Entity(rendererRef, health, attack),
  enemyType(enemy_type)
{
}