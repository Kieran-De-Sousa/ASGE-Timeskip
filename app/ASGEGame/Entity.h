#ifndef ASGEGAME_ENTITY_H
#define ASGEGAME_ENTITY_H

#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

#include "Sprite.h"

#define IDLE      0
#define RUNNING   1
#define JUMPING   2

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

  //Animation
  //int getState();
  //void setSate(int state);

  // Attack
  void setAttack(int attack);
  [[nodiscard]] int getAttack() const;

  virtual void update (const ASGE::GameTime& us);
  bool entityPlayer();
  bool initSprite(std::string& filename, int index);


 private:
<<<<<<< Updated upstream
  int entityHealth;
  int entityAttack;

  std::unique_ptr<ASGE::Sprite> player1;

  Sprite sprites[5];

=======
  int entityHealth = 0;
  int entityAttack = 0;
  //int entityState = IDLE;
>>>>>>> Stashed changes
};
#endif // ASGEGAME_ENTITY_H
