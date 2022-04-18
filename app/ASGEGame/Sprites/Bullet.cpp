//
// Created by tpasl on 4/6/2022.
//

#include "Bullet.h"

Bullet::Bullet(ASGE::Renderer& rendererRef) : Entity(rendererRef), direction(0, 0)
{
  type = ComponentType::BULLET;
}