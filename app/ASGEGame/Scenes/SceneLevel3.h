#ifndef ASGEGAME_SCENELEVEL3_H
#define ASGEGAME_SCENELEVEL3_H

/// Tile map Libraries
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include <vector>

/// Base Class
#include "Scene.h"

/// ASGE Sprites
#include "Sprites/Bullet.h"
#include "Sprites/Enemy.h"
#include "Sprites/EnemyChaser.h"
#include "Sprites/EnemyPassive.h"
#include "Sprites/Entity.h"
#include "Sprites/Player.h"
#include "Sprites/PlayerUI.h"
#include "Sprites/Sprite.h"

/// Helpers
#include "Components/Helper.h"

/// Audio
#include "soloud.h"
#include "soloud_wav.h"

/**
 * @brief Level 3 scene
 * @details
 * @see GameScenes.h
 */
class SceneLevel3 : public Scene
{
 public:
  SceneLevel3(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene);
  virtual ~SceneLevel3() override = default;

  virtual bool init() override;

  virtual void input() override;
  virtual void update(const ASGE::GameTime& us) override;
  virtual void fixedUpdate(const ASGE::GameTime& us) override;
  virtual void render(const ASGE::GameTime& us) override;

  void updatePlayers(const ASGE::GameTime& us, Player* player);
  void updateCamera(const ASGE::GameTime& us);

  void renderScene(const ASGE::GameTime& us);

  /// Map loading
  bool loadPastMap();
  bool loadPresentMap();

  void DebugInfo();
  void initAudio();

 private:
  // Font
  ASGE::Text camera_one_label{};
  ASGE::Text camera_two_label{};

  // some cameras
  ASGE::Camera camera_one{ 1920, 560 };
  ASGE::Camera camera_two{ 1920, 560 };

  /// Container
  std::vector<std::shared_ptr<GameComponent>> gameComponents;

  /// Players
  std::shared_ptr<Player> player1 = nullptr;
  std::shared_ptr<Player> player2 = nullptr;
  ASGE::Point2D player1Look{ 492, 120 };
  ASGE::Point2D player2Look{ 492, 120 };

  /// Enemies
  std::shared_ptr<EnemyPassive> enemy1 = nullptr;
  std::shared_ptr<EnemyChaser> enemy2  = nullptr;
  std::shared_ptr<EnemyChaser> enemy3  = nullptr;
  std::shared_ptr<EnemyPassive> enemy4 = nullptr;

  std::unique_ptr<EnemyPassive> enemy5 = nullptr;
  std::unique_ptr<EnemyChaser> enemy6  = nullptr;
  std::unique_ptr<EnemyChaser> enemy7  = nullptr;
  std::unique_ptr<EnemyPassive> enemy8 = nullptr;

  /// Health PowerUp
  std::shared_ptr<Sprite> HealthPowerUp = nullptr;

  /// UI
  std::shared_ptr<PlayerUI> UI = nullptr;

  /// TILED - TILEMAP VECTORS
  std::vector<std::unique_ptr<ASGE::Sprite>> tilesPastBackground;
  std::vector<std::unique_ptr<ASGE::Sprite>> tilesPresentBackground;
  std::vector<std::unique_ptr<ASGE::Sprite>> PresentTiles;
  std::vector<std::unique_ptr<ASGE::Sprite>> PastTiles;

  std::vector<std::shared_ptr<ASGE::Sprite>> currentTileState;

  tmx::Vector2<float> pastSpawnPos;
  tmx::Vector2<float> pastExitPos;
  tmx::Vector2<float> presentSpawnPos;
  tmx::Vector2<float> presentExitPos;

  tmx::Vector2<float> pastEnemy1Pos;
  tmx::Vector2<float> pastEnemy2Pos;
  tmx::Vector2<float> pastEnemy3Pos;
  tmx::Vector2<float> pastEnemy4Pos;

  tmx::Vector2<float> presentEnemy1Pos;
  tmx::Vector2<float> presentEnemy2Pos;
  tmx::Vector2<float> presentEnemy3Pos;
  tmx::Vector2<float> presentEnemy4Pos;

  // Switching maps initial state
  TimeTravelState state = TimeTravelState::PAST;

  tmx::Map map;

  /// Audio
  SoLoud::Soloud audio_engine;
  SoLoud::Wav background_audio;
  SoLoud::Wav fireAudio;
<<<<<<< Updated upstream

  /// UI
  std::shared_ptr<PlayerUI> UI = nullptr;

  /// Container
  std::vector<std::shared_ptr<GameComponent>> gameComponents;
  == == == =
>>>>>>> Stashed changes
};

#endif // ASGEGAME_SCENELEVEL3_H
