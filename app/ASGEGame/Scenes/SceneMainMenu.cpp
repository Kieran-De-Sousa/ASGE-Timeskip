#include "SceneMainMenu.h"

SceneMainMenu::SceneMainMenu(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene) :
  Scene(rendererRef, inputRef, scene)
{
}

bool SceneMainMenu::init()
{
  setDefaultSceneStatus();

  renderer->setClearColour(ASGE::COLOURS::BLACK);
  game_font = renderer->loadFont("/data/fonts/Contra.ttf", 100, 10);
  Title.setFont(*game_font).setString("TIMESKIP").setPosition({ 350, 500 }).setScale(1.5);

  Play.setFont(*game_font).setString(">> PLAY").setPosition({ 360, 600 }).setScale(0.5);
  LevelSelect.setFont(*game_font).setString("LEVEL SELECT").setPosition({ 360, 700 }).setScale(0.5);
  Quit.setFont(*game_font).setString("QUIT").setPosition({ 360, 800 }).setScale(0.5);

  return true;
}

/**
 * @note Slight refactor to reduce state machine checks - Kieran
 */
void SceneMainMenu::keyHandler(ASGE::SharedEventData data)
{
  const auto* key  = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  if (keymap[ASGE::KEYS::KEY_UP] || keymap[ASGE::KEYS::KEY_W])
  {
    state = (int(state) - 1 > int(MenuState::PLAY)) ? MenuState(int(state) - 1) : MenuState::PLAY;
  }
  else if (keymap[ASGE::KEYS::KEY_DOWN] || keymap[ASGE::KEYS::KEY_S])
  {
    state = (int(state) + 1 < int(MenuState::QUIT)) ? MenuState(int(state) + 1) : MenuState::QUIT;
  }
  else
  {
    if (keymap[ASGE::KEYS::KEY_ENTER])
    {
      switch (state)
      {
        case MenuState::PLAY:
          setNewScene(GameScene::LEVEL_1);
          break;
        case MenuState::LEVELSELECT:
          setNewScene(GameScene::LEVEL_SELECT);
          break;
        case MenuState::QUIT:
          sceneStatus.exit_game = true;
          break;
      }
    }
  }

  switch (state)
  {
    case MenuState::PLAY:
      Play.setString(">> PLAY");
      LevelSelect.setString("LEVEL SELECT");
      Quit.setString("QUIT");
      break;
    case MenuState::LEVELSELECT:
      Play.setString("PLAY");
      LevelSelect.setString(">> LEVEL SELECT");
      Quit.setString("QUIT");
      break;
    case MenuState::QUIT:
      Play.setString("PLAY");
      LevelSelect.setString("LEVEL SELECT");
      Quit.setString(">> QUIT");
      break;
  }
}

void SceneMainMenu::update(const ASGE::GameTime& us) {}

void SceneMainMenu::fixedUpdate(const ASGE::GameTime& us) {}

void SceneMainMenu::render(const ASGE::GameTime& us)
{
  renderer->render(Title);
  renderer->render(Play);
  renderer->render(LevelSelect);
  renderer->render(Quit);
}