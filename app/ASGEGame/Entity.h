#ifndef ASGEGAME_ENTITY_H
#define ASGEGAME_ENTITY_H

#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

#include "Sprite.h"

/**
 * @brief Shared class for player-controlled and non player-controlled objects
 * @details Entity objects (and inheriting classes) possess health, attack, [MORE ATTRIBUTES HERE]
 * @author Kieran
 */
class Entity : public Sprite
{
 public:
  /**
   * @brief Constructor w/Param
   * @details Use when initialisation variables are required in instantiation,
   * @param rendererRef Required for all objects using ASGE Sprites
   * @param health @param attack
   */
  explicit Entity(ASGE::Renderer& rendererRef, int health, int attack);
  /**
   * @brief Default constructor
   * @details Use when initialisation variables are not required in instantiation
   * @param rendererRef
   * @note Possibly unneeded, however the option is presented
   */
  explicit Entity(ASGE::Renderer& rendererRef);
  ~Entity() override = default;

  /// SETTER & GETTER FUNCTIONS
  // Health
  void setHealth(int health);
  int getHealth();
  // Attack
  void setAttack(int attack);
  [[nodiscard]] int getAttack() const;

 private:
  int entityHealth = 0;
  int entityAttack = 0;
};
#endif // ASGEGAME_ENTITY_H
