#ifndef ASGEGAME_SCENE_H
#define ASGEGAME_SCENE_H

/// Game Engine
#include <Engine/FileIO.hpp>
#include <Engine/Gamepad.hpp>
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

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
   * @details Renderer of OGLGame stored in protected member and is accessible in derived classes
   * @param rendererRef Required in all game scenes for rendering
   */
  explicit Scene(ASGE::Renderer& rendererRef) : renderer(&rendererRef) {}
  virtual ~Scene() = default;

  Scene(const Scene&) = delete;
  Scene& operator=(const Scene&) = delete;

  /// Base virtual functions overridden in scene derived classes
  virtual bool init()                                 = 0;
  virtual void keyHandler(ASGE::SharedEventData data) = 0;
  virtual void update(const ASGE::GameTime& us)       = 0;
  virtual void fixedUpdate(const ASGE::GameTime& us)  = 0;
  virtual void render(const ASGE::GameTime& us)       = 0;

 protected:
  std::unique_ptr<ASGE::Renderer> renderer;
  /// Game State
  GameScene gameScene = GameScene::UNDEFINED;
  /// TODO: Handle key stuff more effectively
  // std::string key_callback_id{}; /**< Key Input Callback ID. */
};

#endif // ASGEGAME_SCENE_H