#include "Scene.h"

Scene::Scene(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene) :
  renderer(&rendererRef), inputs(&inputRef), sceneStatus(scene), DEFAULT_SCENE_STATUS(scene)
{
}

/// SETTER & GETTER FUNCTIONS
// Scene Status
void Scene::setDefaultSceneStatus()
{
  sceneStatus = DEFAULT_SCENE_STATUS;
}
SceneStatus Scene::getSceneStatus() const
{
  return sceneStatus;
}
// Game Scene
GameScene Scene::getScene() const
{
  return sceneStatus.current_scene;
}
void Scene::setNewScene(const GameScene& game_scene)
{
  sceneStatus.new_scene    = game_scene;
  sceneStatus.change_scene = true;
}
