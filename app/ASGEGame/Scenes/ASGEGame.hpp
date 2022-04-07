#pragma once

/// Game Engine
#include <Engine/Gamepad.hpp>
#include <Engine/OGLGame.hpp>

/// TODO: Audio engine incorporation into scene handler
#include <soloud.h>
#include <soloud_wav.h>

/// Game Screen FSM
#include "Managers/SceneManager.h"
#include "Scenes/LevelSelect.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneLevel1.h"
#include "Scenes/SceneMainMenu.h"

class ASGENetGame : public ASGE::OGLGame
{
 public:
  explicit ASGENetGame(const ASGE::GameSettings& settings);
  ~ASGENetGame() override;

  ASGENetGame(const ASGENetGame&) = delete;
  ASGENetGame& operator=(const ASGENetGame&) = delete;

  void keyHandler(ASGE::SharedEventData data);
  void update(const ASGE::GameTime& us) override;
  void render(const ASGE::GameTime& us) override;
  void fixedUpdate(const ASGE::GameTime& us) override;

 private:
  /// Game state manager
  std::unique_ptr<SceneManager> scene_manager;

  /// TODO: Audio engine incorporation into scene handler
  void initAudio();
  SoLoud::Soloud audio_engine;
  SoLoud::Wav background_audio;

  /// Required for signal exit of game
  std::string key_callback_id{}; /**< Key Input Callback ID. */
  std::map<int, bool> keymap{};
  std::map<int, ASGE::GamePadData> gamepad_state{};
};
