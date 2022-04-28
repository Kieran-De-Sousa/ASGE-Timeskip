#include "Helper.h"

bool Helper::CollisionDetection::onTop(
  const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface)
{
  return (sprite.v3.y >= surface.v1.y && sprite.v3.y <= surface.v1.y);
}

bool Helper::CollisionDetection::onBottom(
  const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface)
{
  return (sprite.v1.y >= surface.v3.y && sprite.v1.y <= surface.v3.y);
}

bool Helper::CollisionDetection::onLeft(
  const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface)
{
  return (sprite.v1.x >= surface.v2.x && sprite.v1.x <= surface.v2.x);
}

bool Helper::CollisionDetection::onRight(
  const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface)
{
  return (sprite.v2.x >= surface.v1.x && sprite.v2.x <= surface.v1.x);
}

bool Helper::CollisionDetection::touchingTop(
  const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface)
{
  return (sprite.v3.y > surface.v1.y && sprite.v3.y < surface.v3.y);
}

bool Helper::CollisionDetection::touchingBottom(
  const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface)
{
  return (sprite.v3.y > surface.v1.y && sprite.v1.y < surface.v3.y);
}

bool Helper::CollisionDetection::touchingLeft(
  const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface)
{
  return (sprite.v1.x < surface.v2.x && sprite.v1.x > surface.v1.x);
}

bool Helper::CollisionDetection::touchingRight(
  const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface)
{
  return (sprite.v2.x > surface.v1.x && sprite.v2.x < surface.v2.x);
}

bool Helper::CollisionDetection::inXBounds(
  const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2)
{
  return (
    (sprite_1.v1.x >= sprite_2.v1.x && sprite_1.v1.x <= sprite_2.v2.x) ||
    (sprite_1.v2.x >= sprite_2.v1.x && sprite_1.v2.x <= sprite_2.v2.x));
}
bool Helper::CollisionDetection::inYBounds(
  const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2)
{
  return ((sprite_1.v1.y >= sprite_2.v1.y && sprite_1.v1.y <= sprite_2.v4.y));
}

[[maybe_unused]] bool Helper::CollisionDetection::playerYChecking(
  const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2)
{
  return ((sprite_1.v1.y >= sprite_2.v1.y && sprite_1.v1.y <= sprite_2.v3.y));
}
int Helper::CollisionDetection::resolveCollision(
  const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2)
{
  if (Helper::CollisionDetection::inXBounds(sprite_1, sprite_2))
  {
    if (Helper::CollisionDetection::touchingTop(sprite_1, sprite_2))
    {
      return 3;
    }
    if (Helper::CollisionDetection::touchingBottom(sprite_1, sprite_2))
    {
      return 4;
    }
  }
  if (Helper::CollisionDetection::inYBounds(sprite_1, sprite_2))
  {
    // Logging::DEBUG("in Y Bounds");
    if (Helper::CollisionDetection::touchingRight(sprite_1, sprite_2))
    {
      Logging::DEBUG("Player Right Collision");
      return 1;
    }
    if (Helper::CollisionDetection::touchingLeft(sprite_1, sprite_2))
    {
      Logging::DEBUG("Player Left Collision");
      return 2;
    }
  }
  //  if (Helper::CollisionDetection::touchingRight(sprite_1, sprite_2))
  //  {
  //     Logging::DEBUG("Player Left Collision");
  //  }
  //  if (Helper::CollisionDetection::touchingLeft(sprite_1, sprite_2))
  //  {
  //     Logging::DEBUG("Player Right Collision");
  //  }
  return 0;
}

bool Helper::CollisionDetection::isInside(
  const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2)
{
  if (inColYBounds(sprite_1, sprite_2))
  {
    if (inXBounds(sprite_1, sprite_2))
    {
      return true;
    }
  }
  return false;
}
bool Helper::CollisionDetection::inColYBounds(
  const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2)
{
  return (
    (sprite_1.v1.y >= sprite_2.v1.y && sprite_1.v1.y <= sprite_2.v4.y) ||
    (sprite_1.v3.y >= sprite_2.v1.y && sprite_1.v3.y <= sprite_2.v4.y));
}
