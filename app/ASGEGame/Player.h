#ifndef ASGEGAME_PLAYER_H
#define ASGEGAME_PLAYER_H

/// Game Engine
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

/// Base Class
#include "Entity.h"

/// Helper Classes
#include "Timer.h"

/**
 * @brief Player class shared for both players
 * @author Kieran
 */
class Player : public Entity
{
 public:
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

  virtual void update() override = 0;

  /// SETTER & GETTER FUNCTIONS
  // Player ID
  void setPlayerID(const int& id) { playerID = id; };
  [[nodiscard]] int getPlayerID() const { return playerID; };

 protected:
  // ID
  int playerID = 0;
  // Timers
  Timer powerUpTimer;
  float powerUpDuration = 20;
};
#endif // ASGEGAME_PLAYER_H
