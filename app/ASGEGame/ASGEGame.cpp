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

  /*
  std::string path = "/data/sprites/player1.png";

  if(testPlayer->initialiseSprite(path) == true)
  {
    testPlayer->setPosition(256, 128);
    testPlayer->setSpriteVariables(64, 64, 0);
  }
  else
  {
    printf("problem\n");
  }
  */

  // running animation
  ship = renderer->createUniqueSprite();
  ship->loadTexture("/data/sprites/Player1Animation.png");
  ship->width(64);
  ship->height(64);
  ship->xPos(256);
  ship->yPos(128);

  ship->srcRect()[0] = 0;
  ship->srcRect()[1] = 0;
  ship->srcRect()[2] = 32;
  ship->srcRect()[3] = 32;

  ship->setGlobalZOrder(2);
  ship->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);

  // running animation
  ship2 = renderer->createUniqueSprite();
  ship2->loadTexture("/data/sprites/Player2Animation.png");
  ship2->width(64);
  ship2->height(64);
  ship2->xPos(256);
  ship2->yPos(128);

  ship2->srcRect()[0] = 0;
  ship2->srcRect()[1] = 0;
  ship2->srcRect()[2] = 32;
  ship2->srcRect()[3] = 32;

  ship2->setGlobalZOrder(2);
  ship2->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);

  renderMap();
  Camera();
  camera_two.lookAt({ ship->xPos(), ship->yPos() + 100 });
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
  //  std::cout << testTimer->getTimerStatus();
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

      player1State = JUMPING;
    }
    if (abs(gamepad.axis[0]) > 0.1)
    {
      ship->xPos(ship->xPos() + 5 * gamepad.axis[0]);
    }
  }

  player1State = IDLE;
  player2State = IDLE;

  if (keymap[ASGE::KEYS::KEY_A])
  {
    ship->xPos(ship->xPos() - 5);
    player1State = RUNNING;
    ship->setFlipFlags(ASGE::Sprite::FLIP_X);
  }
  if (keymap[ASGE::KEYS::KEY_D])
  {
    ship->xPos(ship->xPos() + 5);
    player1State = RUNNING;
    ship->setFlipFlags(ASGE::Sprite::NORMAL);
  }
  if (keymap[ASGE::KEYS::KEY_W])
  {
    // Logging::DEBUG("jump");
    jump = true;
    // groundCheck = false;
    j_s = 3.0f;
    g_s = 0;
    Logging::DEBUG("jump");
    newPos = ship->yPos() - 200;
    jump   = true;

    player1State = JUMPING;
  }
  //  if (keymap[ASGE::KEYS::KEY_S])
  //  {
  //    ship->yPos(ship->yPos() + 5);
  //  }
  if (keymap[ASGE::KEYS::KEY_LEFT])
  {
    ship2->xPos(ship2->xPos() - 5);
    player2State = RUNNING;
    ship2->setFlipFlags(ASGE::Sprite::FLIP_X);
  }
  if (keymap[ASGE::KEYS::KEY_RIGHT])
  {
    ship2->xPos(ship2->xPos() + 5);
    player2State = RUNNING;
    ship2->setFlipFlags(ASGE::Sprite::NORMAL);
  }
  if (keymap[ASGE::KEYS::KEY_UP])
  {
    jump2 = true;
    // groundCheck2 = false;
    j_s2 = 3.0f;
    g_s2 = 0;
    Logging::DEBUG("jump");
    newPos2 = ship2->yPos() - 200;
    jump2   = true;

    player2State = JUMPING;
  }

  if (gravity)
  {
    j_s = 7.0f;
    j_s -= 0.3f;
    ship->yPos(ship->yPos() - j_s);
    if (ship->yPos() < newPos)
    {
      jump      = false;
      hasPeaked = true;
    }
  }
  if ((!groundCheck || hasPeaked) && !jump)
  {
    ship->yPos(ship->yPos() + 10);
  }
  for (unsigned long long i = 0; i < tiles.size(); i++)
  {
    if (ship->xPos() >= tiles[i]->xPos() && ship->xPos() <= tiles[i]->xPos() + tiles[i]->width())
    {
      if (
        ship->yPos() + ship->height() >= tiles[i]->yPos() &&
        ship->yPos() + ship->height() <= tiles[i]->yPos() + tiles[i]->height())
      {
        groundCheck = true;
        ship->yPos(tiles[i]->yPos() - ship->height());
      }
      if (
        ship->yPos() < tiles[i]->yPos() + tiles[i]->height() &&
        ship->yPos() + ship->height() > tiles[i]->yPos() + tiles[i]->height())
      {
        jump      = false;
        hasPeaked = true;
      }
    }
    if (
      ship->xPos() + ship->width() >= tiles[i]->xPos() &&
      ship->xPos() + ship->width() <= tiles[i]->xPos() + tiles[i]->width())
    {
      if (
        ship->yPos() + ship->height() >= tiles[i]->yPos() &&
        ship->yPos() + ship->height() <= tiles[i]->yPos() + tiles[i]->height())
      {
        groundCheck = true;
        ship->yPos(tiles[i]->yPos() - ship->height());
      }
      if (
        ship->yPos() < tiles[i]->yPos() + tiles[i]->height() &&
        ship->yPos() + ship->height() > tiles[i]->yPos() + tiles[i]->height())
      {
        jump      = false;
        hasPeaked = true;
      }
    }
    if (ship->yPos() >= tiles[i]->yPos() && ship->yPos() <= tiles[i]->yPos() + tiles[i]->height())
    {
      if (ship->xPos() < tiles[i]->xPos() + tiles[i]->width() && ship->xPos() > tiles[i]->xPos())
      {
        ship->xPos(tiles[i]->xPos() + tiles[i]->width());
      }
    }
    if (
      ship->yPos() + ship->height() >= tiles[i]->yPos() + tiles[i]->height() &&
      ship->yPos() + ship->height() <= tiles[i]->yPos() + tiles[i]->height())
    {
      if (ship->xPos() < tiles[i]->xPos() + tiles[i]->width() && ship->xPos() > tiles[i]->xPos())
      {
        ship->xPos(tiles[i]->xPos() + tiles[i]->width());
      }
    }
    if (ship->yPos() >= tiles[i]->yPos() && ship->yPos() <= tiles[i]->yPos() + tiles[i]->height())
    {
      if (
        ship->xPos() + ship->width() > tiles[i]->xPos() &&
        ship->xPos() + ship->width() < tiles[i]->xPos() + tiles[i]->width())
      {
        ship->xPos(tiles[i]->xPos() - ship->width());
      }
    }
    if (
      ship->yPos() + ship->height() >= tiles[i]->yPos() + tiles[i]->height() &&
      ship->yPos() + ship->height() <= tiles[i]->yPos() + tiles[i]->height())
    {
      if (
        ship->xPos() + ship->width() > tiles[i]->xPos() &&
        ship->xPos() + ship->width() < tiles[i]->xPos() + tiles[i]->width())
      {
        ship->xPos(tiles[i]->xPos() - ship->width());
      }
    }
  }

  /// ship 2 logic
  for (unsigned long long i = 0; i < tiles.size(); i++)
  {
    if (ship2->xPos() >= tiles[i]->xPos() && ship2->xPos() <= tiles[i]->xPos() + tiles[i]->width())
    {
      if (
        ship2->yPos() + ship2->height() >= tiles[i]->yPos() &&
        ship2->yPos() + ship2->height() <= tiles[i]->yPos() + tiles[i]->height())
      {
        groundCheck2 = true;
        ship2->yPos(tiles[i]->yPos() - ship2->height());
      }
      if (
        ship2->yPos() < tiles[i]->yPos() + tiles[i]->height() &&
        ship2->yPos() + ship2->height() > tiles[i]->yPos() + tiles[i]->height())
      {
        jump2      = false;
        hasPeaked2 = true;
      }
    }
    if (
      ship2->xPos() + ship2->width() >= tiles[i]->xPos() &&
      ship2->xPos() + ship2->width() <= tiles[i]->xPos() + tiles[i]->width())
    {
      if (
        ship2->yPos() + ship2->height() >= tiles[i]->yPos() &&
        ship2->yPos() + ship2->height() <= tiles[i]->yPos() + tiles[i]->height())
      {
        groundCheck2 = true;
        ship2->yPos(tiles[i]->yPos() - ship2->height());
      }
      if (
        ship2->yPos() < tiles[i]->yPos() + tiles[i]->height() &&
        ship2->yPos() + ship2->height() > tiles[i]->yPos() + tiles[i]->height())
      {
        jump2      = false;
        hasPeaked2 = true;
      }
    }
    if (ship2->yPos() >= tiles[i]->yPos() && ship2->yPos() <= tiles[i]->yPos() + tiles[i]->height())
    {
      if (ship2->xPos() < tiles[i]->xPos() + tiles[i]->width() && ship2->xPos() > tiles[i]->xPos())
      {
        ship2->xPos(tiles[i]->xPos() + tiles[i]->width());
      }
    }
    if (
      ship2->yPos() + ship2->height() >= tiles[i]->yPos() + tiles[i]->height() &&
      ship2->yPos() + ship2->height() <= tiles[i]->yPos() + tiles[i]->height())
    {
      if (ship2->xPos() < tiles[i]->xPos() + tiles[i]->width() && ship2->xPos() > tiles[i]->xPos())
      {
        ship2->xPos(tiles[i]->xPos() + tiles[i]->width());
      }
    }
    if (ship2->yPos() >= tiles[i]->yPos() && ship2->yPos() <= tiles[i]->yPos() + tiles[i]->height())
    {
      if (
        ship2->xPos() + ship2->width() > tiles[i]->xPos() &&
        ship2->xPos() + ship2->width() < tiles[i]->xPos() + tiles[i]->width())
      {
        ship2->xPos(tiles[i]->xPos() - ship2->width());
      }
    }
    if (
      ship2->yPos() + ship2->height() >= tiles[i]->yPos() + tiles[i]->height() &&
      ship2->yPos() + ship2->height() <= tiles[i]->yPos() + tiles[i]->height())
    {
      if (
        ship2->xPos() + ship2->width() > tiles[i]->xPos() &&
        ship2->xPos() + ship2->width() < tiles[i]->xPos() + tiles[i]->width())
      {
        ship2->xPos(tiles[i]->xPos() - ship2->width());
      }
    }
  }

  if (gravity2)
  {
    j_s2 = 7.0f;
    j_s2 -= 0.3f;
    ship2->yPos(ship2->yPos() - j_s2);
    if (ship2->yPos() < newPos2)
    {
      jump2      = false;
      hasPeaked2 = true;
    }
  }
  if ((!groundCheck2 || hasPeaked2) && !jump2)
  {
    ship2->yPos(ship2->yPos() + 10);
  }

  // moving the camera
  if (ship->xPos() > ship_look.x)
  {
    ship_look.x = ship->xPos();
  }
  ship_look.y  = ship->yPos();
  ship2_look.y = ship2->yPos();
  // stopping player exit
  if (ship->xPos() < ship_look.x - 960)
  {
    ship->xPos(ship_look.x - 960);
  }
  camera_one.lookAt(ship_look);
  camera_one.setZoom(0.9F);

  if (ship2->xPos() > ship2_look.x)
  {
    ship2_look.x = ship2->xPos();
  }
  // stopping player exit
  if (ship2->xPos() < ship2_look.x - 960)
  {
    ship2->xPos(ship2_look.x - 960);
  }
  camera_two.lookAt(ship2_look);
  camera_two.setZoom(0.9F);
}
//  ship->xPos(static_cast<float>(ship->xPos() + velocity.x * us.deltaInSecs()));
//  ship->yPos(static_cast<float>(ship->yPos() + velocity.y * us.deltaInSecs()));

/**
 * @brief Render your game and its scenes here.
 * @param us
 */
void ASGENetGame::render(const ASGE::GameTime& us)
{
  // example of split screen. just remove viewports and use
  // a single camera if you don't require the use of split screen
  // renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 1080 });
  // renderer->setProjectionMatrix(camera_one.getView());

  // bottom view
  renderer->setViewport(ASGE::Viewport{ 0, 560, 1920, 560 });
  renderer->setProjectionMatrix(camera_two.getView());
  for (unsigned int i = 0; i < tiles.size(); ++i)
  {
    renderer->render(*tiles[i]);
    // Logging::DEBUG("rendering tiles");
  }
  renderer->render(*ship);
  renderer->render(*ship2);

  // top view
  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 560 });
  renderer->setProjectionMatrix(camera_one.getView());
  //  renderer->render(*ship);
  for (unsigned int i = 0; i < tiles.size(); ++i)
  {
    renderer->render(*tiles[i]);
    // Logging::DEBUG("rendering tiles");
  }
  renderer->render(*ship);
  renderer->render(*ship2);

  // Makes sure the frames don't flick through too quickly, resets if not running or once the frames
  // have finished
  animation_timer += static_cast<float>(us.deltaInSecs());
  if (animation_timer > ANIMATION_FRAME_RATE)
  {
    // player1
    if (player1State == RUNNING)
    {
      animation_index1 += 1;

      if (animation_index1 > 3)
        animation_index1 = 0;
    }
    else if (player1State == IDLE)
    {
      animation_index1 = 4;
    }
    else if (player1State == JUMPING)
    {
      animation_index1 = 5;
    }
    // gets the frame according to the animation index
    ship->srcRect()[0] = static_cast<float>(animation_index1) * 32;

    if (player2State == RUNNING)
    {
      animation_index2 += 1;

      if (animation_index2 > 3)
        animation_index2 = 0;
    }
    else if (player2State == IDLE)
    {
      animation_index2 = 4;
    }
    else if (player2State == JUMPING)
    {
      animation_index2 = 5;
    }
    ship2->srcRect()[0] = static_cast<float>(animation_index2) * 32;

    animation_timer = 0.0f;
  }

  // reset the view and don't use a camera, useful for HUD
  //  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 1080 });
  //  renderer->setProjectionMatrix(0, 0, 1920, 1080);
  //  renderer->render(camera_one_label);
  //  renderer->render(camera_two_label);

  // renderer->render(*testPlayer->getSprite());

  // renderer->setProjectionMatrix(camera_one.getView());
}
void ASGENetGame::renderMap()
{
  for (unsigned long long i = 0; i < height; i++)
  {
    for (unsigned long long j = 0; j < width; j++)
    {
      if (testMap[static_cast<unsigned int>(j + i * width)] == 1)
      {
        auto& sprite = tiles.emplace_back(renderer->createUniqueSprite());
        if (sprite->loadTexture("data/sprites/Black.png"))
        {
          sprite->width(64);
          sprite->height(64);
          sprite->scale(1);
          sprite->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);
          sprite->xPos(
            static_cast<float>(j) * sprite->width() + 1200 -
            static_cast<float>(width) * sprite->width());
          sprite->yPos(
            static_cast<float>(i) * sprite->height() + 700 -
            static_cast<float>(height) * sprite->height());
        }
      }
    }
  }
}

void ASGENetGame::Camera()
{
  camera_one.lookAt(ASGE::Point2D(1920.0f * 0.5F * 0.3F, 1080 * 0.5F * 0.3F));
  camera_one.setZoom(0.3F);
}
