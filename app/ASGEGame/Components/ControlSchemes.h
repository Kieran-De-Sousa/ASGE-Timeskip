#ifndef ASGEGAME_CONTROLSCHEMES_H
#define ASGEGAME_CONTROLSCHEMES_H

/// Game Engine
#include <Engine/OGLGame.hpp>

/// Lookup table would be preferred as opposed to enums sharing same types with different values
enum KeyboardPlayerOne : int
{
  UNDEFINED = 0,
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,
  LOOK_LEFT,
  LOOK_RIGHT,
  LOOK_UP,
  LOOK_DOWN,
  SHOOT,
  TIME_TRAVEL
};
enum KeyboardPlayerTwo : int
{

};

struct ControlSchemeKeyboard
{
  ControlSchemeKeyboard()  = default;
  ~ControlSchemeKeyboard() = default;
};

#endif // ASGEGAME_CONTROLSCHEMES_H
