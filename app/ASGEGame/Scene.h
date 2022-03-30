#ifndef ASGEGAME_SCENE_H
#define ASGEGAME_SCENE_H

#include <memory>

class Scene : public std::enable_shared_from_this<Scene>
{
 public:
  Scene()          = default;
  virtual ~Scene() = default;

  virtual bool init(){};

  virtual void update(){};
  virtual void fixedupdate(){};
  virtual void render(){};
};

#endif // ASGEGAME_SCENE_H
