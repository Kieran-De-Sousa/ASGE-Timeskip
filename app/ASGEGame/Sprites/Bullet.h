//
// Created by tpasl on 4/6/2022.
//

#ifndef ASGEGAME_BULLET_H
#define ASGEGAME_BULLET_H

#include "Sprites/Sprite.h"
#include <cmath>

class Bullet : public Sprite
{
 public:
  struct Vector2
  {
    float x = 0;
    float y = 0;
    void normalise();
    float magnitude();
  };
};

#endif // ASGEGAME_BULLET_H
