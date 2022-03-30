#ifndef ASGEGAME_SCENEMANAGER_H
#define ASGEGAME_SCENEMANAGER_H

#include "Scene.h"
#include <memory>
#include <vector>

class SceneManager : public std::enable_shared_from_this<SceneManager>
{
 public:
  void createScene(std::shared_ptr<Scene> scene);

 protected:
  std::vector<std::shared_ptr<Scene>> scenes;
};

#endif // ASGEGAME_SCENEMANAGER_H
