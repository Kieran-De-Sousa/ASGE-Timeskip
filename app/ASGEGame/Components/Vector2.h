#ifndef ASGEGAME_VECTOR2_H
#define ASGEGAME_VECTOR2_H

/// Game Engine
#include <Engine/Point2D.hpp>

/**
 * @brief Class that provides additional helper functions to Point2D data type
 * @authors Thomas
 * @authors Kieran
 */
struct Vector2
{
  Vector2(float x, float y) : position(x, y) {}
  /**
   * @brief Default constructor
   */
  Vector2()  = default;
  ~Vector2() = default;

  ASGE::Point2D position{ 0, 0 };

  void normalise();
  float magnitude();
};

#endif // ASGEGAME_VECTOR2_H
