#ifndef ASGEGAME_CONTROLSCHEMES_H
#define ASGEGAME_CONTROLSCHEMES_H

/// Game Engine - Input Schemes
#include "Engine/Gamepad.hpp"
#include "Engine/Keys.hpp"

/**
 * @Author Kieran
 */

/// Player ID
enum class PlayerID : int
{
  UNKNOWN  = 0,
  PLAYER_1 = 1,
  PLAYER_2 = 2
};
/**
 * @brief Inherited data struct containing every input type players can use
 */
struct ControlScheme
{
 public:
  explicit ControlScheme(PlayerID playerID) {}
  virtual ~ControlScheme() = default;

  /**
   * @Brief Generate control scheme
   * @param playerID
   */
  void generateControlScheme(PlayerID playerID);

  int MOVE_LEFT   = 0;
  int MOVE_RIGHT  = 0;
  int MOVE_UP     = 0;
  int MOVE_DOWN   = 0;
  int LOOK_LEFT   = 0;
  int LOOK_RIGHT  = 0;
  int LOOK_UP     = 0;
  int LOOK_DOWN   = 0;
  int SHOOT       = 0;
  int TIME_TRAVEL = 0;

 protected:
  /// Pure virtual functions overridden by keyboard and gamepad control scheme structs
  /**
   * @brief Updates input type members to corresponding Player 1 control scheme values
   */
  virtual void generatePlayer1ControlScheme() = 0;
  /**
   * @brief Updates input type members to corresponding Player 2 control scheme values
   */
  virtual void generatePlayer2ControlScheme() = 0;
};

/**
 * @brief Data struct for creating keyboard control schemes for each player
 * @note Can be expanded to allow key rebinding through setter functions that alter
 *       the 'ControlScheme' struct public members
 */
struct ControlSchemeKeyboard : ControlScheme
{
 public:
  explicit ControlSchemeKeyboard(PlayerID playerId);
  ~ControlSchemeKeyboard() override = default;

 protected:
  void generatePlayer1ControlScheme() override;
  void generatePlayer2ControlScheme() override;
};

/**
 * @brief Data struct for generalising gamepad controls
 * @note Can be expanded for different controllers/control schemes that can be
 *       set in the games settings (either through main menu/settings screen)
 */
struct ControlSchemeGamepad : ControlScheme
{
 public:
  explicit ControlSchemeGamepad(PlayerID playerId);
  ~ControlSchemeGamepad() override = default;

 protected:
  void generatePlayer1ControlScheme() override;
  void generatePlayer2ControlScheme() override;
};

#endif // ASGEGAME_CONTROLSCHEMES_H
