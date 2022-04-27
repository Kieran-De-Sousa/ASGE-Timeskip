//
// Created by ali on 27/04/2022.
//

#include "WinScene.h"

WinScene::WinScene(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene) :
  Scene(rendererRef, inputRef, scene)
{
}

bool WinScene::init()
{
  setDefaultSceneStatus();
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  game_font = renderer->loadFont("/data/fonts/Contra.ttf", 45, 10);
  WinText.setFont(*game_font)
    .setString("Congratulations! \nYou fixed the timeline")
    .setPosition({ 350, 350 })
    .setScale(1.5);

  MenuText.setFont(*game_font).setString(">> Main Menu").setPosition({ 360, 600 }).setScale(0.5);
  QuitText.setFont(*game_font).setString("QUIT").setPosition({ 360, 700 }).setScale(0.5);

  return true;
}

void WinScene::input()
{
  if (keymap[ASGE::KEYS::KEY_UP] || keymap[ASGE::KEYS::KEY_W])
  {
    switch (sceneState)
    {
      case WinLevelState::MAINMENU:
        break;
      case WinLevelState::QUIT:
        sceneState = WinLevelState::MAINMENU;
        break;
    }
  }
  else if ((keymap[ASGE::KEYS::KEY_DOWN] || (keymap[ASGE::KEYS::KEY_S])))
  {
    switch (sceneState)
    {
      case WinLevelState::MAINMENU:
        sceneState = WinLevelState::QUIT;
        break;
      case WinLevelState::QUIT:
        break;
    }
  }
  else
  {
    if (keymap[ASGE::KEYS::KEY_ENTER])
    {
      switch (sceneState)
      {
        case WinLevelState::MAINMENU:
          setNewScene(GameScene::MAIN_MENU);
          break;
        case WinLevelState::QUIT:
          sceneStatus.exit_game = true;
          break;
      }
    }
  }

  switch (sceneState)
  {
    case WinLevelState::MAINMENU:
      MenuText.setString(">> Main Menu");
      QuitText.setString("Quit");
      break;
    case WinLevelState::QUIT:
      MenuText.setString("Main Menu");
      QuitText.setString(">> Quit");
      break;
  }
}

void WinScene::update(const ASGE::GameTime& us) {}

void WinScene::fixedUpdate(const ASGE::GameTime& us) {}

void WinScene::render(const ASGE::GameTime& us)
{
  renderer->render(WinText);
  renderer->render(MenuText);
  renderer->render(QuitText);
}