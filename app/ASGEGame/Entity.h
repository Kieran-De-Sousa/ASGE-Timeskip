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
  ~Entity() override;

  /// SETTER & GETTER FUNCTIONS
  // Health
  void setHealth(int health);
  int getHealth();
  // Attack
  void setAttack(int attack);
  [[nodiscard]] int getAttack() const;

  virtual void update (const ASGE::GameTime& us);
  bool entityPlayer();

 private:
  int entityHealth;
  int entityAttack;

  std::unique_ptr<ASGE::Sprite> player1;

  ObjRect animation_frames[4];
  unsigned int animation_index = 0;
  const float ANIMATION_FRAME_RATE = 0.1f;
  float animation_timer = 0.0f;
  enum entityState{IDLE, RUNNING, JUMPING, ATTACKING};
};
#endif // ASGEGAME_ENTITY_H
