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
#include "HitBox.h"
#include "Player.h"
#include "Sprite.h"

#ifndef ASGEGAME_PHYSICS_H
#  define ASGEGAME_PHYSICS_H

namespace Physics
{
  class PhysicsManager
  {
   public:
    void
    rigidBodyEnable(std::vector<std::unique_ptr<ASGE::Sprite>> _rbObjects, bool _gravityControl);
    void setCollisions(bool _control);
    void setGravity(float _gravity);
    void collisionController(
      std::vector<std::shared_ptr<ASGE::Sprite>> _collisionBodies,
      std::vector<std::shared_ptr<ASGE::Sprite>> _tiles);
    void rigidBodyController(std::vector<std::unique_ptr<ASGE::Sprite>> _rigidBodies);

   private:
    bool useCollision;
    float useGravity;
    std::unique_ptr<ASGE::Sprite> currentSprite = nullptr;
    /// rigidBodies default handles 20 objects to prevent memory being reassigned during runtime
    std::vector<std::unique_ptr<ASGE::Sprite>> collisionBodies;
    /// rigidBodies default handles 20 objects to prevent memory being reassigned during runtime
    std::vector<std::unique_ptr<ASGE::Sprite>> rigidBodies;
  };
};

#endif // ASGEGAME_PHYSICS_H
