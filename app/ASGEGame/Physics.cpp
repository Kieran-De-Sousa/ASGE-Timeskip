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
  std::vector<std::shared_ptr<ASGE::Sprite>> _collisionBodies,
  std::vector<std::shared_ptr<ASGE::Sprite>> _tiles)
{
  if (useCollision)
  {
    for (int i = 0; i < static_cast<int>(_collisionBodies.size()); i++)
    {
      HitBox* playerBody = new HitBox;
      playerBody->getHitBox(_collisionBodies[static_cast<unsigned int>(i)]);
      for (int j = 0; j < static_cast<int>(_tiles.size()); ++j)
      {
        HitBox* tileBox = new HitBox;
        tileBox->getHitBox(_tiles[static_cast<unsigned int>(j)]);
        /// Y Collisions
        {
          /// Bottom Collision
          if (
            (static_cast<int>(playerBody->hitBoxRect[3]) >
             static_cast<int>(tileBox->hitBoxRect[1])) &&
            (static_cast<int>(playerBody->hitBoxRect[3]) <
             static_cast<int>(tileBox->hitBoxRect[3])))
          {
            if (
              (static_cast<int>(playerBody->hitBoxRect[0]) >
               static_cast<int>(tileBox->hitBoxRect[0])) &&
              (static_cast<int>(playerBody->hitBoxRect[0]) <
               static_cast<int>(tileBox->hitBoxRect[2])))
            {
              // Logging::DEBUG("successful collision");
              _collisionBodies[static_cast<unsigned int>(i)]->yPos(
                tileBox->hitBoxRect[1] - _collisionBodies[static_cast<unsigned int>(i)]->height());
            }
          }
          /// Top Collision
          if (
            (static_cast<int>(playerBody->hitBoxRect[1]) >
             static_cast<int>(tileBox->hitBoxRect[1])) &&
            (static_cast<int>(playerBody->hitBoxRect[1]) <
             static_cast<int>(tileBox->hitBoxRect[3])))
          {
            if (((static_cast<int>(playerBody->hitBoxRect[0]) >
                  static_cast<int>(tileBox->hitBoxRect[0])) &&
                 (static_cast<int>(playerBody->hitBoxRect[0]) <
                  static_cast<int>(tileBox->hitBoxRect[2]))))
            {
              // Logging::DEBUG("successful collision");
              _collisionBodies[static_cast<unsigned int>(i)]->yPos(tileBox->hitBoxRect[3]);
            }
            if (((static_cast<int>(playerBody->hitBoxRect[2]) >
                  static_cast<int>(tileBox->hitBoxRect[0])) &&
                 (static_cast<int>(playerBody->hitBoxRect[2]) <
                  static_cast<int>(tileBox->hitBoxRect[2]))))
            {
              // Logging::DEBUG("successful collision");
              _collisionBodies[static_cast<unsigned int>(i)]->yPos(tileBox->hitBoxRect[3]);
            }
          }
        }
        /// X Collisions
        {
          /// Right Collision
          if (
            (static_cast<int>(playerBody->hitBoxRect[2]) >
             static_cast<int>(tileBox->hitBoxRect[0])) &&
            (static_cast<int>(playerBody->hitBoxRect[2]) <
             static_cast<int>(tileBox->hitBoxRect[2])))
          {
            if (
              (static_cast<int>(playerBody->hitBoxRect[1]) >
               static_cast<int>(tileBox->hitBoxRect[1])) &&
              (static_cast<int>(playerBody->hitBoxRect[1]) <
               static_cast<int>(tileBox->hitBoxRect[3])))
            {
              if (
                (static_cast<int>(playerBody->hitBoxRect[3]) >
                 static_cast<int>(tileBox->hitBoxRect[1])) &&
                (static_cast<int>(playerBody->hitBoxRect[3]) <
                 static_cast<int>(tileBox->hitBoxRect[3])))
              {
                _collisionBodies[static_cast<unsigned int>(i)]->xPos(
                  tileBox->hitBoxRect[0] - _collisionBodies[static_cast<unsigned int>(i)]->width());
              }
            }
          }
          /// Left Collision
          if (
            (static_cast<int>(playerBody->hitBoxRect[0]) >
             static_cast<int>(tileBox->hitBoxRect[0])) &&
            (static_cast<int>(playerBody->hitBoxRect[0]) <
             static_cast<int>(tileBox->hitBoxRect[2])))
          {
            if (
              (static_cast<int>(playerBody->hitBoxRect[1]) >
               static_cast<int>(tileBox->hitBoxRect[1])) &&
              (static_cast<int>(playerBody->hitBoxRect[1]) <
               static_cast<int>(tileBox->hitBoxRect[3])))
            {
              if (
                (static_cast<int>(playerBody->hitBoxRect[3]) >
                 static_cast<int>(tileBox->hitBoxRect[1])) &&
                (static_cast<int>(playerBody->hitBoxRect[3]) <
                 static_cast<int>(tileBox->hitBoxRect[3])))
              {
                _collisionBodies[static_cast<unsigned int>(i)]->xPos(
                  tileBox->hitBoxRect[0] + _tiles[static_cast<unsigned int>(i)]->width());
              }
            }
          }
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
