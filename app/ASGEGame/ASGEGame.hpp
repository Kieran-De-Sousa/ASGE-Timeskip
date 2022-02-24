#pragma once

#include <Engine/Gamepad.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>
#include <map>
#include <soloud.h>
#include <soloud_wav.h>

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
  SoLoud::Soloud audio_engine;
  SoLoud::Wav background_audio;
  std::string key_callback_id{}; /**< Key Input Callback ID. */
  std::map<int, bool> keymap{};
  std::map<int, ASGE::GamePadData> gamepad_state{};
  std::unique_ptr<ASGE::Sprite> ship{ nullptr };
  ASGE::Point2D velocity{ 0, 0 };

  // Font
  const ASGE::Font* game_font = nullptr;
  ASGE::Text camera_one_label{};
  ASGE::Text camera_two_label{};

  // some cameras
  ASGE::Camera camera_one{ 960, 1080 };
  ASGE::Camera camera_two{ 960, 1080 };
  void initAudio();
};
