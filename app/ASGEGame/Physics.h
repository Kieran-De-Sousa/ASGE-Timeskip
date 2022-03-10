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
  struct Box
  {
    ASGE::Point2D pos;
    ASGE::Point2D size;
    ASGE::Point2D vel;
  };
  class PhysicsManager
  {
   public:
    void
    rigidBodyEnable(std::vector<std::unique_ptr<ASGE::Sprite>> _rbObjects, bool _gravityControl);
    void setCollisions(bool _control);
    void setGravity(float _gravity);
    void collisionController(
      std::vector<std::shared_ptr<Entity>> _collisionBodies,
      std::vector<std::shared_ptr<ASGE::Sprite>> _tiles);
    void rigidBodyController(std::vector<std::unique_ptr<ASGE::Sprite>> _rigidBodies);
    bool pointVsBox(const ASGE::Point2D& p, const Box& r);
    bool boxVsBox(const Physics::Box& r1, const Box& r2);
    bool rayVsBox(
      const ASGE::Point2D& ray_origin, const ASGE::Point2D& ray_dir, const Box& target,
      ASGE::Point2D& contact_point, ASGE::Point2D& contact_normal, float& t_hit_near);
    bool dynamicRectVsRect(
      const Box& in, const Box& target, ASGE::Point2D& contact_point, ASGE::Point2D& contact_normal,
      float& contact_time, float fElapsedTime);

   private:
    bool useCollision;
    float useGravity;
    std::unique_ptr<ASGE::Sprite> currentSprite = nullptr;
    /// rigidBodies default handles 20 objects to prevent memory being reassigned during runtime
    std::vector<std::unique_ptr<Entity>> collisionBodies;
    /// rigidBodies default handles 20 objects to prevent memory being reassigned during runtime
    std::vector<std::unique_ptr<ASGE::Sprite>> rigidBodies;
    std::vector<Box> collisionTiles;
    ASGE::Point2D cp, cn;
    float ct;
    float t = 0, min_t = INFINITY;
    Box playerBox;
    Box tileBox;
  };
};

#endif // ASGEGAME_PHYSICS_H
