#include "ASGEGame.hpp"
#include <Engine/FileIO.hpp>
#include <Engine/Logger.hpp>

/**
 * @brief Initialises the game.
 * Setup your game and initialise the core components.
 * @param settings
 */
ASGENetGame::ASGENetGame(const ASGE::GameSettings& settings) :
  OGLGame(settings), game_font(renderer->loadFont("/data/fonts/machine-gunk.ttf", 42, 5))
{
  renderer->setBaseResolution(1920, 1080, ASGE::Resolution::Policy::MAINTAIN);
  key_callback_id     = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  inputs->use_threads = false;

  //  ship = renderer->createUniqueSprite();
  //  ship->loadTexture("/data/sprites/player_ship.png");
  //
  //  camera_one_label.setFont(*game_font).setString("Camera 1").setPosition({ 0, 55
  //  }).setScale(1.5); camera_two_label.setFont(*game_font).setString("Camera 2").setPosition({
  //  960, 55 }).setScale(1.5);

  initAudio();

  /// TESTING FOR DEFAULT CONSTRUCTORS OF DIFFERENT SPRITE OBJECT CLASSES
  /// @note DELETE OR REMOVE ME WHEN TESTING IS COMPLETE
  //  testSprite = std::make_unique<Sprite>(*renderer);
  //  testEntity = std::make_unique<Entity>(*renderer);
  //  testPlayer = std::make_unique<Player>(*renderer);
}

void ASGENetGame::initAudio()
{
  //  audio_engine.init();
  //  ASGE::FILEIO::File bg_audio_file;
  //  if (bg_audio_file.open("/data/audio/cyberpunk.mp3"))
  //  {
  //    auto buffer = bg_audio_file.read();
  //    auto length = static_cast<unsigned int>(buffer.length);
  //    background_audio.loadMem(buffer.as_unsigned_char(), length, false, false);
  //    background_audio.setLooping(true);
  //    audio_engine.play(background_audio);
  //  }
}

/**
 * Destroys the game.
 */
ASGENetGame::~ASGENetGame()
{
  this->inputs->unregisterCallback(key_callback_id);
  audio_engine.deinit();
}

/**
 * @brief Processes key inputs.
 * This function is added as a callback to handle the game's
 * keyboard input. For this game, calls to this function
 * are not thread safe, so you may alter the game's state
 * but your code needs to designed to prevent data-races.
 *
 * @param data
 * @see KeyEvent
 */
void ASGENetGame::keyHandler(ASGE::SharedEventData data)
{
  const auto* key  = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
}

/**
 * @brief FixedUpdate
 * Calls to this function use the same fixed timestep
 * irrespective of how much time is passed. If you want
 * deterministic behaviour on clients, this is the place
 * to go.
 *
 * https://gamedev.stackexchange.com/questions/1589/when-should-i-use-a-fixed-or-variable-time-step
 * "Use variable timesteps for your fixed steps for physics"
 * @param us
 */
void ASGENetGame::fixedUpdate(const ASGE::GameTime& us)
{
  Game::fixedUpdate(us);
}

/**
 * @brief Updates your game and all it's components.
 * @param us
 */
void ASGENetGame::update(const ASGE::GameTime& us)
{
  //  // process single gamepad
  //  if (auto gamepad = inputs->getGamePad(); gamepad.is_connected)
  //  {
  //    velocity.x = gamepad.axis[ASGE::GAMEPAD::AXIS_LEFT_X] * 500;
  //    velocity.y = gamepad.axis[ASGE::GAMEPAD::AXIS_LEFT_Y] * 500;
  //
  //    if (gamepad_state.contains(gamepad.idx))
  //    {
  //      if (
  //        ((gamepad.buttons[ASGE::GAMEPAD::BUTTON_X]) == 0U) &&
  //        ((gamepad_state.at(gamepad.idx).buttons[ASGE::GAMEPAD::BUTTON_X]) != 0U))
  //      {
  //        Logging::DEBUG("X PRESSED");
  //        velocity.y *= 10;
  //      }
  //    }
  //  }
  //
  //  ship->xPos(static_cast<float>(ship->xPos() + velocity.x * us.deltaInSecs()));
  //  ship->yPos(static_cast<float>(ship->yPos() + velocity.y * us.deltaInSecs()));

  // retrieve all connected gamepads and store their states
  for (auto& gamepad : inputs->getGamePads())
  {
    gamepad_state.insert_or_assign(gamepad.idx, gamepad);
  }
}

/**
 * @brief Render your game and its scenes here.
 * @param us
 */
void ASGENetGame::render(const ASGE::GameTime& /*us*/)
{
  //  // example of split screen. just remove viewports and use
  //  // a single camera if you don't require the use of split screen
  //  renderer->setViewport(ASGE::Viewport{ 0, 0, 960, 1080 });
  //  renderer->setProjectionMatrix(camera_one.getView());
  //  renderer->render(*ship);
  //  renderer->setViewport(ASGE::Viewport{ 960, 0, 960, 1080 });
  //  renderer->setProjectionMatrix(camera_two.getView());
  //  renderer->render(*ship);
  //
  //  // reset the view and don't use a camera, useful for HUD
  //  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 1080 });
  //  renderer->setProjectionMatrix(0, 0, 1920, 1080);
  //  renderer->render(camera_one_label);
  //  renderer->render(camera_two_label);
}
