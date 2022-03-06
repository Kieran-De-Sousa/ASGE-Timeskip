//
// Created by tpasl on 3/6/2022.
//

#pragma once

#include <Engine/Gamepad.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>
#include <map>

#include <soloud.h>
#include <soloud_wav.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "Entity.h"
#include "Player.h"
#include "Sprite.h"

#ifndef ASGEGAME_HITBOX_H
#  define ASGEGAME_HITBOX_H

class HitBox
{
 public:
  std::vector<float> getHitBox(std::shared_ptr<ASGE::Sprite> _sprite);
  std::vector<float> hitBoxRect;
};

#endif // ASGEGAME_HITBOX_H
