/// Helper
#include <cmath>

#include "Vector2.h"

void Vector2::normalise() {}

float Vector2::magnitude()
{
  return sqrt(position.x * position.x + position.y * position.y);
}