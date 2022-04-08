//
// Created by aslib on 06/04/2022.
//

#ifndef ASGEGAME_LEVELSELECT_H
#define ASGEGAME_LEVELSELECT_H

/// Tile map Libraries
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include <vector>

/// Base Class
#include "Scene.h"

enum class LevelSelectState : int
{
  LEVEL1 = 0,
  LEVEL2 = 1,
  BACK   = 2
};

class SceneLevelSelect : public Scene
{
 public:
  SceneLevelSelect(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene);
  virtual ~SceneLevelSelect() override = default;

  virtual bool init() override;

  virtual void keyHandler(ASGE::SharedEventData data) override;
  virtual void update(const ASGE::GameTime& us) override;
  virtual void fixedUpdate(const ASGE::GameTime& us) override;
  virtual void render(const ASGE::GameTime& us) override;

  LevelSelectState state = LevelSelectState::LEVEL1;

 private:
  const ASGE::Font* game_font = nullptr;
  ASGE::Text Title{};
  ASGE::Text Level1{};
  ASGE::Text Level2{};
  ASGE::Text Back{};
};

#endif // ASGEGAME_LEVELSELECT_H
