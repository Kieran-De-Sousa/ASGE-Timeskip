#ifndef ASGEGAME_SCENELEVEL1_H
#define ASGEGAME_SCENELEVEL1_H

/// Tile map Libraries
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include <vector>

/// Base Class
#include "Scene.h"

/// ASGE Sprites
#include "Sprites/Bullet.h"
#include "Sprites/Enemy.h"
#include "Sprites/Entity.h"
#include "Sprites/Player.h"
#include "Sprites/PlayerUI.h"
#include "Sprites/Sprite.h"

/// Helpers
#include "Components/Helper.h"

/// Audio
#include "soloud.h"
#include "soloud_wav.h"

struct ObjRect
{
  float x, y, w, h;
};

enum class TimeTravelState : int
{
  PRESENT = 0,
  PAST    = 1
};

/**
 * @brief Level 1 scene
 * @details
 * @see GameScenes.h
 * @author Kieran
 */
class SceneLevel1 : public Scene
{
 public:
  SceneLevel1(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene);
  virtual ~SceneLevel1() override = default;

  virtual bool init() override;

  virtual void input() override;
  virtual void update(const ASGE::GameTime& us) override;
  virtual void fixedUpdate(const ASGE::GameTime& us) override;
  virtual void render(const ASGE::GameTime& us) override;

  void renderScene(const ASGE::GameTime& us);

  bool loadPastMap();
  bool loadPastBackground();

  bool loadPresentMap();
  bool loadPresentBackground();

  void Camera();
  void DebugInfo();
  void initAudio();

 private:
  // Font
  const ASGE::Font* game_font = nullptr;
  ASGE::Text camera_one_label{};
  ASGE::Text camera_two_label{};

  // some cameras
  ASGE::Camera camera_one{ 1920, 560 };
  ASGE::Camera camera_two{ 1920, 560 };

  /// Players
  std::unique_ptr<Player> player1 = nullptr;
  std::unique_ptr<Player> player2 = nullptr;
  ASGE::Point2D player1Look{ 492, 120 };
  ASGE::Point2D player2Look{ 492, 120 };

  /// Enemies
  std::unique_ptr<Enemy> enemy1 = nullptr;
  std::unique_ptr<Enemy> enemy2 = nullptr;
  std::unique_ptr<Enemy> enemy3 = nullptr;

  int collisions = 0;

  /// Health PowerUp
  std::unique_ptr<Sprite> HealthPowerUp = nullptr;

  /// Bullets
  std::vector<std::unique_ptr<ASGE::Sprite>> bullets;
  std::vector<Vector2> directions;
  int magSize              = 120;
  unsigned int bulletCount = 0;

  /// TILED - TILEMAP VECTORS
  std::vector<std::unique_ptr<ASGE::Sprite>> tilesPastBackground;
  std::vector<std::unique_ptr<ASGE::Sprite>> tilesPresentBackground;
  std::vector<std::unique_ptr<ASGE::Sprite>> PresentTiles;
  std::vector<std::unique_ptr<ASGE::Sprite>> PastTiles;

  // Switching maps initial state
  TimeTravelState state = TimeTravelState::PAST;

  tmx::Map map;

  SoLoud::Soloud audio_engine;
  SoLoud::Wav background_audio;
  SoLoud::Wav fireAudio;

  // ui test shenanigans
  std::unique_ptr<PlayerUI> UI = nullptr;
};

#endif // ASGEGAME_SCENELEVEL1_H
