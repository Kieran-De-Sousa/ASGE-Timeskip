#include "Enemy.h"

Enemy::Enemy(ASGE::Renderer& rendererRef, int health, int attack, Enemy::EnemyType enemy_type) :
  Entity(rendererRef), enemyType(enemy_type)
{
  type = GameComponent::ComponentType::ENEMY;
}

Enemy::Enemy(ASGE::Renderer& rendererRef) : Entity(rendererRef)
{
  type = GameComponent::ComponentType::ENEMY;
}