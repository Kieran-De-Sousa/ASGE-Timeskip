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
#include "TileRect.h"
#include <chrono>

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
  std::unique_ptr<ASGE::Sprite> player;
  std::unique_ptr<ASGE::Sprite> floor;

  // Font
  const ASGE::Font* game_font = nullptr;
  ASGE::Text camera_one_label{};
  ASGE::Text camera_two_label{};

  // some cameras
  ASGE::Camera camera_one{ 1920, 1080 };
  ASGE::Camera camera_two{ 960, 1080 };

  ASGE::Point2D focus{};

  tmx::Map map;
  std::vector<std::unique_ptr<ASGE::Sprite>> tiles;

  void initAudio();
  void loadTiles();
  void renderTileMap();
  void resolveCollision();
  void raycastControl();
  void drawRaycast();

  std::array<float, 1920> view_rays;

  /// TESTING FOR DEFAULT CONSTRUCTORS OF DIFFERENT SPRITE OBJECT CLASSES
  /// @note DELETE OR REMOVE ME WHEN TESTING IS COMPLETE
  std::unique_ptr<Sprite> testSprite;
  std::unique_ptr<Entity> testEntity;
  std::unique_ptr<Player> testPlayer;

  //  /// TILED - TILEMAP VECTORS
  //  std::vector<std::unique_ptr<ASGE::Sprite>> tiles;
  //  std::vector<std::unique_ptr<ASGE::Sprite>> collidables;
  //  tmx::Map map;
};
