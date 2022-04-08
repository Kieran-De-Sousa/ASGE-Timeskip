#ifndef ASGEGAME_PLAYER_H
#define ASGEGAME_PLAYER_H

/// Game Engine
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

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

  virtual void update() override;

  /// SETTER & GETTER FUNCTIONS
  // Player ID
  void setPlayerID(const int& id) { playerID = static_cast<PlayerID>(id); }
  [[nodiscard]] int getPlayerID() const { return static_cast<int>(playerID); }
  // Velocity
  ASGE::Point2D getVelocity();
  void setVelocity(float _x, float _y);

 protected:
  PlayerID playerID = PlayerID::UNKNOWN;
  // Timers
  Timer powerUpTimer;
  float powerUpDuration  = 20;
  ASGE::Point2D velocity = { 0, 0 };
};
#endif // ASGEGAME_PLAYER_H
