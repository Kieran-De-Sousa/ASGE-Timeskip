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

  ship = renderer->createUniqueSprite();
  ship->loadTexture("/data/sprites/Black.png");

  renderMap();
  //  camera_one_label.setFont(*game_font).setString("Camera 1").setPosition({ 0, 55
  //  }).setScale(1.5); camera_two_label.setFont(*game_font).setString("Camera 2").setPosition({
  //  960, 55 }).setScale(1.5);
  //
  //  initAudio();

  /// TESTING FOR DEFAULT CONSTRUCTORS OF DIFFERENT SPRITE OBJECT CLASSES
  /// @note DELETE OR REMOVE ME WHEN TESTING IS COMPLETE
  //  testSprite = std::make_unique<Sprite>(*renderer);
  //  testEntity = std::make_unique<Entity>(*renderer);
  //  testPlayer = std::make_unique<Player>(*renderer);
}

// void ASGENetGame::initAudio()
//{
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
//}

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
  // process single gamepad
  if (auto gamepad = inputs->getGamePad(); gamepad.is_connected)
  {
    if (((gamepad.buttons[0]) != 0u) && !gravity && groundCheck)
    {
      j_s = 3.0f;
      g_s = 0;
      Logging::DEBUG("jump");
      newPos      = ship->yPos() - 200;
      jump        = true;
      groundCheck = false;
    }
    if (abs(gamepad.axis[0]) > 0.1)
    {
      ship->xPos(ship->xPos() + 5 * gamepad.axis[0]);
    }
  }

  if (keymap[ASGE::KEYS::KEY_A])
  {
    ship->xPos(ship->xPos() - 5);
  }
  if (keymap[ASGE::KEYS::KEY_D])
  {
    ship->xPos(ship->xPos() + 5);
  }
  if (keymap[ASGE::KEYS::KEY_A])
  {
    ship->xPos(ship->xPos() - 5);
  }
  if (keymap[ASGE::KEYS::KEY_D])
  {
    ship->xPos(ship->xPos() + 5);
  }
  if (keymap[ASGE::KEYS::KEY_W] && !gravity && groundCheck)
  {
    j_s = 3.0f;
    g_s = 0;
    Logging::DEBUG("jump");
    newPos = ship->yPos() - 200;
    jump   = true;
  }
  if (keymap[ASGE::KEYS::KEY_S])
  {
    ship->yPos(ship->yPos() + 5);
  }
  if ((ship->yPos()) > 640 - ship->height())
  {
    groundCheck = true;
    ship->yPos(640 - ship->height());
    hasPeaked = false;
    gravity   = false;
  }
  if (gravity)
  {
    g_s += 0.3f;
    ship->yPos(ship->yPos() + g_s);
  }
  if (jump && !gravity)
  {
    j_s += 3.0f;
    j_s -= 0.3f;
    ship->yPos(ship->yPos() - j_s);
    if (ship->yPos() < newPos)
    {
      jump      = false;
      hasPeaked = true;
    }
  }
  if (hasPeaked)
  {
    g_s += 0.3f;
    ship->yPos(ship->yPos() + g_s);
  }
}
//  ship->xPos(static_cast<float>(ship->xPos() + velocity.x * us.deltaInSecs()));
//  ship->yPos(static_cast<float>(ship->yPos() + velocity.y * us.deltaInSecs()));

/**
 * @brief Render your game and its scenes here.
 * @param us
 */
void ASGENetGame::render(const ASGE::GameTime& /*us*/)
{
  // example of split screen. just remove viewports and use
  // a single camera if you don't require the use of split screen
  // renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 1080 });
  // renderer->setProjectionMatrix(camera_one.getView());
  for (unsigned int i = 0; i < tiles.size(); ++i)
  {
    renderer->render(*tiles[i]);
    // Logging::DEBUG("rendering tiles");
  }
  renderer->render(*ship);
  //  renderer->setViewport(ASGE::Viewport{ 960, 0, 960, 1080 });
  //  renderer->setProjectionMatrix(camera_two.getView());
  //  renderer->render(*ship);

  // reset the view and don't use a camera, useful for HUD
  //  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 1080 });
  //  renderer->setProjectionMatrix(0, 0, 1920, 1080);
  //  renderer->render(camera_one_label);
  //  renderer->render(camera_two_label);

  // renderer->render(*testPlayer->getSprite());
}
void ASGENetGame::renderMap()
{
  for (unsigned int i = 0; i < 100; ++i)
  {
    tiles.emplace_back(renderer->createUniqueSprite());
    if (tiles[i]->loadTexture("data/sprites/Black.png"))
    {
      // Logging::DEBUG("loaded tile");
      tiles[i]->width(32);
      tiles[i]->height(32);
      tiles[i]->xPos(tiles[i]->width() * static_cast<float>(i));
      tiles[i]->yPos(640);
      tiles[i]->setGlobalZOrder(3);
    }
  }
}
