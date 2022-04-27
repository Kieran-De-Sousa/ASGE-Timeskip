#ifndef ASGEGAME_SCENEMANAGER_H
#define ASGEGAME_SCENEMANAGER_H

/// Scenes
#include "Scenes/Scene.h"
#include "Scenes/SceneLevel1.h"
#include "Scenes/SceneLevel2.h"
#include "Scenes/SceneLevel3.h"
#include "Scenes/SceneMainMenu.h"

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
   * @details Use when starting scene is unknown upon creation - Game uses first scene that can
   * be created within the 'sceneFactory' function as the starting scene
   * @param rendererRef Required in all game scenes for rendering
   * @param inputRef Required in all game scenes for input systems
   * @see setCurrentScene() @see SceneFactory()
   */
  explicit SceneManager(ASGE::Renderer& rendererRef, ASGE::Input& inputRef);
  virtual ~SceneManager() = default;

  /**
   * @brief Adds current scene to 'scenes' vector
   * @param scene Scene to add
   */
  void addScene(const std::shared_ptr<Scene>& scene);
  /**
   * @brief Creates all game scenes by looping through 'GameScene' enum
   * @details Calls 'sceneFactory' function and adds return to 'scenes' array
   * after assessing if the return is a nullptr. Sets currentScene to first element
   * in 'scenes' vector.
   */
  void addGameScenes();
  /**
   * @brief Creates instance of game scene and returns its shared ptr
   * @param gameScene GameScene enum value
   * @return Shared ptr of game scene corresponding to enum state passed in
   */
  std::shared_ptr<Scene> sceneFactory(const GameScene& gameScene);

  /**
   * @brief Sets current scene and calls init function within the scene
   * @param scene Scene to call overloaded functions
   */
  void setCurrentScene(const std::shared_ptr<Scene>& scene);
  [[nodiscard]] GameScene getCurrentScene() const;

  void checkCurrentSceneState();
  [[nodiscard]] bool onExit() const { return exitGame; }

  /// Functions called within 'ASGEGame' that calls corresponding function in the current
  /// game scene
  virtual void keyHandler(const ASGE::SharedEventData& data);
  virtual void input();
  virtual void update(const ASGE::GameTime& us);
  virtual void fixedUpdate(const ASGE::GameTime& us);
  virtual void render(const ASGE::GameTime& us);

 protected:
  /// Save a pointer of renderer and input to pass into game scenes
  ASGE::Renderer* renderer;
  ASGE::Input* inputs;
  /// Scene FSM
  std::shared_ptr<Scene> currentScene;
  std::vector<std::shared_ptr<Scene>> scenes;
  SceneStatus currentSceneStatus;
  bool exitGame = false;
};

#endif // ASGEGAME_SCENEMANAGER_H
