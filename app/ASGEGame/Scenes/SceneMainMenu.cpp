#include "SceneMainMenu.h"

bool SceneMainMenu::init()
{
  gameScene = GameScene::MAIN_MENU;
  game_font = renderer->loadFont("/data/fonts/machine-gunk.ttf", 42, 5);
  camera_one_label.setFont(*game_font).setString("Camera 1").setPosition({ 0, 55 }).setScale(1.5);

  return true;
}

void SceneMainMenu::keyHandler(ASGE::SharedEventData data) {}

void SceneMainMenu::update(const ASGE::GameTime& us) {}

void SceneMainMenu::fixedUpdate(const ASGE::GameTime& us) {}

void SceneMainMenu::render(const ASGE::GameTime& us)
{
  renderer->render(camera_one_label);
}