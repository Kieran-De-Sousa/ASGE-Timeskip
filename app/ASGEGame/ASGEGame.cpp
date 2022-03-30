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
  renderer->setClearColour({ 0, 0, 0 });
  key_callback_id     = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  inputs->use_threads = false;

  ship = renderer->createUniqueSprite();
  ship->loadTexture("/data/sprites/player1.png");
  ship->width(32);
  ship->height(32);
  ship->xPos(64);
  ship->yPos(240);
  ship->setGlobalZOrder(3);

  ship2 = renderer->createUniqueSprite();
  ship2->loadTexture("/data/sprites/Player2.png");
  ship2->width(32);
  ship2->height(32);
  ship2->xPos(64);
  ship2->yPos(240);
  ship2->setGlobalZOrder(3);
  camera_one.lookAt(ship_look);
  camera_two.lookAt(ship2_look);
  renderMap();
  renderBackground();
  // camera_two.lookAt({ ship->xPos(), ship->yPos() + 100 });
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
      newPos      = ship->yPos() - 96;
      jump        = true;
      groundCheck = false;
    }
    if (abs(gamepad.axis[0]) > 0.1)
    {
      ship->xPos(ship->xPos() + 5 * gamepad.axis[0]);
    }
  }
  if (keymap[ASGE::KEYS::KEY_SPACE])
  {
    DebugInfo();
  }
  if (keymap[ASGE::KEYS::KEY_A])
  {
    ship->xPos(ship->xPos() - 5);
    ship->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);
  }
  if (keymap[ASGE::KEYS::KEY_D])
  {
    ship->xPos(ship->xPos() + 5);
    ship->setFlipFlags(ASGE::Sprite::FlipFlags::NORMAL);
  }
  if (keymap[ASGE::KEYS::KEY_W] && groundCheck)
  {
    // Logging::DEBUG("jump");
    jump        = true;
    groundCheck = false;
    j_s         = 3.0f;
    g_s         = 0;
    Logging::DEBUG("jump");
    newPos = ship->yPos() - 96;
    jump   = true;
  }
  //  if (keymap[ASGE::KEYS::KEY_S])
  //  {
  //    ship->yPos(ship->yPos() + 5);
  //  }
  if (keymap[ASGE::KEYS::KEY_LEFT])
  {
    ship2->xPos(ship2->xPos() - 5);
    ship2->setFlipFlags(ASGE::Sprite::FlipFlags::FLIP_X);
  }
  if (keymap[ASGE::KEYS::KEY_RIGHT])
  {
    ship2->xPos(ship2->xPos() + 5);
    ship2->setFlipFlags(ASGE::Sprite::FlipFlags::NORMAL);
  }
  if (keymap[ASGE::KEYS::KEY_UP] && groundCheck2)
  {
    jump2        = true;
    groundCheck2 = false;
    j_s2         = 3.0f;
    g_s2         = 0;
    Logging::DEBUG("jump");
    newPos2 = ship2->yPos() - 96;
    jump2   = true;
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
  camera_one.setZoom(2.0F);

  if (ship2->xPos() > ship2_look.x)
  {
    ship2_look.x = ship2->xPos();
  }
  // stopping player exit
  if (ship2->xPos() < ship2_look.x - 540)
  {
    ship2->xPos(ship2_look.x - 540);
  }
  camera_two.lookAt(ship2_look);
  camera_two.setZoom(2.0F);
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

  // bottom view
  renderer->setViewport(ASGE::Viewport{ 0, 560, 1920, 560 });
  renderer->setProjectionMatrix(camera_two.getView());
  for (unsigned int i = 0; i < tiles.size(); ++i)
  {
    renderer->render(*tiles[i]);
    // Logging::DEBUG("rendering tiles");
  }
  for (unsigned int i = 0; i < tilesB.size(); ++i)
  {
    renderer->render(*tilesB[i]);
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
  for (unsigned int i = 0; i < tilesB.size(); ++i)
  {
    renderer->render(*tilesB[i]);
    // Logging::DEBUG("rendering tiles");
  }
  renderer->render(*ship);
  renderer->render(*ship2);

  // reset the view and don't use a camera, useful for HUD
  //  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 1080 });
  //  renderer->setProjectionMatrix(0, 0, 1920, 1080);
  //  renderer->render(camera_one_label);
  //  renderer->render(camera_two_label);

  // renderer->render(*testPlayer->getSprite());

  // renderer->setProjectionMatrix(camera_one.getView());
}
bool ASGENetGame::renderMap()
{
  ASGE::FILEIO::File tile_map;
  if (!tile_map.open("/data/PastMap2 (1).tmx"))
  {
    Logging::ERRORS("init::Failed to load map");
    return false;
  }
  ASGE::FILEIO::IOBuffer buffer = tile_map.read();
  std::string file_string(buffer.as_char(), buffer.length);
  map.loadFromString(file_string, ".");

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
              auto& sprite = tiles.emplace_back(renderer->createUniqueSprite());
              if (sprite->loadTexture(tile->imagePath))
              {
                sprite->srcRect()[0] = static_cast<float>(tile->imagePosition.x);
                sprite->srcRect()[1] = static_cast<float>(tile->imagePosition.y);
                sprite->srcRect()[2] = static_cast<float>(tile->imageSize.x);
                sprite->srcRect()[3] = static_cast<float>(tile->imageSize.y);

                sprite->width(static_cast<float>(tile->imageSize.x));
                sprite->height(static_cast<float>(tile->imageSize.y));

                sprite->scale(1);
                sprite->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);

                sprite->xPos(static_cast<float>(col * tile->imageSize.x));
                sprite->yPos(static_cast<float>(row * tile->imageSize.y));
                sprite->setGlobalZOrder(1);
              }
            }
          }
        }
      }
    }
  }
  return true;
}
bool ASGENetGame::renderBackground()
{
  ASGE::FILEIO::File tile_map;
  if (!tile_map.open("/data/PastMap2 (1).tmx"))
  {
    Logging::ERRORS("init::Failed to load map");
    return false;
  }
  ASGE::FILEIO::IOBuffer buffer = tile_map.read();
  std::string file_string(buffer.as_char(), buffer.length);
  map.loadFromString(file_string, ".");

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
            auto& sprite = tilesB.emplace_back(renderer->createUniqueSprite());
            if (sprite->loadTexture(tile->imagePath))
            {
              sprite->srcRect()[0] = static_cast<float>(tile->imagePosition.x);
              sprite->srcRect()[1] = static_cast<float>(tile->imagePosition.y);
              sprite->srcRect()[2] = static_cast<float>(tile->imageSize.x);
              sprite->srcRect()[3] = static_cast<float>(tile->imageSize.y);

              sprite->width(static_cast<float>(tile->imageSize.x));
              sprite->height(static_cast<float>(tile->imageSize.y));

              sprite->scale(1);
              sprite->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);

              sprite->xPos(static_cast<float>(col * tile->imageSize.x));
              sprite->yPos(static_cast<float>(row * tile->imageSize.y));
            }
          }
        }
      }
    }
  }
  return true;
}
void ASGENetGame::DebugInfo()
{
  Logging::DEBUG(std::to_string(ship_look.x));
}
