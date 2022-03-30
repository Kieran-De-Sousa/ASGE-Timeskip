#include "SceneManager.h"

void SceneManager::createScene(std::shared_ptr<Scene> scene)
{
  if (scene)
  {
    scenes.push_back(scene);
    scene->setup(shared_from_this());
  }
}
