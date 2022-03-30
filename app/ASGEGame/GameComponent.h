#ifndef ASGEGAME_GAMECOMPONENT_H
#define ASGEGAME_GAMECOMPONENT_H

class GameComponent
{
 public:
  explicit GameComponent(){};
  virtual ~GameComponent() = default;

  virtual void update() = 0;

 protected:
 private:
};

#endif // ASGEGAME_GAMECOMPONENT_H
