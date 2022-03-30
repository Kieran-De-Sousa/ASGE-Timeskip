#pragma once

#include <Engine/Gamepad.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>
#include <map>

#include <soloud.h>
#include <soloud_wav.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "Entity.h"
#include "Player.h"
#include "Sprite.h"

#define MAINMENU
#define PAUSE
#define NEXTLEVEL
#define WIN
#define LOSE

struct ObjRect
{
  //object rectangle

  float x, y, w, h;
};

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
  void renderMap();
  void Camera();

 private:
  SoLoud::Soloud audio_engine;
  SoLoud::Wav background_audio;
  std::string key_callback_id{}; /**< Key Input Callback ID. */
  std::map<int, bool> keymap{};
  std::map<int, ASGE::GamePadData> gamepad_state{};
  std::unique_ptr<ASGE::Sprite> ship{ nullptr };
  std::unique_ptr<ASGE::Sprite> ship2{ nullptr };
  ASGE::Point2D velocity{ 0, 0 };

  // Font
  const ASGE::Font* game_font = nullptr;
  ASGE::Text camera_one_label{};
  ASGE::Text camera_two_label{};

  // some cameras
  ASGE::Camera camera_one{ 1920, 560 };
  ASGE::Camera camera_two{ 1920, 560 };
  void initAudio();

  ASGE::Point2D ship_look{ 0, 120 };
  ASGE::Point2D ship2_look{ 0, 120 };

  /// TESTING FOR DEFAULT CONSTRUCTORS OF DIFFERENT SPRITE OBJECT CLASSES
  /// @note DELETE OR REMOVE ME WHEN TESTING IS COMPLETE
  std::unique_ptr<Sprite> testSprite;
  std::unique_ptr<Entity> testEntity;
  std::unique_ptr<Player> testPlayer;

  std::unique_ptr<Entity> player1;

  //  /// TILED - TILEMAP VECTORS
  std::vector<std::unique_ptr<ASGE::Sprite>> tiles;
  //  std::vector<std::unique_ptr<ASGE::Sprite>> collidables;
  //  tmx::Map map;
  bool gravity     = true;
  bool hasPeaked   = false;
  bool jump        = false;
  bool groundCheck = false;
  float newPos     = 0;
  float g_s = 0, j_s = 0;
  unsigned long long width = 16, height = 10;
  std::vector<int> testMap = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  };

  bool gravity2     = true;
  bool hasPeaked2   = false;
  bool jump2        = false;
  bool groundCheck2 = false;
  float newPos2     = 0;
  float g_s2 = 0, j_s2 = 0;

  //Animation stuff
  ObjRect animation_frames[5];
  int animation_index1 = 0;
  int animation_index2 = 0;
  const float ANIMATION_FRAME_RATE = 0.1f;
  float animation_timer = 0.0f;

  int player1State = IDLE;
  int player2State = IDLE;
};
