#ifndef ASGEGAME_GAMECOMPONENT_H
#define ASGEGAME_GAMECOMPONENT_H

/// Game Engine
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>

class GameComponent
{
 public:
  enum class ComponentType : int
  {
    UNKNOWN = 0,
    SPRITE  = 1,
    BULLET  = 2,
    ENEMY   = 3,
    PLAYER  = 4,
    UI      = 5
  };
  explicit GameComponent() = default;
  virtual ~GameComponent() = default;

  virtual void update(const ASGE::GameTime& us) = 0;

  void setComponentType(const ComponentType& componentType) { type = componentType; }
  [[nodiscard]] ComponentType getComponentType() const { return type; }

 protected:
  ComponentType type = ComponentType::UNKNOWN;
};

#endif // ASGEGAME_GAMECOMPONENT_H
