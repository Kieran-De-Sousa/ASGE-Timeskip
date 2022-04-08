#ifndef ASGEGAME_SCENEMANAGER_H
#define ASGEGAME_SCENEMANAGER_H

/// FSM
#include "Scenes/Scene.h"
/// State Tracking
#include "Scenes/GameScenes.h"

#include <vector>

/**
 * @brief Manager class handling game state
 * @details Runs virtual function from 'Scene' base class for the current scene
 * @details Pure virtual functions in base scene class are then overloaded in derived classes
 * @author Kieran
 */
class SceneManager
{
 public:
  /**
   * @brief Constructor w/Param
   * @details Use when starting scene is known upon instantiation
   * @param rendererRef Required in all game scenes for rendering
   * @param inputRef Required in all game scenes for input systems
   * @param scene Default/starting scene for game
   */
  SceneManager(
    ASGE::Renderer& rendererRef, ASGE::Input& inputRef, const std::shared_ptr<Scene>& scene);
  /**
   * @brief Default constructor
   * @details Use when starting scene is unknown upon creation - Use setter functions
   * when needed to set game state
   * @param rendererRef Required in all game scenes for rendering
   * @param inputRef Required in all game scenes for input systems
   * @see setCurrentScene()
   */
  explicit SceneManager(ASGE::Renderer& rendererRef, ASGE::Input& inputRef);
  virtual ~SceneManager() = default;

  /**
   * @brief Adds current scene to 'scenes' vector
   * @param scene Scene to add
   */
  void addScene(const std::shared_ptr<Scene>& scene);

  /**
   * @brief Sets current scene and calls init function within the scene
   * @param scene Scene to call overloaded functions
   */
  void setCurrentScene(const std::shared_ptr<Scene>& scene);
  [[nodiscard]] GameScene getCurrentScene() const;

  void checkCurrentSceneState();

  /// Functions called within 'ASGEGame' that calls corresponding function in the current
  /// game scene
  virtual void keyHandler(ASGE::SharedEventData data);
  virtual void update(ASGE::GameTime us);
  virtual void fixedUpdate(ASGE::GameTime us);
  virtual void render(ASGE::GameTime us);

 protected:
  /// Save a pointer of renderer and input to pass into game scenes
  std::unique_ptr<ASGE::Renderer> renderer;
  std::unique_ptr<ASGE::Input> inputs;
  /// Scene FSM
  std::shared_ptr<Scene> currentScene;
  std::vector<std::shared_ptr<Scene>> scenes;
};

#endif // ASGEGAME_SCENEMANAGER_H
