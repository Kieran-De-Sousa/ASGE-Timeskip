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

  explicit Enemy(
    ASGE::Renderer& rendererRef1, int health, int attack, Enemy::EnemyType enemy_type,
    float patrolPoint1, float patrolPoint2);
  explicit Enemy(ASGE::Renderer& rendererRef);
  virtual ~Enemy() override = default;

  virtual void update(const ASGE::GameTime& us) override;
  // virtual void behaviour(const ASGE::GameTime& us) = 0;

  void setGrounded(const bool& grounded) { isGrounded = grounded; }
  [[nodiscard]] bool getGrounded() const { return isGrounded; }
  // Jump
  void setJumping(const bool& jumping) { isJumping = jumping; }
  [[nodiscard]] bool getJumping() const { return isJumping; }
  void setJumpSpeed(const float& value) { j_s = value; }
  // Jump Peaked
  void setJumpPeaked(const bool& peaked) { isJumpPeaked = peaked; }
  [[nodiscard]] bool getJumpPeaked() const { return isJumpPeaked; }
  // Velocity
  void setActive(const bool& Act) { active = Act; }

 protected:
  EnemyType enemyType = EnemyType::UNDEFINED;
  float pointA        = 0;
  float pointB        = 0;
  float p_speed       = 1.5F;
  float c_speed       = 3.0F;
  bool directionR     = true;

  bool gravity      = false;
  bool isGrounded   = false;
  bool isJumping    = false;
  bool isJumpPeaked = false;
  bool active       = false;
  float newPos      = 0;
  float j_s         = 0;

  int animation_index              = 0;
  const float ANIMATION_FRAME_RATE = 0.1f;
  float animation_timer            = 0.0f;

  void updateAnimations(const ASGE::GameTime& us);
};

#endif // ASGEGAME_ENEMY_H
