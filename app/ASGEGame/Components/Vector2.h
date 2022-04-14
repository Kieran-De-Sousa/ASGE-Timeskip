#ifndef ASGEGAME_VECTOR2_H
#define ASGEGAME_VECTOR2_H

struct Vector2
{
  float x = 0;
  float y = 0;

  void normalise();
  float magnitude();
};

#endif // ASGEGAME_VECTOR2_H
