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

  explicit Enemy(ASGE::Renderer& rendererRef, int health, int attack, Enemy::EnemyType enemy_type);
  explicit Enemy(ASGE::Renderer& rendererRef);
  virtual ~Enemy() override = default;

  virtual void behaviour(const ASGE::GameTime& us)        = 0;
  virtual void updateAnimations(const ASGE::GameTime& us) = 0;

  void setGrounded(const bool& grounded) { isGrounded = grounded; }
  [[nodiscard]] bool getGrounded() const { return isGrounded; }
  // Jump
  void setJumping(const bool& jumping) { isJumping = jumping; }
  [[nodiscard]] bool getJumping() const { return isJumping; }
  void setJumpSpeed(const float& value) { j_s = value; }
  // Jump Peaked
  void setJumpPeaked(const bool& peaked) { isJumpPeaked = peaked; }
  [[nodiscard]] bool getJumpPeaked() const { return isJumpPeaked; }

  void setTotalAnimFrames(const int& frames) { total_frames = frames; }

 protected:
  EnemyType enemyType = EnemyType::UNDEFINED;
  /// Movement
  bool directionR = true;
  float speed     = 0.0F;
  float newPos    = 0;
  /// Jumping
  float j_s         = 0;
  bool gravity      = false;
  bool isGrounded   = false;
  bool isJumping    = false;
  bool isJumpPeaked = false;

  int animation_index              = 0;
  int total_frames                 = 0;
  const float ANIMATION_FRAME_RATE = 0.1f;
  float animation_timer            = 0.0f;
};

#endif // ASGEGAME_ENEMY_H
