#include "Vector2.h"
#include <cmath>

void Vector2::normalise() {}

float Vector2::magnitude()
{
  return sqrt(x * x + y * y);
}
