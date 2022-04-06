//
// Created by tpasl on 4/6/2022.
//

#include "bullet.h"
void bullet::Vector2::normalise()
{
  x /= magnitude();
  y /= magnitude();
}

float bullet::Vector2::magnitude()
{
  return sqrt(x * x + y * y);
}
