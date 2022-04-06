#ifndef ASGEGAME_SCENEMAINMENU_H
#define ASGEGAME_SCENEMAINMENU_H

/// Tile map Libraries
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include <vector>

/// Base Class
#include "Scene.h"

/**
 * @brief Main menu scene
 * @details Currently first scene loaded for game
 * @see GameScenes.h
 * @author Kieran
 */
class SceneMainMenu : public Scene
{
 public:
  SceneMainMenu(ASGE::Renderer& rendererRef, ASGE::Input& inputRef) : Scene(rendererRef, inputRef)
  {
  }
  virtual ~SceneMainMenu() override = default;

  virtual bool init() override;

  virtual void keyHandler(ASGE::SharedEventData data) override;
  virtual void update(const ASGE::GameTime& us) override;
  virtual void fixedUpdate(const ASGE::GameTime& us) override;
  virtual void render(const ASGE::GameTime& us) override;

 private:
  const ASGE::Font* game_font = nullptr;
  ASGE::Text camera_one_label{};
};

#endif // ASGEGAME_SCENEMAINMENU_H