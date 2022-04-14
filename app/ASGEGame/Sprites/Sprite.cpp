#include "Sprite.h"

Sprite::Sprite(ASGE::Renderer& rendererRef) : renderer(&rendererRef)
{
  type = ComponentType::SPRITE;
}

bool Sprite::initialiseSprite(const std::string& filename)
{
  sprite = renderer->createUniqueSprite();
  if (!setSprite(filename))
  {
    return false;
  }
  /**
   * @details Sets default values for sprite initialisation
   */
  setPosition(DEFAULT_SPRITE_POSITION[0], DEFAULT_SPRITE_POSITION[1]);
  setSpriteVariables(DEFAULT_SPRITE_VARIABLES[0], DEFAULT_SPRITE_VARIABLES[1], DEFAULT_Z_ORDER);
  sprite->scale(1);

  return true;
}

bool Sprite::setSprite(const std::string& filename)
{
  if (!sprite->loadTexture(filename))
  {
    Logging::WARN("Could not load file: " + filename);
    return false;
  }
  return true;
}

void Sprite::setPosition(const float& x, const float& y)
{
  sprite->xPos(x);
  sprite->yPos(y);
}

void Sprite::setSpriteVariables(const float& width, const float& height, const int16_t& z_order)
{
  sprite->width(width);
  sprite->height(height);
  sprite->setGlobalZOrder(z_order);
}