#include "SceneLevel3.h"

SceneLevel3::SceneLevel3(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene) :
  Scene(rendererRef, inputRef, scene)
{
}

bool SceneLevel3::init()
{
  setDefaultSceneStatus();

  /// Create maps and populate vectors
  loadPastMap();
  loadPresentMap();

  /// Players
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
  enemy1 = std::make_shared<EnemyPassive>(*renderer, 5, 1, Enemy::EnemyType::PASSIVE, 500, 600);
  enemy1->initialiseSprite("/data/sprites/SlimeA.png");
  enemy1->setSpriteVariables(16, 16, 3);
  enemy1->setPosition(pastEnemy1Pos.x, pastEnemy1Pos.y);
  /// Animations
  enemy1->getSprite()->srcRect()[0] = 0;
  enemy1->getSprite()->srcRect()[1] = 0;
  enemy1->getSprite()->srcRect()[2] = 16;
  enemy1->getSprite()->srcRect()[3] = 16;
  enemy1->setTotalAnimFrames(15);
  gameComponents.emplace_back(enemy1);

  enemy2 = std::make_shared<EnemyChaser>(*renderer, 5, 1, Enemy::EnemyType::CHASER);
  enemy2->initialiseSprite("/data/sprites/IDS.png");
  enemy2->setSpriteVariables(27, 27, 3);
  enemy2->setPosition(pastEnemy2Pos.x, pastEnemy2Pos.y);
  /// Animations
  enemy2->getSprite()->srcRect()[0] = 0;
  enemy2->getSprite()->srcRect()[1] = 0;
  enemy2->getSprite()->srcRect()[2] = 27;
  enemy2->getSprite()->srcRect()[3] = 27;
  enemy2->setTotalAnimFrames(7);
  gameComponents.emplace_back(enemy2);

  enemy3 = std::make_shared<EnemyChaser>(*renderer, 5, 1, Enemy::EnemyType::CHASER);
  enemy3->initialiseSprite("/data/sprites/CultistWalk.png");
  enemy3->setSpriteVariables(32, 32, 3);
  enemy3->setPosition(pastEnemy3Pos.x, pastEnemy3Pos.y);
  /// Animations
  enemy3->getSprite()->srcRect()[0] = 0;
  enemy3->getSprite()->srcRect()[1] = 0;
  enemy3->getSprite()->srcRect()[2] = 32;
  enemy3->getSprite()->srcRect()[3] = 32;
  enemy3->setTotalAnimFrames(5);
  gameComponents.emplace_back(enemy3);

  enemy4 = std::make_shared<EnemyPassive>(*renderer, 5, 1, Enemy::EnemyType::PASSIVE, 530, 530);
  enemy4->initialiseSprite("/data/sprites/WormWalk.png");
  enemy4->setSpriteVariables(32, 32, 3);
  enemy4->setPosition(pastEnemy4Pos.x, pastEnemy4Pos.y);
  /// Animations
  enemy4->getSprite()->srcRect()[0] = 0;
  enemy4->getSprite()->srcRect()[1] = 0;
  enemy4->getSprite()->srcRect()[2] = 32;
  enemy4->getSprite()->srcRect()[3] = 32;
  enemy4->setTotalAnimFrames(8);
  gameComponents.emplace_back(enemy4);

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
  if (bg_audio_file.open("/data/audio/Level3Audio.mp3")) // open the file
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

void SceneLevel3::input()
{
  player1->updateKeymap(keymap);
  player2->updateKeymap(keymap);
}

void SceneLevel3::update(const ASGE::GameTime& us)
{
  /// Update the camera
  updateCamera(us);

  for (auto& component : gameComponents)
  {
    /// Tick every components update function
    component->update(us);

    /// Get component type to static cast into appropriate type
    const auto& component_type = component->getComponentType();
    if (component_type == GameComponent::ComponentType::PLAYER)
    {
      std::shared_ptr<Player> player = std::static_pointer_cast<Player>(component);
      /// Retrieve all connected gamepads and store their states
      for (auto& gamepad : inputs->getGamePads())
      {
        if (gamepad.buttons[ASGE::GAMEPAD::BUTTON_GUIDE] != 0u)
        {
          setPauseScreen(!sceneStatus.pause_scene);
        }
        if (gamepad.idx == 0)
        {
          player1->updateGamepad(gamepad);
        }
        else
        {
          player2->updateGamepad(gamepad);
        }
      }
      updatePlayers(us, player.get());
    }
    else if (component_type == GameComponent::ComponentType::ENEMY)
    {
      std::shared_ptr<Enemy> enemy = std::static_pointer_cast<Enemy>(component);
      checkEnemies(us, enemy.get());
    }
    else if (component_type == GameComponent::ComponentType::UI)
    {
      std::shared_ptr<PlayerUI> ui = std::static_pointer_cast<PlayerUI>(component);
      ui->setLocations(player1Look, player2Look);
    }
  }

  if (keymap[ASGE::KEYS::KEY_F])
  {
    audio_engine.play(fireAudio);
  }
  if (keymap[ASGE::KEYS::KEY_SLASH])
  {
    audio_engine.play(fireAudio);
  }
}

void SceneLevel3::updatePlayers(const ASGE::GameTime& us, Player* player)
{
  switch (player->getTimeState())
  {
    case TimeTravelState::PAST:
      for (auto& PastTile : PastTiles)
      {
        /// Exit Check
        if (player->getSprite()->getWorldBounds().v3.x >= pastExitPos.x)
        {
          setNewScene(GameScene::WIN_SCENE);
        }

        if (Helper::CollisionDetection::inYBounds(
              enemy2->getSprite()->getWorldBounds(), PastTile->getWorldBounds()))
        {
          if (Helper::CollisionDetection::touchingLeft(
                enemy2->getSprite()->getWorldBounds(), PastTile->getWorldBounds()))
          {
            enemy2->getSprite()->xPos(PastTile->xPos() + PastTile->width());
          }
        }
        /// Player Collision Detection
        if (Helper::CollisionDetection::inXBounds(
              player->getSprite()->getWorldBounds(), PastTile->getWorldBounds()))
        {
          if (Helper::CollisionDetection::touchingTop(
                player->getSprite()->getWorldBounds(), PastTile->getWorldBounds()))
          {
            player->setGrounded(true);
            player->getSprite()->yPos(PastTile->yPos() - player->getSprite()->height());
          }
          else if ((Helper::CollisionDetection::touchingBottom(
                     player->getSprite()->getWorldBounds(), PastTile->getWorldBounds())))
          {
            player->setJumpSpeed(0);
            player->setJumping(false);
            player->setJumpPeaked(true);
            player->getSprite()->yPos(PastTile->yPos() + PastTile->height());
          }
        }
        if (Helper::CollisionDetection::playerYChecking(
              player->getSprite()->getWorldBounds(), PastTile->getWorldBounds()))
        {
          if (
            Helper::CollisionDetection::touchingLeft(
              player->getSprite()->getWorldBounds(), PastTile->getWorldBounds()) &&
            !(Helper::CollisionDetection::touchingBottom(
              player->getSprite()->getWorldBounds(), PastTile->getWorldBounds())))
          {
            player->getSprite()->xPos(PastTile->xPos() + PastTile->width());
          }
          else if (
            Helper::CollisionDetection::touchingRight(
              player->getSprite()->getWorldBounds(), PastTile->getWorldBounds()) &&
            !(Helper::CollisionDetection::touchingBottom(
              player->getSprite()->getWorldBounds(), PastTile->getWorldBounds())))
          {
            player->getSprite()->xPos(PastTile->xPos() - player->getSprite()->width());
          }
        }
      }
      break;
    case TimeTravelState::PRESENT:
      for (auto& PresentTile : PresentTiles)
      {
        //        /// Exit Check
        //        if (player->getSprite()->getWorldBounds().v3.x >= presentExitPos.x)
        //        {
        //          setNewScene(GameScene::WIN_SCENE);
        //        }
        /// Enemies
        if (Helper::CollisionDetection::inYBounds(
              enemy2->getSprite()->getWorldBounds(), PresentTile->getWorldBounds()))
        {
          if (Helper::CollisionDetection::touchingLeft(
                enemy2->getSprite()->getWorldBounds(), PresentTile->getWorldBounds()))
          {
            enemy2->getSprite()->xPos(PresentTile->xPos() + PresentTile->width());
          }
        }
        /// Player Collision Detection
        if (Helper::CollisionDetection::inXBounds(
              player->getSprite()->getWorldBounds(), PresentTile->getWorldBounds()))
        {
          if (Helper::CollisionDetection::touchingTop(
                player->getSprite()->getWorldBounds(), PresentTile->getWorldBounds()))
          {
            player->setGrounded(true);
            player->getSprite()->yPos(PresentTile->yPos() - player->getSprite()->height());
          }
          else if ((Helper::CollisionDetection::touchingBottom(
                     player->getSprite()->getWorldBounds(), PresentTile->getWorldBounds())))
          {
            player->setJumpSpeed(0);
            player->setJumping(false);
            player->setJumpPeaked(true);
            player->getSprite()->yPos(PresentTile->yPos() + PresentTile->height());
          }
        }
        if (Helper::CollisionDetection::playerYChecking(
              player->getSprite()->getWorldBounds(), PresentTile->getWorldBounds()))
        {
          if (
            Helper::CollisionDetection::touchingLeft(
              player->getSprite()->getWorldBounds(), PresentTile->getWorldBounds()) &&
            !(Helper::CollisionDetection::touchingBottom(
              player->getSprite()->getWorldBounds(), PresentTile->getWorldBounds())))
          {
            player->getSprite()->xPos(PresentTile->xPos() + PresentTile->width());
          }
          else if (
            Helper::CollisionDetection::touchingRight(
              player->getSprite()->getWorldBounds(), PresentTile->getWorldBounds()) &&
            !(Helper::CollisionDetection::touchingBottom(
              player->getSprite()->getWorldBounds(), PresentTile->getWorldBounds())))
          {
            player->getSprite()->xPos(PresentTile->xPos() - player->getSprite()->width());
          }
        }
      }
      break;
  }

  /// Enemy detection radius
  if (enemy2->getSprite()->xPos() - player->getSprite()->xPos() < 128)
  {
    enemy2->getSprite()->setFlipFlags(ASGE::Sprite::FLIP_X);
    enemy2->setActive(true);
  }
  if (enemy3->getSprite()->xPos() - player->getSprite()->xPos() < 256)
  {
    enemy3->getSprite()->setFlipFlags(ASGE::Sprite::FLIP_X);
    enemy3->setActive(true);
  }
}

void SceneLevel3::updateCamera(const ASGE::GameTime& us)
{
  {
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
  }
}

void SceneLevel3::checkEnemies(const ASGE::GameTime& us, Enemy* enemy)
{
  for (const auto& bullet : player1->getBullets())
  {
    if (Helper::CollisionDetection::isInside(
          bullet->getSprite()->getWorldBounds(), enemy->getSprite()->getWorldBounds()))
    {
      enemy->getSprite()->xPos(10000);
    }
  }
  for (const auto& bullet : player2->getBullets())
  {
    if (Helper::CollisionDetection::isInside(
          bullet->getSprite()->getWorldBounds(), enemy->getSprite()->getWorldBounds()))
    {
      enemy->getSprite()->xPos(10000);
    }
  }
}

void SceneLevel3::fixedUpdate(const ASGE::GameTime& us) {}

void SceneLevel3::render(const ASGE::GameTime& us)
{
  /// Bottom view
  renderer->setViewport(ASGE::Viewport{ 0, 560, 1920, 560 });
  renderer->setProjectionMatrix(camera_two.getView());
  renderScene(us, player2->getTimeState());
  // P1 health UI render
  renderer->render(*UI->getP1Portrait());
  renderer->render(*UI->getP1HealthBar());
  renderer->render(*UI->getP1HealthNum());

  // P1 weapon UI render
  renderer->render(*UI->getP1WepIndicator());
  renderer->render(*UI->getP1ActiveWep());

  // P1 kill count UI render
  renderer->render(*UI->getP1KillsIndicator());
  renderer->render(*UI->getP1KillCount());
  if (UI->getP1KillCountVal() >= 10)
  {
    renderer->render(*UI->getP1KillCountExtra());
  }

  /// Top view
  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 560 });
  renderer->setProjectionMatrix(camera_one.getView());
  renderScene(us, player1->getTimeState());
  // P2 health UI render
  renderer->render(*UI->getP2HealthBar());
  renderer->render(*UI->getP2Portrait());
  renderer->render(*UI->getP2HealthNum());

  // P2 weapon UI render
  renderer->render(*UI->getP2WepIndicator());
  renderer->render(*UI->getP2ActiveWep());

  // P2 kill count render
  renderer->render(*UI->getP2KillsIndicator());
  renderer->render(*UI->getP2KillCount());
  if (UI->getP2KillCountVal() >= 10)
  {
    renderer->render(*UI->getP2KillCountExtra());
  }
}

void SceneLevel3::renderScene(const ASGE::GameTime& us, const TimeTravelState& timeTravelState)
{
  if (timeTravelState == TimeTravelState::PAST)
  {
    for (auto& pastBackground : tilesPastBackground)
    {
      renderer->render(*pastBackground);
    }
    for (auto& PastTile : PastTiles)
    {
      renderer->render(*PastTile);
    }
  }
  if (timeTravelState == TimeTravelState::PRESENT)
  {
    for (auto& presentBackground : tilesPresentBackground)
    {
      renderer->render(*presentBackground);
    }
    for (auto& PresentTile : PresentTiles)
    {
      renderer->render(*PresentTile);
    }
  }

  for (auto& component : gameComponents)
  {
    if (
      component->getComponentType() != GameComponent::ComponentType::UNKNOWN &&
      component->getComponentType() != GameComponent::ComponentType::UI)
    {
      std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(component);
      renderer->render(*sprite->getSprite());
      if (component->getComponentType() == GameComponent::ComponentType::PLAYER)
      {
        std::shared_ptr<Player> player = std::static_pointer_cast<Player>(sprite);
        /// Bullets
        for (const auto& bullet : player->getBullets())
        {
          renderer->render(*bullet->getSprite());
        }
      }
    }
  }
}

bool SceneLevel3::loadPastMap()
{
  ASGE::FILEIO::File tile_map;
  if (!tile_map.open("data/map/Level3PastMap.tmx"))
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
            else
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
        if (object.getName() == "Enemy1")
        {
          pastEnemy1Pos = object.getPosition();
        }
        else if (object.getName() == "Enemy2")
        {
          pastEnemy2Pos = object.getPosition();
        }
        else if (object.getName() == "Enemy3")
        {
          pastEnemy3Pos = object.getPosition();
        }
        else if (object.getName() == "Enemy4")
        {
          pastEnemy4Pos = object.getPosition();
        }
        else if (object.getName() == "StartPoint")
        {
          pastSpawnPos = object.getPosition();
        }
        else if (object.getName() == "EndPoint")
        {
          pastExitPos = object.getPosition();
        }
      }
    }
  }
  return true;
}

bool SceneLevel3::loadPresentMap()
{
  ASGE::FILEIO::File tile_map;

  if (!tile_map.open("data/map/Level3PresentMap.tmx"))
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
            else
            {
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
        if (object.getName() == "Enemy1")
        {
          presentEnemy1Pos = object.getPosition();
        }
        else if (object.getName() == "Enemy2")
        {
          presentEnemy2Pos = object.getPosition();
        }
        else if (object.getName() == "Enemy3")
        {
          presentEnemy3Pos = object.getPosition();
        }
        else if (object.getName() == "Enemy4")
        {
          presentEnemy4Pos = object.getPosition();
        }
      }
    }
  }
  return true;
}

void SceneLevel3::DebugInfo()
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