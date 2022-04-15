#ifndef ASGEGAME_PLAYERUI_H
#define ASGEGAME_PLAYERUI_H

#include "Sprite.h"
#include <Engine/Sprite.hpp>

class PlayerUI
{
 public:
  explicit PlayerUI() = default;
  virtual ~PlayerUI() = default;

  void init(std::unique_ptr<Sprite> sprite, float health_val, float y_val);
  // void update_health();
  // void render();
};

#endif // ASGEGAME_PLAYERUI_H
