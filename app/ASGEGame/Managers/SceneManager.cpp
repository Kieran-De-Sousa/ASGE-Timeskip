#include "SceneManager.h"

SceneManager::SceneManager(
  ASGE::Renderer& rendererRef, ASGE::Input& inputRef, const std::shared_ptr<Scene>& scene) :
  renderer(&rendererRef),
  inputs(&inputRef)
{
  addScene(scene);
  setCurrentScene(scene);
}

SceneManager::SceneManager(ASGE::Renderer& rendererRef, ASGE::Input& inputRef) :
  renderer(&rendererRef), inputs(&inputRef)
{
}

void SceneManager::addScene(const std::shared_ptr<Scene>& scene)
{
  scenes.push_back(scene);
}

void SceneManager::setCurrentScene(const std::shared_ptr<Scene>& scene)
{
  currentScene = scene;
  scene->init();
}

Scene* SceneManager::getCurrentScene()
{
  return currentScene.get();
}

void SceneManager::keyHandler(ASGE::SharedEventData data)
{
  currentScene->keyHandler(data);
}

void SceneManager::update(ASGE::GameTime us)
{
  currentScene->update(us);
}
void SceneManager::render(ASGE::GameTime us)
{
  currentScene->render(us);
}
void SceneManager::fixedUpdate(ASGE::GameTime us)
{
  currentScene->fixedUpdate(us);
}