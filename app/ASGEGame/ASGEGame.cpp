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

  //running animation
  ship = renderer->createUniqueSprite();
<<<<<<< Updated upstream
  ship->loadTexture("/data/sprites/player_ship.png");

=======
  ship->loadTexture("/data/sprites/Player1Run.png");
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

  //player1 frame
  ship = renderer->createUniqueSprite();
  ship->loadTexture("/data/sprites/Player1.png");
  ship->width(64);
  ship->height(64);
  ship->xPos(256);
  ship->yPos(128);

  //jumping frame
  ship = renderer->createUniqueSprite();
  ship->loadTexture("/data/sprites/player1Jump.png");
  ship->width(64);
  ship->height(64);
  ship->xPos(256);
  ship->yPos(128);
>>>>>>> Stashed changes


  camera_one_label.setFont(*game_font).setString("Camera 1").setPosition({ 0, 55 }).setScale(1.5);
  camera_two_label.setFont(*game_font).setString("Camera 2").setPosition({ 960, 55 }).setScale(1.5);

  initMap();
  initAudio();
  initSprites();

  /// TESTING FOR DEFAULT CONSTRUCTORS OF DIFFERENT SPRITE OBJECT CLASSES
  /// @note DELETE OR REMOVE ME WHEN TESTING IS COMPLETE
  testSprite = std::make_unique<Sprite>(*renderer);
  testEntity = std::make_unique<Entity>(*renderer);
  testPlayer = std::make_unique<Player>(*renderer);
}

void ASGENetGame::initAudio()
{
  //audio_engine.init();
  //ASGE::FILEIO::File bg_audio_file;
  //if (bg_audio_file.open("/data/audio/cyberpunk.mp3"))
  //{
   // auto buffer = bg_audio_file.read();
    //auto length = static_cast<unsigned int>(buffer.length);
    //background_audio.loadMem(buffer.as_unsigned_char(), length, false, false);
    //background_audio.setLooping(true);
    //audio_engine.play(background_audio);
  //}
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
  // process single gamepad
  if (auto gamepad = inputs->getGamePad(); gamepad.is_connected)
  {
<<<<<<< Updated upstream
    velocity.x = gamepad.axis[ASGE::GAMEPAD::AXIS_LEFT_X] * 500;
    velocity.y = gamepad.axis[ASGE::GAMEPAD::AXIS_LEFT_Y] * 500;
=======
    if (((gamepad.buttons[0]) != 0u) && !gravity && groundCheck)
    {
      j_s = 3.0f;
      g_s = 0;
      Logging::DEBUG("jump");
      newPos      = ship->yPos() - 200;
      jump        = true;
      groundCheck = false;

      animationState = JUMPING;
    }
    if (abs(gamepad.axis[0]) > 0.1)
    {
      ship->xPos(ship->xPos() + 5 * gamepad.axis[0]);
    }
  }

  animationState = IDLE;

  if (keymap[ASGE::KEYS::KEY_A])
  {
    ship->xPos(ship->xPos() - 5);
    animationState = RUNNING;
  }
  if (keymap[ASGE::KEYS::KEY_D])
  {
    ship->xPos(ship->xPos() + 5);
    animationState = RUNNING;
  }
  if (keymap[ASGE::KEYS::KEY_W] && groundCheck)
  {
    // Logging::DEBUG("jump");
    jump        = true;
    groundCheck = false;
    j_s         = 3.0f;
    g_s         = 0;
    Logging::DEBUG("jump");
    newPos = ship->yPos() - 200;
    jump   = true;
  }
  //  if (keymap[ASGE::KEYS::KEY_S])
  //  {
  //    ship->yPos(ship->yPos() + 5);
  //  }
  if (keymap[ASGE::KEYS::KEY_LEFT])
  {
    ship2->xPos(ship2->xPos() - 5);
  }
  if (keymap[ASGE::KEYS::KEY_RIGHT])
  {
    ship2->xPos(ship2->xPos() + 5);
  }
  if (keymap[ASGE::KEYS::KEY_UP] && groundCheck2)
  {
    jump2        = true;
    groundCheck2 = false;
    j_s2         = 3.0f;
    g_s2         = 0;
    Logging::DEBUG("jump");
    newPos2 = ship2->yPos() - 200;
    jump2   = true;
  }
>>>>>>> Stashed changes

    if (gamepad_state.contains(gamepad.idx))
    {
      if (
        ((gamepad.buttons[ASGE::GAMEPAD::BUTTON_X]) == 0U) &&
        ((gamepad_state.at(gamepad.idx).buttons[ASGE::GAMEPAD::BUTTON_X]) != 0U))
      {
        Logging::DEBUG("X PRESSED");
        velocity.y *= 10;
      }
    }
  }

  ship->xPos(static_cast<float>(ship->xPos() + velocity.x * us.deltaInSecs()));
  ship->yPos(static_cast<float>(ship->yPos() + velocity.y * us.deltaInSecs()));

  // retrieve all connected gamepads and store their states
  for (auto& gamepad : inputs->getGamePads())
  {
    gamepad_state.insert_or_assign(gamepad.idx, gamepad);
  }
<<<<<<< Updated upstream
=======
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

  // animation speed
  if (animationState == RUNNING)
  {
    animation_timer += static_cast<float>(us.deltaInSecs());

    if (animation_timer > ANIMATION_FRAME_RATE)
    {
      animation_index ++;

      if(animation_index == 5) animation_index = 1;

      animation_timer = 0.0f;
    }
  }
  else
  {
    animation_index = 0;
  }
>>>>>>> Stashed changes
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

  renderMap();
}
bool ASGENetGame::initSprites()
{
  std::string filename = "data/sprite/player1.png";

  if(player1->initialiseSprite(filename) == true)
  {
    auto sprite = player1->getSprite();

    sprite->srcRect()[0] = 0;
    sprite->srcRect()[1] = 0;
    sprite->srcRect()[2] = 32;
    sprite->srcRect()[3] = 32;

    sprite->xPos(10);
    sprite->yPos(175);
    sprite->width(32);
    sprite->height(32);
    sprite->setGlobalZOrder(2);
    sprite->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);
  }
  /*
  if(player1->initialiseSprite(filename) == true)
  {
    auto sprite = player1->getSprite();

    sprite->srcRect()[0] = 0;
    sprite->srcRect()[1] = 0;
    sprite->srcRect()[2] = 32;
    sprite->srcRect()[3] = 32;

    sprite->xPos(10);
    sprite->yPos(175);
    sprite->width(32);
    sprite->height(32);
    sprite->setGlobalZOrder(2);
    sprite->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);
  }
   */
  return true;
}

bool ASGENetGame::initMap()
{
  ASGE::FILEIO::File tile_map;
  if (!tile_map.open("/data/map/PresentMap2.tmx"))
  {
    Logging::ERRORS("init::Failed to load map");
    return false;
  }
  ASGE::FILEIO::IOBuffer buffer = tile_map.read();
  std::string file_string(buffer.as_char(), buffer.length);
  map.loadFromString(file_string, ".");

<<<<<<< Updated upstream
  /// All collidable objects are checked within the init function as their location is will remain
  /// the same during gameplay, i.e: they remain static.
  for (const auto& layer : map.getLayers())
  {
    if (layer->getType() == tmx::Layer::Type::Tile)
    {
      auto tile_layer = layer->getLayerAs<tmx::TileLayer>();
      /// Look up tiles from a layer in a tile set
      for (unsigned int row = 0; row < layer->getSize().y; row++)
      {
        for (unsigned int col = 0; col < layer->getSize().x; col++)
        {
          auto tile_info = tile_layer.getTiles()[row * tile_layer.getSize().x + col];
          auto tile      = map.getTilesets()[0].getTile(tile_info.ID);
          if (tile != nullptr)
          {
            /// All contactable objects can be checked within this if statement, currently only
            /// walls but easily expandable with additional || / or
            if (tile_layer.getName() == "Ground")
            {
              auto& colliders = collidables.emplace_back(renderer->createUniqueSprite());
              if (colliders->loadTexture(tile->imagePath))
              {
                colliders->srcRect()[0] = static_cast<float>(tile->imagePosition.x);
                colliders->srcRect()[1] = static_cast<float>(tile->imagePosition.y);
                colliders->srcRect()[2] = static_cast<float>(tile->imageSize.x);
                colliders->srcRect()[3] = static_cast<float>(tile->imageSize.y);
=======
  if (animationState == RUNNING)
  {
    animation_index += 1;
  }

  if(animation_index > 5.0) animation_index = 0;

  ship->srcRect()[0] = animation_index * 32;



  // reset the view and don't use a camera, useful for HUD
  //  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 1080 });
  //  renderer->setProjectionMatrix(0, 0, 1920, 1080);
  //  renderer->render(camera_one_label);
  //  renderer->render(camera_two_label);
>>>>>>> Stashed changes

                colliders->width(static_cast<float>(tile->imageSize.x));
                colliders->height(static_cast<float>(tile->imageSize.y));

                colliders->scale(1);
                colliders->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);

                colliders->xPos(static_cast<float>(col * tile->imageSize.x));
                colliders->yPos(static_cast<float>(row * tile->imageSize.y));
              }
            }
          }
        }
      }
    }
  }
  return true;
}
void ASGENetGame::renderMap()
{
  /// Casting tile map layers to TileLayer
  for (const auto& layer : map.getLayers())
  {
    if (layer->getType() == tmx::Layer::Type::Object)
    {
      auto object_layer = layer->getLayerAs<tmx::ObjectGroup>();
      for (const auto& object : object_layer.getObjects())
      {
        if (object.getName() == "StartPoint")
        {
          // Only sets Mario's position to the spawn position on the first frame of the game's
          // render
          if (!player1Spawned)
          {
            spawnPos = object.getPosition();
            player1->getSprite()->xPos((spawnPos.x - player1->getSprite()->width()));
            player1->getSprite()->yPos((spawnPos.y - player1->getSprite()->height()));
            player1Spawned = true;
          }
        }
        else if (object.getName() == "EndPoint")
        {
          exitPos = object.getPosition();
        }
      }
    }
  }
}