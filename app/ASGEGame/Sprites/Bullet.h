//
// Created by tpasl on 4/6/2022.
//

#ifndef ASGEGAME_BULLET_H
#define ASGEGAME_BULLET_H

#include "Sprite.h"
#include <cmath>

struct Bullet : public ASGE::Sprite
{
  struct Vector2
  {
    float x = 0;
    float y = 0;
    void normalise();
    float magnitude();
  };
  // Vector2 direction;
  float speed;
  std::vector<std::unique_ptr<ASGE::Sprite>> imgSprite;
  std::vector<Vector2> directions;
};

#endif // ASGEGAME_BULLET_H
