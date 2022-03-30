#ifndef ASGEGAME_SCENE_H
#define ASGEGAME_SCENE_H
#include <memory>
class SceneManager; // Forward Declaring
class Scene
{
 public:
  void setup(std::shared_ptr<SceneManager> sm);

  std::shared_ptr<SceneManager> getSceneManager();

 protected:
  std::weak_ptr<SceneManager> manager;
};

#endif // ASGEGAME_SCENE_H
