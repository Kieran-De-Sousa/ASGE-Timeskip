#include "Sprite.h"

Sprite::Sprite(ASGE::Renderer& rendererRef) : renderer(&rendererRef) {}
Sprite::~Sprite() {}

bool Sprite::initialiseSprite(std::string& filename)
{
  sprite = renderer->createUniqueSprite();
  if (!sprite->loadTexture("data/sprite/Player1.png"))
  {
    Logging::WARN("Could not load file: " + filename);
    return false;
  }
  /**
   * @details Sets default values for sprite initialisation
   */
  setPosition(defaultSpritePosition[0], defaultSpritePosition[1]);
  setSpriteVariables(defaultSpriteVariables[0], defaultSpriteVariables[1], defaultZOrder);
  sprite->scale(1);



  return true;
}
ASGE::Sprite* Sprite::getSprite()
{
  return sprite.get();
}

void Sprite::setPosition(float x, float y)
{
  sprite->xPos(x);
  sprite->yPos(y);
}

void Sprite::setSpriteVariables(float width, float height, int16_t z_order)
{
  sprite->width(width);
  sprite->height(height);
  sprite->setGlobalZOrder(z_order);
}