#ifndef ASGEGAME_SCENE_H
#define ASGEGAME_SCENE_H

/// Game Engine
#include <Engine/FileIO.hpp>
#include <Engine/Gamepad.hpp>
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

/// Input System
#include <map>

/// Possibly unneeded
#include <memory>

/// State Tracking
#include "GameScenes.h"

/**
 * @brief Pure virtual scene class
 * @details All scenes required for game should inherit this class as a base class
 * @author Kieran
 */
class Scene : public std::enable_shared_from_this<Scene>
{
 public:
  /**
   * @brief Default constructor
   * @details Renderer and input of OGLGame stored in protected member and is accessible in derived
   * classes
   * @param rendererRef Required in all game scenes for rendering
   */
  Scene(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene);
  virtual ~Scene() = default;

  Scene(const Scene&) = delete;
  Scene& operator=(const Scene&) = delete;

  /// SETTER & GETTER FUNCTIONS
  // Scene Status
  void setDefaultSceneStatus();
  virtual SceneStatus getSceneStatus() const;
  // Game Scene
  [[nodiscard]] virtual GameScene getScene() const;
  void setNewScene(const GameScene& game_scene);

  /// Base virtual functions overridden in scene derived classes
  virtual bool init()                                 = 0;
  virtual void keyHandler(ASGE::SharedEventData data) = 0;
  virtual void update(const ASGE::GameTime& us)       = 0;
  virtual void fixedUpdate(const ASGE::GameTime& us)  = 0;
  virtual void render(const ASGE::GameTime& us)       = 0;

 protected:
  /// Save a pointer of renderer and input to pass into game scenes
  std::unique_ptr<ASGE::Renderer> renderer;
  std::unique_ptr<ASGE::Input> inputs;

  /// Input System
  std::string key_callback_id{}; /**< Key Input Callback ID. */
  std::map<int, bool> keymap{};
  std::map<int, ASGE::GamePadData> gamepad_state{};

  /// Scene State Data
  SceneStatus sceneStatus;
  const SceneStatus DEFAULT_SCENE_STATUS;
};

#endif // ASGEGAME_SCENE_H