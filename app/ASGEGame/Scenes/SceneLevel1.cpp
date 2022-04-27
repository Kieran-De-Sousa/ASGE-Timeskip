#include "SceneLevel1.h"

SceneLevel1::SceneLevel1(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene) :
  Scene(rendererRef, inputRef, scene)
{
}

bool SceneLevel1::init()
{
  setDefaultSceneStatus();

  /// Create maps and populate vectors
  loadPastMap();
  loadPresentMap();
  loadPastBackground();
  loadPresentBackground();

  player1 = std::make_shared<Player>(*renderer, 1);
  player1->initialiseSprite("/data/sprites/Player1Animation.png");
  player1->setSpriteVariables(24, 24, 3);
  player1->setPosition(pastSpawnPos.x, pastSpawnPos.y);
  /// Animations
  player1->getSprite()->srcRect()[0] = 0;
  player1->getSprite()->srcRect()[1] = 0;
  player1->getSprite()->srcRect()[2] = 32;
  player1->getSprite()->srcRect()[3] = 32;
  gameComponents.emplace_back(player1);

  player2 = std::make_shared<Player>(*renderer, 2);
  player2->initialiseSprite("/data/sprites/Player2Animation.png");
  player2->setSpriteVariables(24, 24, 3);
  player2->setPosition(pastSpawnPos.x, pastSpawnPos.y);
  /// Animations
  player2->getSprite()->srcRect()[0] = 0;
  player2->getSprite()->srcRect()[1] = 0;
  player2->getSprite()->srcRect()[2] = 32;
  player2->getSprite()->srcRect()[3] = 32;
  gameComponents.emplace_back(player2);

  /// Enemies
  enemy1 = std::make_shared<EnemyPassive>(*renderer, 5, 1, Enemy::EnemyType::PASSIVE, 300, 500);
  enemy1->initialiseSprite("/data/sprites/mushroom.png");
  enemy1->setSpriteVariables(16, 16, 3);
  enemy1->setPosition(421, 367);
  /// Animations
  enemy1->getSprite()->srcRect()[0] = 0;
  enemy1->getSprite()->srcRect()[1] = 0;
  enemy1->getSprite()->srcRect()[2] = 16;
  enemy1->getSprite()->srcRect()[3] = 16;
  gameComponents.emplace_back(enemy1);

  enemy2 = std::make_shared<EnemyChaser>(*renderer, 5, 1, Enemy::EnemyType::CHASER);
  enemy2->initialiseSprite("/data/sprites/mushroom.png");
  enemy2->setSpriteVariables(16, 16, 3);
  enemy2->setPosition(2670, 241);
  /// Animations
  enemy2->getSprite()->srcRect()[0] = 0;
  enemy2->getSprite()->srcRect()[1] = 0;
  enemy2->getSprite()->srcRect()[2] = 16;
  enemy2->getSprite()->srcRect()[3] = 16;
  gameComponents.emplace_back(enemy2);

  enemy3 = std::make_shared<EnemyChaser>(*renderer, 5, 1, Enemy::EnemyType::CHASER);
  enemy3->initialiseSprite("/data/sprites/mushroom.png");
  enemy3->setSpriteVariables(16, 16, 3);
  enemy3->setPosition(1840, 178);
  /// Animations
  enemy3->getSprite()->srcRect()[0] = 0;
  enemy3->getSprite()->srcRect()[1] = 0;
  enemy3->getSprite()->srcRect()[2] = 16;
  enemy3->getSprite()->srcRect()[3] = 16;
  gameComponents.emplace_back(enemy3);

  enemy4 = std::make_shared<EnemyChaser>(*renderer, 5, 1, Enemy::EnemyType::CHASER);
  enemy4->initialiseSprite("/data/sprites/mushroom.png");
  enemy4->setSpriteVariables(16, 16, 3);
  enemy4->setPosition(5303, 244);
  /// Animations
  enemy4->getSprite()->srcRect()[0] = 0;
  enemy4->getSprite()->srcRect()[1] = 0;
  enemy4->getSprite()->srcRect()[2] = 16;
  enemy4->getSprite()->srcRect()[3] = 16;
  gameComponents.emplace_back(enemy4);

  enemy5 = std::make_shared<EnemyPassive>(*renderer, 5, 1, Enemy::EnemyType::PASSIVE, 530, 530);
  enemy5->initialiseSprite("/data/sprites/mushroom.png");
  enemy5->setSpriteVariables(16, 16, 3);
  enemy5->setPosition(3790, 178);
  /// Animations
  enemy5->getSprite()->srcRect()[0] = 0;
  enemy5->getSprite()->srcRect()[1] = 0;
  enemy5->getSprite()->srcRect()[2] = 16;
  enemy5->getSprite()->srcRect()[3] = 16;
  gameComponents.emplace_back(enemy5);

  /// Health power up
  HealthPowerUp = std::make_shared<Sprite>(*renderer);
  HealthPowerUp->initialiseSprite("/data/sprites/Health.png");
  HealthPowerUp->setPosition(370, 330);
  HealthPowerUp->setSpriteVariables(16, 16, 3);
  gameComponents.emplace_back(HealthPowerUp);

  /// UI Initialisation
  UI = std::make_shared<PlayerUI>(*renderer);
  UI->init();
  gameComponents.emplace_back(UI);

  camera_one.lookAt(player1Look);
  camera_two.lookAt(player2Look);

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
    fireAudio.mVolume = 0.2F;
  }
  audio_engine.play(background_audio);
  return true;
}

void SceneLevel1::input()
{
  // TODO: updateGamepad() for players
  player1->updateKeymap(keymap);
  player2->updateKeymap(keymap);

  if (keymap[ASGE::KEYS::KEY_Q] || keymap[ASGE::KEYS::KEY_SPACE])
  {
    switch (state)
    {
      case TimeTravelState::PAST:
        state = TimeTravelState::PRESENT;
        break;
      case TimeTravelState::PRESENT:
        state = TimeTravelState::PAST;
        break;
    }
  }
}

void SceneLevel1::update(const ASGE::GameTime& us)
{
  for (auto& component : gameComponents)
  {
    /// Tick every components update function
    component->update(us);
    const auto& component_type = component->getComponentType();
    if (component_type == GameComponent::ComponentType::PLAYER)
    {
      std::shared_ptr<Player> player = std::static_pointer_cast<Player>(component);
      // retrieve all connected gamepads and store their states
      for (auto& gamepad : inputs->getGamePads())
      {
        player->updateGamepad(gamepad);
      }
      updatePlayers(us, player.get());
    }
    else if (component_type == GameComponent::ComponentType::UI)
    {
      // UI movement
      // health updating
      UI->getP1HealthBar()->xPos(player2Look.x - 435);
      UI->getP1HealthBar()->yPos(player2Look.y - 105);
      UI->getP1HealthNum()->xPos(player2Look.x - 335);
      UI->getP1HealthNum()->yPos(player2Look.y - 105);
      UI->getP2HealthBar()->xPos(player1Look.x - 435);
      UI->getP2HealthBar()->yPos(player1Look.y - 135);
      UI->getP2HealthNum()->xPos(player1Look.x - 335);
      UI->getP2HealthNum()->yPos(player1Look.y - 135);

      // portrait updating
      UI->getP1Portrait()->xPos(player2Look.x - 475);
      UI->getP1Portrait()->yPos(player2Look.y - 105);
      UI->getP2Portrait()->xPos(player1Look.x - 475);
      UI->getP2Portrait()->yPos(player1Look.y - 135);

      // weapon updating
      UI->getP1WepIndicator()->xPos(player2Look.x - 436);
      UI->getP1WepIndicator()->yPos(player2Look.y - 85);
      UI->getP1ActiveWep()->xPos(player2Look.x - 350);
      UI->getP1ActiveWep()->yPos(player2Look.y - 85);
      UI->getP2WepIndicator()->xPos(player1Look.x - 436);
      UI->getP2WepIndicator()->yPos(player1Look.y - 115);
      UI->getP2ActiveWep()->xPos(player1Look.x - 350);
      UI->getP2ActiveWep()->yPos(player1Look.y - 115);
    }
  }

  if (Helper::CollisionDetection::isInside(
        player1->getSprite()->getWorldBounds(), HealthPowerUp->getSprite()->getWorldBounds()))
  {
    player1->setHealth(player1->getHealth() + 1);
    UI->addHealth(2);
    HealthPowerUp->getSprite()->xPos(-300);
  }

  if (Helper::CollisionDetection::isInside(
        player2->getSprite()->getWorldBounds(), HealthPowerUp->getSprite()->getWorldBounds()))
  {
    player2->setHealth(player2->getHealth() + 1);
    UI->addHealth(1);
    HealthPowerUp->getSprite()->xPos(-300);
  }

  if (
    (enemy2->getSprite()->xPos() - player1->getSprite()->xPos() < 128) ||
    (enemy2->getSprite()->xPos() - player2->getSprite()->xPos() < 128))
  {
    enemy2->getSprite()->setFlipFlags(ASGE::Sprite::FLIP_X);
    enemy2->setActive(true);
  }
  if (
    (enemy3->getSprite()->xPos() - player1->getSprite()->xPos() < 256) ||
    (enemy3->getSprite()->xPos() - player2->getSprite()->xPos() < 256))
  {
    enemy3->getSprite()->setFlipFlags(ASGE::Sprite::FLIP_X);
    enemy3->setActive(true);
  }

  // moving the camera
  if (player1->getSprite()->xPos() > player1Look.x)
  {
    player1Look.x = player1->getSprite()->xPos();
  }

  if (player2->getSprite()->xPos() > player2Look.x)
  {
    player2Look.x = player2->getSprite()->xPos();
  }

  player1Look.y = player1->getSprite()->yPos();
  player2Look.y = player2->getSprite()->yPos();
  // stopping player exit
  if (player1->getSprite()->xPos() < player1Look.x - 960)
  {
    player1->getSprite()->xPos(player1Look.x - 960);
  }

  if (player2->getSprite()->xPos() < player2Look.x - 960)
  {
    player2->getSprite()->xPos(player2Look.x - 960);
  }

  camera_one.lookAt(player1Look);
  camera_one.setZoom(2.0F);

  camera_two.lookAt(player2Look);
  camera_two.setZoom(2.0F);

  if (keymap[ASGE::KEYS::KEY_F])
  {
    audio_engine.play(fireAudio);
  }
}

void SceneLevel1::updatePlayers(const ASGE::GameTime& us, Player* player)
{
  switch (state)
  {
    case TimeTravelState::PAST:
      for (unsigned long long i = 0; i < PastTiles.size(); i++)
      {
        /// Exit Check
        if (player->getSprite()->getWorldBounds().v3.x >= pastExitPos.x)
        {
          setNewScene(GameScene::LEVEL_2);
        }

        if (Helper::CollisionDetection::inYBounds(
              enemy2->getSprite()->getWorldBounds(), PastTiles[i]->getWorldBounds()))
        {
          if (Helper::CollisionDetection::touchingLeft(
                enemy2->getSprite()->getWorldBounds(), PastTiles[i]->getWorldBounds()))
          {
            enemy2->getSprite()->xPos(PastTiles[i]->xPos() + PastTiles[i]->width());
          }
        }
        /// Player Collision Detection
        if (Helper::CollisionDetection::inXBounds(
              player->getSprite()->getWorldBounds(), PastTiles[i]->getWorldBounds()))
        {
          if (Helper::CollisionDetection::touchingTop(
                player->getSprite()->getWorldBounds(), PastTiles[i]->getWorldBounds()))
          {
            player->setGrounded(true);
            player->getSprite()->yPos(PastTiles[i]->yPos() - player->getSprite()->height());
          }
          else if ((Helper::CollisionDetection::touchingBottom(
                     player->getSprite()->getWorldBounds(), PastTiles[i]->getWorldBounds())))
          {
            player->setJumpSpeed(0);
            player->setJumping(false);
            player->setJumpPeaked(true);
            player->getSprite()->yPos(PastTiles[i]->yPos() + PastTiles[i]->height());
          }
        }
        if (Helper::CollisionDetection::playerYChecking(
              player->getSprite()->getWorldBounds(), PastTiles[i]->getWorldBounds()))
        {
          if (
            Helper::CollisionDetection::touchingLeft(
              player->getSprite()->getWorldBounds(), PastTiles[i]->getWorldBounds()) &&
            !(Helper::CollisionDetection::touchingBottom(
              player->getSprite()->getWorldBounds(), PastTiles[i]->getWorldBounds())))
          {
            player->getSprite()->xPos(PastTiles[i]->xPos() + PastTiles[i]->width());
          }
          else if (
            Helper::CollisionDetection::touchingRight(
              player->getSprite()->getWorldBounds(), PastTiles[i]->getWorldBounds()) &&
            !(Helper::CollisionDetection::touchingBottom(
              player->getSprite()->getWorldBounds(), PastTiles[i]->getWorldBounds())))
          {
            player->getSprite()->xPos(PastTiles[i]->xPos() - player->getSprite()->width());
          }
        }
      }
      break;
    case TimeTravelState::PRESENT:
      for (unsigned long long i = 0; i < PresentTiles.size(); i++)
      {
        /// Exit Check
        if (player->getSprite()->getWorldBounds().v3.x >= presentExitPos.x)
        {
          setNewScene(GameScene::LEVEL_2);
        }

        if (Helper::CollisionDetection::inYBounds(
              enemy2->getSprite()->getWorldBounds(), PresentTiles[i]->getWorldBounds()))
        {
          if (Helper::CollisionDetection::touchingLeft(
                enemy2->getSprite()->getWorldBounds(), PresentTiles[i]->getWorldBounds()))
          {
            enemy2->getSprite()->xPos(PresentTiles[i]->xPos() + PresentTiles[i]->width());
          }
        }
        /// Player Collision Detection
        if (Helper::CollisionDetection::inXBounds(
              player->getSprite()->getWorldBounds(), PresentTiles[i]->getWorldBounds()))
        {
          if (Helper::CollisionDetection::touchingTop(
                player->getSprite()->getWorldBounds(), PresentTiles[i]->getWorldBounds()))
          {
            player->setGrounded(true);
            player->getSprite()->yPos(PresentTiles[i]->yPos() - player->getSprite()->height());
          }
          else if ((Helper::CollisionDetection::touchingBottom(
                     player->getSprite()->getWorldBounds(), PresentTiles[i]->getWorldBounds())))
          {
            player->setJumpSpeed(0);
            player->setJumping(false);
            player->setJumpPeaked(true);
            player->getSprite()->yPos(PresentTiles[i]->yPos() + PresentTiles[i]->height());
          }
        }
        if (Helper::CollisionDetection::playerYChecking(
              player->getSprite()->getWorldBounds(), PresentTiles[i]->getWorldBounds()))
        {
          if (
            Helper::CollisionDetection::touchingLeft(
              player->getSprite()->getWorldBounds(), PresentTiles[i]->getWorldBounds()) &&
            !(Helper::CollisionDetection::touchingBottom(
              player->getSprite()->getWorldBounds(), PresentTiles[i]->getWorldBounds())))
          {
            player->getSprite()->xPos(PresentTiles[i]->xPos() + PresentTiles[i]->width());
          }
          else if (
            Helper::CollisionDetection::touchingRight(
              player->getSprite()->getWorldBounds(), PresentTiles[i]->getWorldBounds()) &&
            !(Helper::CollisionDetection::touchingBottom(
              player->getSprite()->getWorldBounds(), PresentTiles[i]->getWorldBounds())))
          {
            player->getSprite()->xPos(PresentTiles[i]->xPos() - player->getSprite()->width());
          }
        }
      }
      break;
  }
}

void SceneLevel1::fixedUpdate(const ASGE::GameTime& us) {}

void SceneLevel1::render(const ASGE::GameTime& us)
{
  /// Bottom view
  renderer->setViewport(ASGE::Viewport{ 0, 560, 1920, 560 });
  renderer->setProjectionMatrix(camera_two.getView());
  renderScene(us);
  // P1 health UI render
  renderer->render(*UI->getP1Portrait());
  renderer->render(*UI->getP1HealthBar());
  renderer->render(*UI->getP1HealthNum());

  // P1 weapon UI render
  renderer->render(*UI->getP1WepIndicator());
  renderer->render(*UI->getP1ActiveWep());

  /// Top view
  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 560 });
  renderer->setProjectionMatrix(camera_one.getView());
  renderScene(us);
  // P2 health UI render
  renderer->render(*UI->getP2HealthBar());
  renderer->render(*UI->getP2Portrait());
  renderer->render(*UI->getP2HealthNum());

  // P2 weapon UI render
  renderer->render(*UI->getP2WepIndicator());
  renderer->render(*UI->getP2ActiveWep());
}

void SceneLevel1::renderScene(const ASGE::GameTime& us)
{
  if (state == TimeTravelState::PAST)
  {
    for (unsigned int i = 0; i < tilesPastBackground.size(); ++i)
    {
      renderer->render(*tilesPastBackground[i]);
    }
    for (unsigned int i = 0; i < PastTiles.size(); ++i)
    {
      renderer->render(*PastTiles[i]);
    }
  }
  if (state == TimeTravelState::PRESENT)
  {
    for (unsigned int i = 0; i < tilesPresentBackground.size(); ++i)
    {
      renderer->render(*tilesPresentBackground[i]);
    }
    for (unsigned int i = 0; i < PresentTiles.size(); ++i)
    {
      renderer->render(*PresentTiles[i]);
    }
  }

  renderer->render(*player1->getSprite());
  renderer->render(*player2->getSprite());
  renderer->render(*enemy1->getSprite());
  renderer->render(*enemy2->getSprite());
  renderer->render(*enemy3->getSprite());
  renderer->render(*enemy4->getSprite());
  renderer->render(*enemy5->getSprite());
  renderer->render(*HealthPowerUp->getSprite());
  /// Bullets
  for (const auto& bullet : player1->getBullets())
  {
    renderer->render(*bullet->getSprite());
  }
  for (const auto& bullet : player2->getBullets())
  {
    renderer->render(*bullet->getSprite());
  }
}

bool SceneLevel1::loadPastMap()
{
  ASGE::FILEIO::File tile_map;
  if (!tile_map.open("data/map/PastMap2.tmx"))
  {
    Logging::ERRORS("init::Failed to load past map");
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
      /// Look up tilemapPastContactable from a layer in a tile set
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
              auto& sprite = PastTiles.emplace_back(renderer->createUniqueSprite());

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
    if (layer->getType() == tmx::Layer::Type::Object)
    {
      auto object_layer = layer->getLayerAs<tmx::ObjectGroup>();
      for (const auto& object : object_layer.getObjects())
      {
        if (object.getName() == "Entrance")
        {
          pastSpawnPos = object.getPosition();
        }
        else if (object.getName() == "Exit")
        {
          pastExitPos = object.getPosition();
        }
      }
    }
  }
  return true;
}

bool SceneLevel1::loadPresentMap()
{
  ASGE::FILEIO::File tile_map;

  if (!tile_map.open("data/map/PresentMap2.tmx"))
  {
    Logging::ERRORS("init::Failed to load present map");
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
              auto& sprite = PresentTiles.emplace_back(renderer->createUniqueSprite());
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
    if (layer->getType() == tmx::Layer::Type::Object)
    {
      auto object_layer = layer->getLayerAs<tmx::ObjectGroup>();
      for (const auto& object : object_layer.getObjects())
      {
        if (object.getName() == "Entrance")
        {
          presentSpawnPos = object.getPosition();
        }
        else if (object.getName() == "Exit")
        {
          presentExitPos = object.getPosition();
        }
      }
    }
  }
  return true;
}

bool SceneLevel1::loadPastBackground()
{
  ASGE::FILEIO::File tile_map;
  if (!tile_map.open("data/map/PastMap2.tmx"))
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
      /// Look up tilemapPastContactable from a layer in a tile set
      for (unsigned int row = 0; row < layer->getSize().y; row++)
      {
        for (unsigned int col = 0; col < layer->getSize().x; col++)
        {
          auto tile_info = tile_layer.getTiles()[row * tile_layer.getSize().x + col];
          auto tile      = map.getTilesets()[0].getTile(tile_info.ID);
          if (tile != nullptr)
          {
            auto& sprite = tilesPastBackground.emplace_back(renderer->createUniqueSprite());
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

bool SceneLevel1::loadPresentBackground()
{
  ASGE::FILEIO::File tile_map;

  if (!tile_map.open("data/map/PresentMap2.tmx"))
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
            auto& sprite = tilesPresentBackground.emplace_back(renderer->createUniqueSprite());
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
  /// Beware Ugly Code in the name of debug
  //  Logging::DEBUG(std::to_string(bullets[bulletCount]->xPos()));
  //  Logging::DEBUG("V1 X:" + std::to_string(player1->getSprite()->getWorldBounds().v1.x));
  //  Logging::DEBUG("V2 X:" +std::to_string(player1->getSprite()->getWorldBounds().v2.x));
  //  Logging::DEBUG("V3 X:" +std::to_string(player1->getSprite()->getWorldBounds().v3.x));
  //  Logging::DEBUG("V4 X:" +std::to_string(player1->getSprite()->getWorldBounds().v4.x));
  //  Logging::DEBUG("V1 Y:" +std::to_string(player1->getSprite()->getWorldBounds().v1.y));
  //  Logging::DEBUG("V2 Y:" +std::to_string(player1->getSprite()->getWorldBounds().v2.y));
  //  Logging::DEBUG("V3 Y:" +std::to_string(player1->getSprite()->getWorldBounds().v3.y));
  //  Logging::DEBUG("V4 Y:" +std::to_string(player1->getSprite()->getWorldBounds().v4.y));
  //  Logging::DEBUG("V1 2 X:" + std::to_string(player2->getSprite()->getWorldBounds().v1.x));
  //  Logging::DEBUG("V2 2 X:" +std::to_string(player2->getSprite()->getWorldBounds().v2.x));
  //  Logging::DEBUG("V3 2 X:" +std::to_string(player2->getSprite()->getWorldBounds().v3.x));
  //  Logging::DEBUG("V4 2 X:" +std::to_string(player2->getSprite()->getWorldBounds().v4.x));
  //  Logging::DEBUG("V1 2 Y:" +std::to_string(player2->getSprite()->getWorldBounds().v1.y));
  //  Logging::DEBUG("V2 2 Y:" +std::to_string(player2->getSprite()->getWorldBounds().v2.y));
  //  Logging::DEBUG("V3 2 Y:" +std::to_string(player2->getSprite()->getWorldBounds().v3.y));
  //  Logging::DEBUG("V4 2 Y:" +std::to_string(player2->getSprite()->getWorldBounds().v4.y));
  //  if(Helper::CollisionDetection::inYBounds(player1->getSprite()->getWorldBounds(),
  //  player2->getSprite()->getWorldBounds())){
  //    if(Helper::CollisionDetection::touchingRight(player1->getSprite()->getWorldBounds(),
  //    player2->getSprite()->getWorldBounds()))
  //    {
  //      player1->getSprite()->xPos(player2->getSprite()->xPos() - player1->getSprite()->width());
  //    }
  //    if(Helper::CollisionDetection::touchingLeft(player1->getSprite()->getWorldBounds(),
  //    player2->getSprite()->getWorldBounds()))
  //    {
  //      player1->getSprite()->xPos(player2->getSprite()->xPos() - player1->getSprite()->width());
  //    }
  //  }
}