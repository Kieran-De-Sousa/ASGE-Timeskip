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
  loadTiles();

  /// TESTING FOR DEFAULT CONSTRUCTORS OF DIFFERENT SPRITE OBJECT CLASSES
  /// @note DELETE OR REMOVE ME WHEN TESTING IS COMPLETE
  //  testSprite = std::make_unique<Sprite>(*renderer);
  //  testEntity = std::make_unique<Entity>(*renderer);
  //  testPlayer = std::make_unique<Player>(*renderer);

  player = renderer->createUniqueSprite();
  if (!player->loadTexture("/data/sprites/player_ship.jpg"))
  {
    Logging::ERRORS("didnt load player");
  }
  floor = renderer->createUniqueSprite();
  if (!floor->loadTexture("/data/sprites/floor.png"))
  {
  }
  player->width(32);
  player->height(32);
  player->xPos(64);
  player->yPos(64);

  camera_one.setZoom(3.0f);
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
  float playerRotation = player->rotationInRadians() * 57.8570f;
  float xStep          = cos(player->rotationInRadians()) * 5;
  float yStep          = sin(player->rotationInRadians()) * 5;
  Logging::ERRORS(std::to_string(playerRotation));
  if (keymap[ASGE::KEYS::KEY_RIGHT])
  {
    player->rotationInRadians(player->rotationInRadians() + 0.03f);
  }
  if (keymap[ASGE::KEYS::KEY_LEFT])
  {
    player->rotationInRadians(player->rotationInRadians() - 0.03f);
  }
  if (keymap[ASGE::KEYS::KEY_DOWN])
  {
    player->yPos(player->yPos() - yStep);
    player->xPos(player->xPos() - xStep);
  }
  if (keymap[ASGE::KEYS::KEY_UP])
  {
    player->yPos(player->yPos() + yStep);
    player->xPos(player->xPos() + xStep);
  }
  focus.x = player->xPos();
  focus.y = player->yPos();
  camera_one.lookAt(focus);
  // resolveCollision();
  // raycastControl();

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
  renderTileMap();
  renderer->render(*player);
  //  // example of split screen. just remove viewports and use
  //  // a single camera if you don't require the use of split screen
  //  renderer->setViewport(ASGE::Viewport{ 0, 0, 960, 1080 });
  renderer->setProjectionMatrix(camera_one.getView());
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
void ASGENetGame::loadTiles()
{
  ASGE::FILEIO::File tile_map;
  if (tile_map.open("data/testmapforraycast.tmx"))
  {
    ASGE::FILEIO::IOBuffer buffer = tile_map.read();
    std::string file_string(buffer.as_char(), buffer.length);
    map.loadFromString(file_string, ".");
  }
}
void ASGENetGame::renderTileMap()
{
  for (const auto& layer : map.getLayers())
  {
    if (layer->getType() == tmx::Layer::Type::Tile)
    {
      auto tile_layer = layer->getLayerAs<tmx::TileLayer>();
      for (unsigned int row = 0; row < layer->getSize().y; ++row)
      {
        for (unsigned int col = 0; col < layer->getSize().x; ++col)
        {
          auto tile_info   = tile_layer.getTiles()[row * tile_layer.getSize().x + col];
          const auto* tile = map.getTilesets()[0].getTile(tile_info.ID);
          if (tile != nullptr)
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

              sprite->yPos(static_cast<float>(row * tile->imageSize.y));
              sprite->xPos(static_cast<float>(col * tile->imageSize.x));

              renderer->render(*sprite);
            }
          }
        }
      }
    }
  }
}
void ASGENetGame::resolveCollision()
{
  for (const auto& layer : map.getLayers())
  {
    auto tile_layer = layer->getLayerAs<tmx::TileLayer>();
    for (unsigned int row = 0; row < layer->getSize().y; ++row)
    {
      for (unsigned int col = 0; col < layer->getSize().x; ++col)
      {
        auto tile_info   = tile_layer.getTiles()[row * tile_layer.getSize().x + col];
        const auto* tile = map.getTilesets()[0].getTile(tile_info.ID);
        if (tile != nullptr)
        {
          auto tile_rect = TileRect(
            tile->imageSize.x * col, tile->imageSize.y * row, tile->imageSize.x, tile->imageSize.y);
          auto player_rect = TileRect(
            static_cast<unsigned int>(player->xPos()),
            static_cast<unsigned int>(player->yPos()),
            static_cast<unsigned int>(player->width()),
            static_cast<unsigned int>(player->height()));
          if (
            ((static_cast<float>(player_rect.left()) > static_cast<float>(tile_rect.left())) &&
             (static_cast<float>(player_rect.left()) <
              static_cast<float>(tile_rect.left() + tile_rect.width()))) &&
            ((static_cast<float>(player_rect.top()) >= static_cast<float>(tile_rect.top())) &&
             (static_cast<float>(player_rect.top() + player_rect.height())) <=
               static_cast<float>((tile_rect.top() + tile_rect.height()))))
          {
            // Logging::DEBUG("left collision");
            player->xPos(static_cast<float>(tile_rect.left() + tile_rect.width()));
          }
          if (
            ((static_cast<float>(player_rect.top() + player_rect.height()) >
              static_cast<float>(tile_rect.top())) &&
             (static_cast<float>(player_rect.top() + player_rect.height()) <
              static_cast<float>(tile_rect.top() + tile_rect.height()))) &&
            (((static_cast<float>(player_rect.left()) >= static_cast<float>(tile_rect.left())) &&
              (static_cast<float>(player_rect.left()) <=
               static_cast<float>(tile_rect.left() + tile_rect.width()))) ||
             ((static_cast<float>(player_rect.left() + player_rect.width()) >=
               static_cast<float>(tile_rect.left())) &&
              (static_cast<float>(player_rect.left() + player_rect.width()) <=
               static_cast<float>(tile_rect.left() + tile_rect.width())))))
          {
            // Logging::DEBUG("colliding");
            //              isGround = true;
            player->yPos(
              static_cast<float>(tile_rect.top()) - static_cast<float>(player_rect.height()));
          }
          //            if((playerRect.top + playerRect.height < tileRect.top) &&
          //                (((playerRect.left > tileRect.left)
          //                   && (playerRect.left < tileRect.left + tileRect.width))
          //                  || ((playerRect.left + playerRect.width > tileRect.left) &&
          //                  (playerRect.left + playerRect.width < tileRect.left +
          //                  tileRect.width))))
          //            {
          //              //Logging::DEBUG("falling");
          //              isGround = false;
          //            }
          if (
            (static_cast<float>(player_rect.top() + player_rect.height()) <
             static_cast<float>(tile_rect.top())) &&
            (((static_cast<float>(player_rect.left()) > static_cast<float>(tile_rect.left())) &&
              (static_cast<float>(player_rect.left()) <
               static_cast<float>(tile_rect.left() + tile_rect.width()))) ||
             ((static_cast<float>(player_rect.left() + player_rect.width()) >
               static_cast<float>(tile_rect.left())) &&
              (static_cast<float>(player_rect.left() + player_rect.width()) <
               static_cast<float>(tile_rect.left() + tile_rect.width())))))
          {
            // Logging::DEBUG("colliding");
          }
          if (
            ((static_cast<float>(player_rect.top() + player_rect.height()) >
              static_cast<float>(tile_rect.top())) &&
             (static_cast<float>(player_rect.top() + player_rect.height()) <
              static_cast<float>(tile_rect.top() + tile_rect.height()))) &&
            (((static_cast<float>(player_rect.left()) >= static_cast<float>(tile_rect.left())) &&
              (static_cast<float>(player_rect.left()) <=
               static_cast<float>(tile_rect.left() + tile_rect.width()))) ||
             ((static_cast<float>(player_rect.left() + player_rect.width()) >=
                 static_cast<float>(tile_rect.left()) &&
               (static_cast<float>(player_rect.left() + player_rect.width()) <=
                static_cast<float>(tile_rect.left() + tile_rect.width()))))))
          {
            // Logging::DEBUG("colliding");
            player->yPos(
              static_cast<float>(tile_rect.top()) - static_cast<float>(player_rect.height()));
          }
          if (
            (static_cast<float>(player_rect.top()) <
             static_cast<float>(tile_rect.top() + tile_rect.height())) &&
            (static_cast<float>(player_rect.top() + player_rect.height()) >
             static_cast<float>(tile_rect.top() + tile_rect.height())) &&
            (((static_cast<float>(player_rect.left()) >= static_cast<float>(tile_rect.left())) &&
              (static_cast<float>(player_rect.left()) <=
               static_cast<float>(tile_rect.left() + tile_rect.width()))) ||
             ((static_cast<float>(player_rect.left() + player_rect.width()) >=
                 static_cast<float>(tile_rect.left()) &&
               (static_cast<float>(player_rect.left() + player_rect.width()) <=
                static_cast<float>(tile_rect.left() + tile_rect.width()))))))
          {
            // Logging::DEBUG("colliding 2");
            player->yPos(static_cast<float>(tile_rect.top() + tile_rect.height()));
          }
          if (
            ((static_cast<float>(player_rect.left() + player_rect.width()) >
              static_cast<float>(tile_rect.left())) &&
             (static_cast<float>(player_rect.left() + player_rect.width()) <
              static_cast<float>(tile_rect.left() + tile_rect.width()))) &&
            ((static_cast<float>(player_rect.top()) >= static_cast<float>(tile_rect.top())) &&
             (static_cast<float>(player_rect.top() + player_rect.height())) <=
               (static_cast<float>(tile_rect.top() + tile_rect.height()))))
          {
            // Logging::DEBUG("right collision");
            player->xPos(
              static_cast<float>(tile_rect.left()) - static_cast<float>(player_rect.width()));
          }
        }
      }
    }
  }
}
void ASGENetGame::raycastControl() {}
