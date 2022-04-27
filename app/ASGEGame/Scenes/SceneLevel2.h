#ifndef ASGEGAME_SCENELEVEL2_H
#define ASGEGAME_SCENELEVEL2_H

/// Tile map Libraries
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <vector>

/// Audio
//#include "soloud.h"
//#include "soloud_wav.h"

/// ASGE Sprites
// Bases
#include "Sprites/Entity.h"
#include "Sprites/Sprite.h"
// Enemies
#include "Sprites/Enemy.h"
#include "Sprites/EnemyChaser.h"
#include "Sprites/EnemyPassive.h"
// Player
#include "Sprites/Player.h"
#include "Sprites/PlayerUI.h"
// Players + Enemies
#include "Sprites/Bullet.h"
/// Audio
#include "soloud.h"
#include "soloud_wav.h"

/// Helpers
#include "Components/Helper.h"

/// Base Class
#include "Scene.h"

class SceneLevel2 : public Scene
{
 public:
  SceneLevel2(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene);
  virtual ~SceneLevel2() override = default;

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
  // const ASGE::Font* game_font = nullptr;
  ASGE::Text camera_one_label{};
  ASGE::Text camera_two_label{};

  // some cameras
  ASGE::Camera camera_one{ 1920, 560 };
  ASGE::Camera camera_two{ 1920, 560 };

  /// TILED - TILEMAP VECTORS
  std::vector<std::unique_ptr<ASGE::Sprite>> tilesPastBackground;
  std::vector<std::unique_ptr<ASGE::Sprite>> tilesPresentBackground;
  std::vector<std::unique_ptr<ASGE::Sprite>> PresentTiles;
  std::vector<std::unique_ptr<ASGE::Sprite>> PastTiles;

  // Switching maps initial state
  TimeTravelState state = TimeTravelState::PAST;

  tmx::Map level2map;

  /// Enemies
  std::unique_ptr<EnemyPassive> enemy1 = nullptr;
  std::unique_ptr<EnemyChaser> enemy2  = nullptr;
  std::unique_ptr<EnemyChaser> enemy3  = nullptr;
  std::unique_ptr<EnemyChaser> enemy4  = nullptr;
  std::unique_ptr<EnemyPassive> enemy5 = nullptr;

  std::vector<std::shared_ptr<GameComponent>> gameComponents;
  /// Players
  std::shared_ptr<Player> player1 = nullptr;
  std::shared_ptr<Player> player2 = nullptr;
  ASGE::Point2D player1Look{ 492, 120 };
  ASGE::Point2D player2Look{ 492, 120 };

  SoLoud::Soloud audio_engine;
  SoLoud::Wav background_audio;
  SoLoud::Wav fireAudio;

  /// Health PowerUp
  std::unique_ptr<Sprite> HealthPowerUp = nullptr;

  std::unique_ptr<PlayerUI> UI = nullptr;
};

#endif // ASGEGAME_SCENELEVEL2_H
