#ifndef ASGEGAME_SPRITE_H
#define ASGEGAME_SPRITE_H

/// Game Engine
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
  explicit Sprite(ASGE::Renderer& rendererRef) : renderer(&rendererRef) {}
  virtual ~Sprite() = default;

  virtual void update() {}

  /**
   * @brief Initialise sprite with default values
   * @details Pass filename in std::string to initialise a ASGE sprite with default values
   * @see setPosition
   * @param filename
   */
  bool initialiseSprite(const std::string& filename);

  bool setSprite(const std::string& filename);
  /**
   * @brief Get the ASGE sprite interface of the sprite class
   * @return sprite
   */
  ASGE::Sprite* getSprite() { return sprite.get(); }
  /**
   * @brief MAYBE NOT NEEDED DUE TO ASGE SPRITES HAVING xPos() AND yPos()
   * @param x
   * @param y
   */
  void setPosition(const float& x, const float& y);

  void setSpriteVariables(const float& width, const float& height, const int16_t& z_order);

 protected:
  std::unique_ptr<ASGE::Sprite> sprite;
  /// TODO: CAN BE REGULAR POINTER
  std::unique_ptr<ASGE::Renderer> renderer;

  const std::vector<float> DEFAULT_SPRITE_POSITION{ 0, 0 };
  const std::vector<float> DEFAULT_SPRITE_VARIABLES{ 16, 16 };
  const int16_t DEFAULT_Z_ORDER = 0;
};
#endif // ASGEGAME_SPRITE_H
