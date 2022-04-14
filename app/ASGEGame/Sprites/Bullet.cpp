//
// Created by tpasl on 4/6/2022.
//

#include "Bullet.h"

Bullet::Bullet(ASGE::Renderer& rendererRef) : Sprite(rendererRef)
{
  type = ComponentType::BULLET;
}