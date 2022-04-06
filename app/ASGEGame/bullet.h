//
// Created by tpasl on 4/6/2022.
//

#ifndef ASGEGAME_BULLET_H
#define ASGEGAME_BULLET_H

#include "Sprite.h"
#include <cmath>

class bullet : public Sprite
{
  struct Vector2
  {
    float x = 0;
    float y = 0;
    void normalise();
    float magnitude();
  };
};

#endif // ASGEGAME_BULLET_H
