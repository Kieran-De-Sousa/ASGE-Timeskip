#include "Scene.h"

Scene::Scene(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene) :
  renderer(&rendererRef), inputs(&inputRef), sceneStatus(scene), DEFAULT_SCENE_STATUS(scene)
{
}

void Scene::keyHandler(const ASGE::SharedEventData& data)
{
  const auto* key  = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  if (keymap[ASGE::KEYS::KEY_ESCAPE])
  {
    sceneStatus.exit_game = true;
  }
  if (keymap[ASGE::KEYS::KEY_P])
  {
    setPauseScreen(!sceneStatus.pause_scene);
  }
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
void Scene::setPauseScreen(const bool& paused)
{
  sceneStatus.pause_scene = paused;
}