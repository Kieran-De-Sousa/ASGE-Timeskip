#include "Scene.h"
#include "SceneManager.h"

void Scene::setup(std::shared_ptr<SceneManager> sm)
{
  manager = sm;
}
std::shared_ptr<SceneManager> Scene::getSceneManager()
{
  if (!manager.expired())
  {
    return manager.lock();
  }
  return nullptr;
}
