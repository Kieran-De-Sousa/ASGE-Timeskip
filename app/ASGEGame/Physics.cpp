#include "Physics.h"

void Physics::PhysicsManager::rigidBodyEnable(
  std::vector<std::unique_ptr<ASGE::Sprite>> _rbObjects, bool _gravityControl)
{
}
void Physics::PhysicsManager::setCollisions(bool _control)
{
  useCollision = _control;
}

void Physics::PhysicsManager::setGravity(float _gravity)
{
  useGravity = _gravity;
}

void Physics::PhysicsManager::collisionController(
  std::vector<std::shared_ptr<Entity>> _collisionBodies,
  std::vector<std::shared_ptr<ASGE::Sprite>> _tiles)
{
  if (useCollision)
  {
    for (int i = 0; i < _collisionBodies.size(); i++)
    {
      playerBox.pos.x  = _collisionBodies[i]->getSprite()->xPos();
      playerBox.pos.y  = _collisionBodies[i]->getSprite()->xPos();
      playerBox.size.x = _collisionBodies[i]->getSprite()->width();
      playerBox.size.y = _collisionBodies[i]->getSprite()->height();
      playerBox.vel.x  = _collisionBodies[i]->getVelocity().x;
      playerBox.vel.y  = _collisionBodies[i]->getVelocity().y;

      for (int j = 0; j < _tiles.size(); j++)
      {
        tileBox.pos.x  = _tiles[j]->xPos();
        tileBox.pos.y  = _tiles[j]->yPos();
        tileBox.size.x = _tiles[j]->width();
        tileBox.size.y = _tiles[j]->height();
        tileBox.vel.x  = 0;
        tileBox.vel.y  = 0;
        if (dynamicRectVsRect(playerBox, tileBox, cp, cn, ct, t))
        {
          _collisionBodies[i]->setVelocity(
            cn.x * std::abs(_collisionBodies[i]->getVelocity().x * (1 - ct)),
            (cn.y * std::abs(_collisionBodies[i]->getVelocity().y * (1 - ct))));
        }
      }
    }
  }
}

void Physics::PhysicsManager::rigidBodyController(
  std::vector<std::unique_ptr<ASGE::Sprite>> _rigidBodies)
{
  for (int i = 0; i < static_cast<int>(_rigidBodies.size()); i++)
  {
  }
}
bool Physics::PhysicsManager::pointVsBox(const ASGE::Point2D& p, const Box& r)
{
  return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
}
bool Physics::PhysicsManager::boxVsBox(const Physics::Box& r1, const Box& r2)
{
  return (
    r1.pos.x < r2.pos.x + r2.size.x && r1.pos.x + r1.size.x > r2.pos.x &&
    r1.pos.y < r2.pos.y + r2.size.y && r1.pos.y + r1.size.y > r2.pos.y);
}
bool Physics::PhysicsManager::rayVsBox(
  const ASGE::Point2D& ray_origin, const ASGE::Point2D& ray_dir, const Physics::Box& target,
  ASGE::Point2D& contact_point, ASGE::Point2D& contact_normal, float& t_hit_near)
{
  ASGE::Point2D t_near;
  t_near.x = (target.pos.x - ray_origin.x) / ray_dir.x;
  t_near.y = (target.pos.y - ray_origin.y) / ray_dir.y;
  ASGE::Point2D t_far;
  t_far.x = (target.pos.x + target.size.x - ray_origin.x) / ray_dir.x;
  t_far.y = (target.pos.y + target.size.y - ray_origin.y) / ray_dir.y;

  if (t_near.x > t_far.x)
  {
    std::swap(t_near.x, t_far.x);
  }
  if (t_near.y > t_far.y)
  {
    std::swap(t_near.y, t_far.y);
  }
  if (t_near.x > t_far.y || t_near.x > t_far.x)
  {
    return false;
  }
  t_hit_near      = max(t_near.x, t_near.y);
  float t_hit_far = min(t_far.x, t_far.y);

  if (t_hit_far < 0)
  {
    return false;
  }
  contact_point.x = ray_origin.x + t_hit_near * ray_dir.x;
  contact_point.y = ray_origin.y + t_hit_near * ray_dir.y;

  if (t_near.x > t_near.y)
    if (ray_dir.x < 0)
      contact_normal = { 1, 0 };
    else
      contact_normal = { -1, 0 };
  else if (t_near.x < t_near.y)
    if (ray_dir.y < 0)
      contact_normal = { 0, 1 };
    else
      contact_normal = { 0, -1 };
  return true;
}
bool Physics::PhysicsManager::dynamicRectVsRect(
  const Physics::Box& in, const Physics::Box& target, ASGE::Point2D& contact_point,
  ASGE::Point2D& contact_normal, float& contact_time, float fElapsedTime)
{
  if (in.vel.x == 0 && in.vel.y == 0)
  {
    return false;
  }
  Box expanded_target;
  expanded_target.pos.x  = target.pos.x - in.size.x / 2;
  expanded_target.pos.y  = target.pos.y - in.size.y / 2;
  expanded_target.size.x = target.size.x + in.size.x;
  expanded_target.size.y = target.size.y + in.size.y;
  if (rayVsBox(
        { in.pos.x + in.size.x / 2, in.pos.y + in.size.y / 2 },
        in.vel * fElapsedTime,
        expanded_target,
        contact_point,
        contact_normal,
        contact_time))
  {
    if (contact_time < 1.0f)
    {
      return true;
    }
  }
  return false;
}
