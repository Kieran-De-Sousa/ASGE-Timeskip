//
// Created by ali on 27/04/2022.
//
#ifndef ASGEGAME_WINSCENE_H
#define ASGEGAME_WINSCENE_H

/// Tile map Libraries
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include <vector>

/// Base Class
#include "Scene.h"

enum class WinLevelState : int
{
  MAINMENU = 0,
  QUIT     = 1
};

class WinScene : public Scene
{
 public:
  WinScene(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene);
  virtual ~WinScene() override = default;

  virtual bool init() override;

  virtual void input() override;
  virtual void update(const ASGE::GameTime& us) override;
  virtual void fixedUpdate(const ASGE::GameTime& us) override;
  virtual void render(const ASGE::GameTime& us) override;

 private:
  WinLevelState sceneState = WinLevelState::MAINMENU;

  const ASGE::Font* game_font = nullptr;
  ASGE::Text WinText{};
  ASGE::Text MenuText{};
  ASGE::Text QuitText{};
};

#endif // ASGEGAME_WINSCENE_H
