#include "LevelSelect.h"

bool SceneLevelSelect::init()
{
  gameScene = GameScene::LEVEL_SELECT;
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  game_font = renderer->loadFont("/data/fonts/machine-gunk.ttf", 100, 10);
  Title.setFont(*game_font).setString("TIMESKIP").setPosition({ 350, 500 }).setScale(1.5);

  Level1.setFont(*game_font).setString("LEVEL1 .").setPosition({ 360, 600 }).setScale(0.5);
  Level2.setFont(*game_font).setString("LEVEL2").setPosition({ 360, 700 }).setScale(0.5);
  Back.setFont(*game_font).setString("QUIT").setPosition({ 360, 800 }).setScale(0.5);

  return true;
}

void SceneLevelSelect::keyHandler(ASGE::SharedEventData data)
{
  const auto* key  = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  if (keymap[ASGE::KEYS::KEY_UP] || keymap[ASGE::KEYS::KEY_W])
  {
    switch (state)
    {
      case LevelSelectState::LEVEL1:
        break;
      case LevelSelectState::LEVEL2:
        state = LevelSelectState::LEVEL1;
        break;
      case LevelSelectState::BACK:
        state = LevelSelectState::LEVEL2;
        break;
    }
  }
  else if ((keymap[ASGE::KEYS::KEY_DOWN] || (keymap[ASGE::KEYS::KEY_S])))
  {
    switch (state)
    {
      case LevelSelectState::LEVEL1:
        state = LevelSelectState::LEVEL2;
        break;
      case LevelSelectState::LEVEL2:
        state = LevelSelectState::BACK;
        break;
      case LevelSelectState::BACK:
        break;
    }
  }
  else
  {
    if (keymap[ASGE::KEYS::KEY_ENTER])
    {
    }
  }

  switch (state)
  {
    case LevelSelectState::LEVEL1:
      Level1.setString("LEVEL1 .");
      Level2.setString("LEVEL2");
      Back.setString("BACK");
      break;
    case LevelSelectState::LEVEL2:
      Level1.setString("LEVEL1");
      Level2.setString("LEVEL2 .");
      Back.setString("BACK");
      break;
    case LevelSelectState::BACK:
      Level1.setString("LEVEL1");
      Level2.setString("LEVEL2");
      Back.setString("BACK .");
      break;
  }
}
void SceneLevelSelect::update(const ASGE::GameTime& us) {}

void SceneLevelSelect::fixedUpdate(const ASGE::GameTime& us) {}

void SceneLevelSelect::render(const ASGE::GameTime& us)
{
  renderer->render(Title);
  renderer->render(Level1);
  renderer->render(Level2);
  renderer->render(Back);
}