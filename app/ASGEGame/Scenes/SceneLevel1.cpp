#include "SceneLevel1.h"

SceneLevel1::SceneLevel1(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene) :
  Scene(rendererRef, inputRef, scene)
{
}

bool SceneLevel1::init()
{
  setDefaultSceneStatus();

  player1 = std::make_unique<Player>(*renderer, 1);
  player1->initialiseSprite("/data/sprites/Player1Animation.png");
  player1->setSpriteVariables(32, 32, 3);
  player1->setPosition(64, 240);

  player2 = std::make_unique<Player>(*renderer, 2);
  player2->initialiseSprite("/data/sprites/Player2Animation.png");
  player2->setSpriteVariables(32, 32, 3);
  player2->setPosition(64, 240);

  /// Animations
  player1->getSprite()->srcRect()[0]  = 0;
  player1->getSprite()->srcRect()[1]  = 0;
  player1->getSprite()->srcRect()[2]  = 32;
  player1->getSprite()->srcRect()[3]  = 32;

  player2->getSprite()->srcRect()[0] = 0;
  player2->getSprite()->srcRect()[1] = 0;
  player2->getSprite()->srcRect()[2] = 32;
  player2->getSprite()->srcRect()[3] = 32;

  camera_one.lookAt(player1Look);
  camera_two.lookAt(player2Look);
  renderMap();
  renderBackground();

  for (int i = 0; i < magSize; ++i)
  {
    bullets.push_back(renderer->createUniqueSprite());
    directions.emplace_back(0, 0);

    // TODO: Finish below
    //    auto bullet = std::make_unique<Bullet>(*renderer);
    //    bullet->initialiseSprite("data/sprites/bulletSprite.png");
    //    bullet->getSprite()->setGlobalZOrder(6);
    //    betterBullets.emplace_back(bullet.get());
  }
  for (unsigned long long int i = 0; i < bullets.size(); i++)
  {
    bullets[i]->loadTexture("data/sprites/bulletSprite.png");
    bullets[i]->xPos(-200);
    bullets[i]->yPos(-200);
    bullets[i]->width(8);
    bullets[i]->height(8);
    bullets[i]->setGlobalZOrder(6);
  }

  audio_engine.init();

  ASGE::FILEIO::File bg_audio_file;
  if (bg_audio_file.open("/data/audio/bgm_action_4.mp3")) // open the file
  {
    static auto buffer = bg_audio_file.read(); // read its contents
    background_audio.loadMem(
      buffer.as_unsigned_char(), static_cast<unsigned int>(buffer.length), false, false);
  }
  ASGE::FILEIO::File f_audio_file;
  if (f_audio_file.open("/data/audio/sfx_wpn_machinegun_loop3.wav")) // open the file
  {
    static auto buffer = f_audio_file.read(); // read its contents
    fireAudio.loadMem(
      buffer.as_unsigned_char(), static_cast<unsigned int>(buffer.length), false, false);
    fireAudio.mVolume = 0.2f;
  }
  audio_engine.play(background_audio);
  return true;
}

void SceneLevel1::input()
{
  // TODO: updateGamepad() for players
  player1->updateKeymap(keymap);
  player2->updateKeymap(keymap);
}

void SceneLevel1::update(const ASGE::GameTime& us)
{
  // TODO: Finish conversion into "betterBullets" (part of bullet class)
  for (unsigned long long i = 0; i < bullets.size(); i++)
  {
    bullets[i]->xPos(bullets[i]->xPos() + directions[i].position.x * 8.4F);
    bullets[i]->yPos(bullets[i]->yPos() + directions[i].position.y * 8.4F);
  }

  player1->update(us);
  player2->update(us);

  for (unsigned long long i = 0; i < tilemapContactable.size(); i++)
  {
    /// Player 1 Collision Detection
    if (Helper::CollisionDetection::inXBounds(
          player1->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()))
    {
      if (Helper::CollisionDetection::touchingTop(
            player1->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()))
      {
        player1->setGrounded(true);
        player1->getSprite()->yPos(tilemapContactable[i]->yPos() - player1->getSprite()->height());
      }
      else if ((Helper::CollisionDetection::touchingBottom(
                 player1->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds())))
      {
        player1->setJumpSpeed(0);
        player1->setJumping(false);
        player1->setJumpPeaked(true);
        player1->getSprite()->yPos(tilemapContactable[i]->yPos() + tilemapContactable[i]->height());
      }
    }
    if (Helper::CollisionDetection::playerYChecking(
          player1->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()))
    {
      if (
        Helper::CollisionDetection::touchingLeft(
          player1->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()) &&
        !(Helper::CollisionDetection::touchingBottom(
          player1->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds())))
      {
        player1->getSprite()->xPos(tilemapContactable[i]->xPos() + tilemapContactable[i]->width());
      }
      else if (
        Helper::CollisionDetection::touchingRight(
          player1->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()) &&
        !(Helper::CollisionDetection::touchingBottom(
          player1->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds())))
      {
        player1->getSprite()->xPos(tilemapContactable[i]->xPos() - player1->getSprite()->width());
      }
    }

    /// Player 2 Collision Detection
    if (Helper::CollisionDetection::inXBounds(
          player2->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()))
    {
      if (Helper::CollisionDetection::touchingTop(
            player2->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()))
      {
        player2->setGrounded(true);
        player2->getSprite()->yPos(tilemapContactable[i]->yPos() + player2->getSprite()->height());
      }
      else if (Helper::CollisionDetection::touchingBottom(
                 player2->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()))
      {
        player2->setJumpSpeed(0);
        player2->setJumping(false);
        player2->setJumpPeaked(true);
        player2->getSprite()->yPos(tilemapContactable[i]->yPos() + tilemapContactable[i]->height());
      }
    }
    if (Helper::CollisionDetection::playerYChecking(
          player2->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()))
    {
      if (
        Helper::CollisionDetection::touchingLeft(
          player2->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()) &&
        !(Helper::CollisionDetection::touchingBottom(
          player2->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds())))
      {
        player2->getSprite()->xPos(tilemapContactable[i]->xPos() + tilemapContactable[i]->width());
      }
      else if (
        Helper::CollisionDetection::touchingRight(
          player2->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds()) &&
        !(Helper::CollisionDetection::touchingBottom(
          player2->getSprite()->getWorldBounds(), tilemapContactable[i]->getWorldBounds())))
      {
        player2->getSprite()->xPos(tilemapContactable[i]->xPos() - player2->getSprite()->width());
      }
    }
  }

  // moving the camera
  if (player1->getSprite()->xPos() > player1Look.x)
  {
    player1Look.x = player1->getSprite()->xPos();
  }
  player1Look.y = player1->getSprite()->yPos();
  player2Look.y = player2->getSprite()->yPos();
  // stopping player exit
  if (player1->getSprite()->xPos() < player1Look.x - 960)
  {
    player1->getSprite()->xPos(player1Look.x - 960);
  }
  camera_one.lookAt(player1Look);
  camera_one.setZoom(2.0F);

  if (player2->getSprite()->xPos() > player2Look.x)
  {
    player2Look.x = player2->getSprite()->xPos();
  }
  // stopping player exit
  if (player2->getSprite()->xPos() < player2Look.x - 540)
  {
    player2->getSprite()->xPos(player2Look.x - 540);
  }
  camera_two.lookAt(player2Look);
  camera_two.setZoom(2.0F);

  if (keymap[ASGE::KEYS::KEY_F])
  {
    audio_engine.play(fireAudio);
  }
}

void SceneLevel1::fixedUpdate(const ASGE::GameTime& us) {}

void SceneLevel1::render(const ASGE::GameTime& us)
{
  /// bottom view
  renderer->setViewport(ASGE::Viewport{ 0, 560, 1920, 560 });
  renderer->setProjectionMatrix(camera_two.getView());
  renderScene(us);

  /// top view
  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 560 });
  renderer->setProjectionMatrix(camera_one.getView());
  renderScene(us);
}

void SceneLevel1::renderScene(const ASGE::GameTime& us)
{
  for (unsigned int i = 0; i < tilemapContactable.size(); ++i)
  {
    renderer->render(*tilemapContactable[i]);
  }
  for (unsigned int i = 0; i < tilesBackground.size(); ++i)
  {
    renderer->render(*tilesBackground[i]);
  }

  renderer->render(*player1->getSprite());
  renderer->render(*player2->getSprite());


  // TODO: Convert into "betterBullets"
  for (unsigned long long int i = 0; i < bullets.size(); i++)
  {
    renderer->render(*bullets[i]);
  }
}

bool SceneLevel1::renderMap()
{
  ASGE::FILEIO::File tile_map;
  if (!tile_map.open("/data/PastMap2.tmx"))
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
      /// Look up tilemapContactable from a layer in a tile set
      for (unsigned int row = 0; row < layer->getSize().y; row++)
      {
        for (unsigned int col = 0; col < layer->getSize().x; col++)
        {
          auto tile_info = tile_layer.getTiles()[row * tile_layer.getSize().x + col];
          auto tile      = map.getTilesets()[0].getTile(tile_info.ID);
          if (tile != nullptr)
          {
            if (tile_layer.getName() == "Ground")
            {
              auto& sprite = tilemapContactable.emplace_back(renderer->createUniqueSprite());
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
bool SceneLevel1::renderBackground()
{
  ASGE::FILEIO::File tile_map;
  if (!tile_map.open("/data/PastMap2.tmx"))
  {
    Logging::ERRORS("init::Failed to load map");
    return false;
  }
  ASGE::FILEIO::IOBuffer buffer = tile_map.read();
  std::string file_string(buffer.as_char(), buffer.length);
  map.loadFromString(file_string, ".");

  for (const auto& layer : map.getLayers())
  {
    if (layer->getType() == tmx::Layer::Type::Tile)
    {
      auto tile_layer = layer->getLayerAs<tmx::TileLayer>();
      /// Look up tilemapContactable from a layer in a tile set
      for (unsigned int row = 0; row < layer->getSize().y; row++)
      {
        for (unsigned int col = 0; col < layer->getSize().x; col++)
        {
          auto tile_info = tile_layer.getTiles()[row * tile_layer.getSize().x + col];
          auto tile      = map.getTilesets()[0].getTile(tile_info.ID);
          if (tile != nullptr)
          {
            auto& sprite = tilesBackground.emplace_back(renderer->createUniqueSprite());
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
void SceneLevel1::Camera() {}
void SceneLevel1::DebugInfo()
{
  Logging::DEBUG(std::to_string(bullets[bulletCount]->xPos()));
}