//
// Created by tpasl on 4/6/2022.
//

#include "Bullet.h"
void Bullet::Vector2::normalise() {}

float Bullet::Vector2::magnitude()
{
  return sqrt(x * x + y * y);
}
