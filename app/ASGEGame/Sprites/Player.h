#ifndef ASGEGAME_PLAYER_H
#define ASGEGAME_PLAYER_H

/// Game Engine
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

/// Data Storage
#include <map>
#include <utility>

/// Base Class
#include "Entity.h"

/// Helper Classes
#include "Bullet.h"
#include "Components/ControlSchemes.h"
#include "Components/Timer.h"

/**
 * @brief Player class shared for both players
 * @authors Kieran
 * @authors Tom
 * @authors Asli
 */
class Player : public Entity
{
 public:
  enum class PlayerState : int
  {
    IDLE    = 0,
    RUNNING = 1,
    JUMPING = 2
  };
  /**
   * @brief Constructor w/Param
   * @details Use when initialisation variables are required in instantiation,
   * @param rendererRef Required for all objects using ASGE Sprites
   * @param id Player ID (Player 1 = 1 | Player 2 = 2 | etc.)
   */
  explicit Player(ASGE::Renderer& rendererRef, int id);
  /**
   * @brief Default constructor
   * @details Use when player ID isn't required during instantiation
   * @param rendererRef
   * @note Possibly unneeded, however the option is presented
   */
  explicit Player(ASGE::Renderer& rendererRef);
  ~Player() override = default;

  virtual void update(const ASGE::GameTime& us) override;

  void updateKeymap(const std::map<int, bool>& key_state) { keymap = key_state; }
  void updateGamepad(const ASGE::GamePadData& gamepad_state) { gamepad = gamepad_state; }

  /// SETTER & GETTER FUNCTIONS
  // Player ID
  void setPlayerID(const int& id) { playerID = static_cast<PlayerID>(id); }
  [[nodiscard]] PlayerID getPlayerID() const { return playerID; }
  // Grounded
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
  void setVelocity(const float& _x, const float& _y);
  [[nodiscard]] ASGE::Point2D getVelocity() const;
  // Jump Speed
  [[nodiscard]] float getJumpSpeed() const { return j_s; }
  // Bullets
  [[nodiscard]] const std::vector<std::unique_ptr<Bullet>>& getBullets() const { return bullets; }
  [[nodiscard]] int getCurrentBullet() const { return currentBullet; }

 protected:
  /// @note Methods
  void updateAnimations(const ASGE::GameTime& us);

  /// @note Members
  PlayerID playerID = PlayerID::UNKNOWN;
  /// Inputs
  // Keyboard
  std::map<int, bool> keymap{};
  ControlSchemeKeyboard keyboard;
  // Controller
  ASGE::GamePadData gamepad = ASGE::GamePadData(0, nullptr, nullptr, nullptr);
  ControlSchemeGamepad controller;
  /// Movement
  // Walking
  const float MOVEMENT_SPEED = 5;
  // Jumping
  const float JUMP_HEIGHT = 80;
  bool gravity            = true;
  bool isGrounded         = false;
  bool isJumping          = false;
  bool isJumpPeaked       = false;
  float newPos            = 0;
  // Position
  float j_s = 0;
  // Position
  float gravity_f        = 0;
  ASGE::Point2D velocity = { 0, 0 };
  /// Bullets
  std::vector<std::unique_ptr<Bullet>> bullets;
  const int DEFAULT_MAG_SIZE = 30;
  int magSize                = DEFAULT_MAG_SIZE;
  int currentBullet          = 0;
  /// Timers
  Timer powerUpTimer;
  float powerUpDuration = 20;

  /// Animation
  // ObjRect animation_frames[5];
  int animation_index              = 0;
  const float ANIMATION_FRAME_RATE = 0.1f;
  float animation_timer            = 0.0f;

  PlayerState player1 = PlayerState::IDLE;
  PlayerState player2 = PlayerState::IDLE;
};
#endif // ASGEGAME_PLAYER_H
