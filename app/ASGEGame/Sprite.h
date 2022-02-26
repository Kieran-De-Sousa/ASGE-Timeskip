#ifndef ASGEGAME_SPRITE_H
#define ASGEGAME_SPRITE_H

#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

/**
 * @brief Base sprite class that is inherited by any object requiring ASGE Sprites
 * @details
 * @author Kieran
 */
class Sprite
{
 public:
  /**
   * @details Renderer required to be passed into constructor for creation of any Sprite related
   * objects
   * @param rendererRef Required for all objects using ASGE Sprites
   */
  explicit Sprite(ASGE::Renderer& rendererRef);
  virtual ~Sprite();

  /**
   * @details Pass filename in std::string to initialise a ASGE sprite with default values
   * @see setPosition
   * @param filename
   */
  bool initialiseSprite(std::string& filename);
  ASGE::Sprite* getSprite();

  /**
   * @brief MAYBE NOT NEEDED DUE TO ASGE SPRITES HAVING xPos() AND yPos()
   * @param x
   * @param y
   */
  void setPosition(float x, float y);
  void setSpriteVariables(float width, float height, int16_t z_order);

 private:
  std::unique_ptr<ASGE::Sprite> sprite;
  std::unique_ptr<ASGE::Renderer> renderer;

  /// Would be const due to not needing to be changed, however this results in compiler errors.
  std::array<float, 2> defaultSpritePosition{ 0, 0 };
  std::array<float, 2> defaultSpriteVariables{ 16, 16 };
  int16_t defaultZOrder = 0;
};
#endif // ASGEGAME_SPRITE_H
