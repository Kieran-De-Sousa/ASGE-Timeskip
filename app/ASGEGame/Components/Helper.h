#ifndef ASGEGAME_HELPER_H
#define ASGEGAME_HELPER_H

/// Game Engine
// CollisionDetection
#include <Engine/Logger.hpp>
#include <Engine/Sprite.hpp>

/**
 * @author Kieran
 */
namespace Helper
{
  namespace CollisionDetection
  {
    /**
     * @brief Checks if a ASGE sprite is inside of another ASGE sprite
     * @param sprite_1
     * @param sprite_2
     * @return boolean result
     */
    bool isInside(const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2);

    bool onTop(const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface);
    bool onBottom(const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface);
    bool onLeft(const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface);
    bool onRight(const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface);

    /**
     * @brief Checks if a ASGE sprite is touching the the top of another ASGE sprite
     * @param sprite "Moving" sprite
     * @param surface "World" sprite
     * @return boolean result
     */
    bool touchingTop(const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface);
    /**
     * @brief Checks if a ASGE sprite is touching the bottom of another ASGE sprite
     * @param sprite "Moving" sprite
     * @param surface "World" sprite
     * @return boolean result
     */
    bool touchingBottom(const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface);
    /**
     * @brief Checks if a ASGE sprite is touching the left of another ASGE sprite
     * @param sprite "Moving" sprite
     * @param surface "World" sprite
     * @return boolean result
     */
    bool touchingLeft(const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface);
    /**
     * @brief Checks if a ASGE sprite is touching the right of another ASGE sprite
     * @param sprite "Moving" sprite
     * @param surface "World" sprite
     * @return boolean result
     */
    bool touchingRight(const ASGE::SpriteBounds& sprite, const ASGE::SpriteBounds& surface);
    /**
     *
     * @param sprite_1
     * @param sprite_2
     * @return
     */
    bool inXBounds(const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2);
    /**
     *
     * @param sprite_1
     * @param sprite_2
     * @return
     */
    bool inYBounds(const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2);

    [[maybe_unused]] bool
    playerYChecking(const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2);

    int resolveCollision(const ASGE::SpriteBounds& sprite_1, const ASGE::SpriteBounds& sprite_2);

  }
} // namespace Helper

#endif // ASGEGAME_HELPER_H
