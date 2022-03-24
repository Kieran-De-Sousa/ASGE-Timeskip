#ifndef ASGEGAME_ENTITY_H
#define ASGEGAME_ENTITY_H

/// Game Engine
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

/// Base Class
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
  explicit Entity(ASGE::Renderer& rendererRef) : Sprite(rendererRef){};
  ~Entity() override = default;

  virtual void update() override = 0;

  /// SETTER & GETTER FUNCTIONS
  // Health
  void setHealth(int health) { entityHealth = health; };
  [[nodiscard]] int getHealth() const { return entityHealth; }
  // Attack
  void setAttack(int attack) { entityAttack = attack; };
  [[nodiscard]] int getAttack() const { return entityAttack; };

 protected:
  int entityHealth = 0;
  int entityAttack = 0;
};
#endif // ASGEGAME_ENTITY_H
