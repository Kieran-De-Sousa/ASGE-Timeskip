#ifndef ASGEGAME_GAMECOMPONENT_H
#define ASGEGAME_GAMECOMPONENT_H

class GameComponent
{
 public:
  enum class ComponentType : int
  {
    UNKNOWN = 0,
    SPRITE  = 1,
    BULLET  = 2,
    ENEMY   = 3,
    PLAYER  = 4
  };
  explicit GameComponent() = default;
  virtual ~GameComponent() = default;

  virtual void update() = 0;

  void setComponentType(const ComponentType& componentType) { type = componentType; }
  [[nodiscard]] ComponentType getComponentType() const { return type; }

 protected:
  ComponentType type = ComponentType::UNKNOWN;
};

#endif // ASGEGAME_GAMECOMPONENT_H
