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
#include "Components/Timer.h"

/**
 * @brief Player class shared for both players
 * @author Kieran
 */
class Player : public Entity
{
 public:
  /// ID
  enum class PlayerID : int
  {
    UNKNOWN  = 0,
    PLAYER_1 = 1,
    PLAYER_2 = 2
  };

  enum class PlayerState : int
  {
    IDLE = 0,
    RUNNING = 1,
    JUMPING = 2
  };

  enum class TimeTravelState : int
  {
    PRESENT = 0,
    PAST    = 1
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
  void updateGamepad(const std::map<int, ASGE::GamePadData>& gamepad_state)
  {
    gamepad = gamepad_state;
  }

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
  // Jump Peaked
  void setJumpPeaked(const bool& peaked) { isJumpPeaked = peaked; }
  [[nodiscard]] bool getJumpPeaked() const { return isJumpPeaked; }
  // Velocity
  void setVelocity(const float& _x, const float& _y);
  [[nodiscard]] ASGE::Point2D getVelocity() const;
  void setJumpSpeed(const float& jump) { j_s = jump; }


 protected:
  PlayerID playerID = PlayerID::UNKNOWN;
  /// Inputs
  std::map<int, bool> keymap{};
  std::map<int, ASGE::GamePadData> gamepad{};
  /// Movement
  // Walking
  const float MOVEMENT_SPEED = 5;
  // Jumping
  const float JUMP_HEIGHT = 128;
  bool gravity            = true;
  bool isGrounded         = false;
  bool isJumping          = false;
  bool isJumpPeaked       = false;
  float newPos            = 0;
  // Position
  float j_s              = 0;
  ASGE::Point2D velocity = { 0, 0 };
  /// Timers
  Timer powerUpTimer;
  float powerUpDuration = 20;

  /// Animation
  //ObjRect animation_frames[5];
  int animation_index              = 0;
  const float ANIMATION_FRAME_RATE = 0.1f;
  float animation_timer            = 0.0f;

  PlayerState player1 = PlayerState::IDLE;
  PlayerState player2 = PlayerState::IDLE;
};
#endif // ASGEGAME_PLAYER_H
