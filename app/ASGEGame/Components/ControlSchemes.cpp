#include "ControlSchemes.h"

//// Control Schemes - Base struct
/// Protected setter function
void ControlScheme::generateControlScheme(PlayerID playerID)
{
  switch (playerID)
  {
    case PlayerID::PLAYER_1:
      generatePlayer1ControlScheme();
      break;
    case PlayerID::PLAYER_2:
      generatePlayer2ControlScheme();
      break;
    case PlayerID::UNKNOWN:
      break;
  }
}

//// Control Schemes - Keyboard
ControlSchemeKeyboard::ControlSchemeKeyboard(PlayerID playerId) : ControlScheme(playerId)
{
  generateControlScheme(playerId);
}
/// Player 1
void ControlSchemeKeyboard::generatePlayer1ControlScheme()
{
  MOVE_LEFT   = ASGE::KEYS::KEY_A;
  MOVE_RIGHT  = ASGE::KEYS::KEY_D;
  MOVE_UP     = ASGE::KEYS::KEY_W;
  MOVE_DOWN   = ASGE::KEYS::KEY_S;
  LOOK_LEFT   = ASGE::KEYS::KEY_L;
  LOOK_RIGHT  = ASGE::KEYS::KEY_J;
  LOOK_UP     = ASGE::KEYS::KEY_I;
  LOOK_DOWN   = ASGE::KEYS::KEY_K;
  SHOOT       = ASGE::KEYS::KEY_R;
  TIME_TRAVEL = ASGE::KEYS::KEY_Q;
}
/// Player 2
void ControlSchemeKeyboard::generatePlayer2ControlScheme()
{
  MOVE_LEFT   = ASGE::KEYS::KEY_LEFT;
  MOVE_RIGHT  = ASGE::KEYS::KEY_RIGHT;
  MOVE_UP     = ASGE::KEYS::KEY_UP;
  MOVE_DOWN   = ASGE::KEYS::KEY_DOWN;
  LOOK_LEFT   = ASGE::KEYS::KEY_C;
  LOOK_RIGHT  = ASGE::KEYS::KEY_B;
  LOOK_UP     = ASGE::KEYS::KEY_F;
  LOOK_DOWN   = ASGE::KEYS::KEY_V;
  SHOOT       = ASGE::KEYS::KEY_SLASH;
  TIME_TRAVEL = ASGE::KEYS::KEY_ENTER;
}

//// Control Schemes - Gamepad
ControlSchemeGamepad::ControlSchemeGamepad(PlayerID playerId) : ControlScheme(playerId)
{
  generateControlScheme(playerId);
}
/// Player 1
void ControlSchemeGamepad::generatePlayer1ControlScheme()
{
  MOVE_LEFT   = ASGE::GAMEPAD::BUTTON_DPAD_LEFT;
  MOVE_RIGHT  = ASGE::GAMEPAD::BUTTON_DPAD_RIGHT;
  MOVE_UP     = ASGE::GAMEPAD::BUTTON_DPAD_UP;
  MOVE_DOWN   = ASGE::GAMEPAD::BUTTON_DPAD_DOWN;
  LOOK_LEFT   = ASGE::GAMEPAD::BUTTON_X;
  LOOK_RIGHT  = ASGE::GAMEPAD::BUTTON_B;
  LOOK_UP     = ASGE::GAMEPAD::BUTTON_Y;
  LOOK_DOWN   = ASGE::GAMEPAD::BUTTON_A;
  SHOOT       = ASGE::GAMEPAD::BUTTON_RIGHT_BUMPER;
  TIME_TRAVEL = ASGE::GAMEPAD::BUTTON_LEFT_BUMPER;
}
/// Player 2
void ControlSchemeGamepad::generatePlayer2ControlScheme()
{
  MOVE_LEFT   = ASGE::GAMEPAD::BUTTON_DPAD_LEFT;
  MOVE_RIGHT  = ASGE::GAMEPAD::BUTTON_DPAD_RIGHT;
  MOVE_UP     = ASGE::GAMEPAD::BUTTON_DPAD_UP;
  MOVE_DOWN   = ASGE::GAMEPAD::BUTTON_DPAD_DOWN;
  LOOK_LEFT   = ASGE::GAMEPAD::BUTTON_X;
  LOOK_RIGHT  = ASGE::GAMEPAD::BUTTON_B;
  LOOK_UP     = ASGE::GAMEPAD::BUTTON_Y;
  LOOK_DOWN   = ASGE::GAMEPAD::BUTTON_A;
  SHOOT       = ASGE::GAMEPAD::BUTTON_RIGHT_BUMPER;
  TIME_TRAVEL = ASGE::GAMEPAD::BUTTON_LEFT_BUMPER;
}