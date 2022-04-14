#ifndef ASGEGAME_SCENELEVEL1_H
#define ASGEGAME_SCENELEVEL1_H

/// Tile map Libraries
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include <vector>

/// Base Class
#include "Scene.h"

/// ASGE Sprites
#include "Sprites/Entity.h"
#include "Sprites/Player.h"
#include "Sprites/Sprite.h"

/**
 * @brief Level 1 scene
 * @details
 * @see GameScenes.h
 * @author Kieran
 */

class SceneLevel1 : public Scene
{
 public:
  SceneLevel1(ASGE::Renderer& rendererRef, ASGE::Input& inputRef) : Scene(rendererRef, inputRef) {}
  virtual ~SceneLevel1() override = default;

  virtual bool init() override;

  virtual void keyHandler(ASGE::SharedEventData data) override;
  virtual void update(const ASGE::GameTime& us) override;
  virtual void fixedUpdate(const ASGE::GameTime& us) override;
  virtual void render(const ASGE::GameTime& us) override;

  bool renderMap();
  bool renderBackground();
  void Camera();
  void DebugInfo();

 private:
  // Players
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

  ASGE::Point2D ship_look{ 492, 120 };
  ASGE::Point2D ship2_look{ 492, 120 };

  /// TESTING FOR DEFAULT CONSTRUCTORS OF DIFFERENT SPRITE OBJECT CLASSES
  /// @note DELETE OR REMOVE ME WHEN TESTING IS COMPLETE
  std::unique_ptr<Sprite> testSprite;
  std::unique_ptr<Entity> testEntity;
  std::unique_ptr<Player> testPlayer;

  std::unique_ptr<Entity> player1;

  //  /// TILED - TILEMAP VECTORS
  std::vector<std::unique_ptr<ASGE::Sprite>> tiles;
  std::vector<std::unique_ptr<ASGE::Sprite>> tilesB;
  std::vector<std::unique_ptr<ASGE::Sprite>> bullets;
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
  tmx::Map map;
  int magSize              = 120;
  unsigned int bulletCount = 0;
  std::unique_ptr<ASGE::Sprite> playerIcon{ nullptr };

  // joey UI stuff
  float p1_health_val = 100;
  float p2_health_val = 100;
  std::unique_ptr<ASGE::Sprite> p1_health_bar;
  std::unique_ptr<ASGE::Sprite> p2_health_bar;
};

#endif // ASGEGAME_SCENELEVEL1_H
