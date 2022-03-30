#include "SceneManager.h"

SceneManager::SceneManager(const std::shared_ptr<Scene>& scene)
{
  setScene(scene);
}

void SceneManager::setScene(const std::shared_ptr<Scene>& scene)
{
  currentScene = scene;
  scene->init();
}

Scene* SceneManager::getCurrentScene()
{
  return currentScene.get();
}

void SceneManager::update()
{
  currentScene->update();
}
void SceneManager::render()
{
  currentScene->render();
}
void SceneManager::fixedupdate()
{
  currentScene->fixedupdate();
}
