#include "SceneManager.h"

SceneManager::SceneManager(
  ASGE::Renderer& rendererRef, ASGE::Input& inputRef, const std::shared_ptr<Scene>& scene) :
  renderer(&rendererRef),
  inputs(&inputRef)
{
  addGameScenes();
  setCurrentScene(scene);
}

SceneManager::SceneManager(ASGE::Renderer& rendererRef, ASGE::Input& inputRef) :
  renderer(&rendererRef), inputs(&inputRef)
{
  addGameScenes();
}

void SceneManager::addGameScenes()
{
  for (const auto& scene : ALL_GAMESCENES)
  {
    auto game_scene = sceneFactory(scene);
    if (game_scene != nullptr)
    {
      addScene(game_scene);
    }
  }
  /// Sets current scene of game to first scene in scenes vector
  setCurrentScene(scenes.front());
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

GameScene SceneManager::getCurrentScene() const
{
  return currentScene->getScene();
}

std::shared_ptr<Scene> SceneManager::sceneFactory(const GameScene& gameScene)
{
  switch (gameScene)
  {
    case GameScene::MAIN_MENU:
      return std::make_shared<SceneMainMenu>(*renderer, *inputs, gameScene);
    case GameScene::LEVEL_1:
      return std::make_shared<SceneLevel1>(*renderer, *inputs, gameScene);
    /// @Note: Cannot compile with 'Default', meaning all enumeration cases are required.
    case GameScene::UNDEFINED:
    case GameScene::LEVEL_2:
    case GameScene::LEVEL_SELECT:
      return nullptr;
      /// ADD MORE CASES AS MORE SCENES ARE CREATED!
  }
}

void SceneManager::checkCurrentSceneState()
{
  /// Grabs state of current scene every frame
  const SceneStatus CURRENT_STATE = currentScene->getSceneStatus();
  // Update state to exit game if required
  exitGame = CURRENT_STATE.exit_game;
  if (CURRENT_STATE.change_scene)
  {
    for (const auto& scene : scenes)
    {
      if (scene->getScene() == CURRENT_STATE.new_scene)
      {
        setCurrentScene(scene);
      }
    }
  }
}

/// Calls virtual functions within scene base class
void SceneManager::keyHandler(const ASGE::SharedEventData& data)
{
  currentScene->keyHandler(data);
}
void SceneManager::input()
{
  currentScene->input();
}
void SceneManager::update(const ASGE::GameTime& us)
{
  currentScene->update(us);
}
void SceneManager::render(const ASGE::GameTime& us)
{
  currentScene->render(us);
}
void SceneManager::fixedUpdate(const ASGE::GameTime& us)
{
  currentScene->fixedUpdate(us);
}