#ifndef ASGEGAME_SCENEMANAGER_H
#define ASGEGAME_SCENEMANAGER_H

#include "Scene.h"
#include <vector>

class SceneManager
{
 public:
  explicit SceneManager(std::shared_ptr<Scene> const& scene);

  SceneManager()          = default;
  virtual ~SceneManager() = default;

  void setScene(const std::shared_ptr<Scene>& scene);
  Scene* getCurrentScene();

  void update();
  void fixedupdate();
  void render();

 protected:
  std::shared_ptr<Scene> currentScene;
  std::vector<std::shared_ptr<Scene>> scenes;
};

#endif // ASGEGAME_SCENEMANAGER_H
