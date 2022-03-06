//
// Created by tpasl on 3/6/2022.
//

#include "HitBox.h"

std::vector<float> HitBox::getHitBox(std::shared_ptr<ASGE::Sprite> _sprite)
{
  hitBoxRect.clear();
  hitBoxRect.push_back(_sprite->xPos());
  hitBoxRect.push_back(_sprite->yPos());
  hitBoxRect.push_back(_sprite->xPos() + _sprite->width());
  hitBoxRect.push_back(_sprite->yPos() + _sprite->height());
  return hitBoxRect;
}
