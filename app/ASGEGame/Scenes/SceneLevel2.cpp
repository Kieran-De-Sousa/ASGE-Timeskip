#include "SceneLevel2.h"

SceneLevel2::SceneLevel2(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene) :
  Scene(rendererRef, inputRef, scene)
{
}

bool SceneLevel2::init()
{
  setDefaultSceneStatus();

  loadPastMap();
  loadPresentMap();

  player1 = std::make_shared<Player>(*renderer, 1);
  player1->initialiseSprite("/data/sprites/Player1Animation.png");
  player1->setSpriteVariables(24, 24, 3);
  player1->setPosition(64, 240);
  /// Animations
  player1->getSprite()->srcRect()[0] = 0;
  player1->getSprite()->srcRect()[1] = 0;
  player1->getSprite()->srcRect()[2] = 32;
  player1->getSprite()->srcRect()[3] = 32;
  gameComponents.emplace_back(player1);

  player2 = std::make_shared<Player>(*renderer, 2);
  player2->initialiseSprite("/data/sprites/Player2Animation.png");
  player2->setSpriteVariables(24, 24, 3);
  player2->setPosition(88, 240);
  /// Animations
  player2->getSprite()->srcRect()[0] = 0;
  player2->getSprite()->srcRect()[1] = 0;
  player2->getSprite()->srcRect()[2] = 32;
  player2->getSprite()->srcRect()[3] = 32;
  gameComponents.emplace_back(player2);

  /// Enemies
  enemy1 = std::make_shared<EnemyPassive>(*renderer, 5, 1, Enemy::EnemyType::PASSIVE, 300, 350);
  enemy1->initialiseSprite("/data/sprites/mushroom.png");
  enemy1->setSpriteVariables(16, 16, 3);
  enemy1->setPosition(370, 337);
  /// Animations
  enemy1->getSprite()->srcRect()[0] = 0;
  enemy1->getSprite()->srcRect()[1] = 0;
  enemy1->getSprite()->srcRect()[2] = 16;
  enemy1->getSprite()->srcRect()[3] = 16;
  gameComponents.emplace_back(enemy1);

  enemy2 = std::make_shared<EnemyChaser>(*renderer, 5, 1, Enemy::EnemyType::CHASER);
  enemy2->initialiseSprite("/data/sprites/mushroom.png");
  enemy2->setSpriteVariables(16, 16, 3);
  enemy2->setPosition(822, 400);
  /// Animations
  enemy2->getSprite()->srcRect()[0] = 0;
  enemy2->getSprite()->srcRect()[1] = 0;
  enemy2->getSprite()->srcRect()[2] = 16;
  enemy2->getSprite()->srcRect()[3] = 16;
  gameComponents.emplace_back(enemy2);

  enemy3 = std::make_shared<EnemyChaser>(*renderer, 5, 1, Enemy::EnemyType::CHASER);
  enemy3->initialiseSprite("/data/sprites/mushroom.png");
  enemy3->setSpriteVariables(16, 16, 3);
  enemy3->setPosition(1171, 272);
  /// Animations
  enemy3->getSprite()->srcRect()[0] = 0;
  enemy3->getSprite()->srcRect()[1] = 0;
  enemy3->getSprite()->srcRect()[2] = 16;
  enemy3->getSprite()->srcRect()[3] = 16;
  gameComponents.emplace_back(enemy3);

  enemy4 = std::make_shared<EnemyChaser>(*renderer, 5, 1, Enemy::EnemyType::CHASER);
  enemy4->initialiseSprite("/data/sprites/mushroom.png");
  enemy4->setSpriteVariables(16, 16, 3);
  enemy4->setPosition(3283, 335);
  /// Animations
  enemy4->getSprite()->srcRect()[0] = 0;
  enemy4->getSprite()->srcRect()[1] = 0;
  enemy4->getSprite()->srcRect()[2] = 16;
  enemy4->getSprite()->srcRect()[3] = 16;
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
void SceneLevel2::input()
{
  player1->updateKeymap(keymap);
  player2->updateKeymap(keymap);

  if (keymap[ASGE::KEYS::KEY_Q] || keymap[ASGE::KEYS::KEY_SPACE])
  {
    switch (state)
    {
      case TimeTravelState::PAST:
        state = TimeTravelState::PRESENT;
        DebugInfo();
        break;

      case TimeTravelState::PRESENT:
        state = TimeTravelState::PAST;
        DebugInfo();
        break;
    }
  }
}

void SceneLevel2::update(const ASGE::GameTime& us)
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
        if (gamepad.buttons[ASGE::GAMEPAD::BUTTON_CIRCLE])
        {
          setPauseScreen(true);
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

void SceneLevel2::updatePlayers(const ASGE::GameTime& us, Player* player)
{
  switch (state)
  {
    case TimeTravelState::PAST:
      for (unsigned long long i = 0; i < PastTiles.size(); ++i)
      {
        /// Exit Check
        if (player->getSprite()->getWorldBounds().v3.x >= pastExitPos.x)
        {
          setNewScene(GameScene::LEVEL_3);
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
      for (unsigned long long i = 0; i < PresentTiles.size(); ++i)
      {
        //        /// Exit Check
        //        if (player->getSprite()->getWorldBounds().v3.x >= presentExitPos.x)
        //        {
        //          setNewScene(GameScene::LEVEL_3);
        //        }
        /// Enemies
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

  /// Health pick up
  if (Helper::CollisionDetection::isInside(
        player->getSprite()->getWorldBounds(), HealthPowerUp->getSprite()->getWorldBounds()))
  {
    player->setHealth(player->getHealth() + 1);
    UI->addHealth(static_cast<int>(player->getPlayerID()));
    HealthPowerUp->getSprite()->xPos(-300);
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
  if (enemy4->getSprite()->xPos() - player->getSprite()->xPos() < 128)
  {
    enemy4->getSprite()->setFlipFlags(ASGE::Sprite::FLIP_X);
    enemy4->setActive(true);
  }
}

void SceneLevel2::updateCamera(const ASGE::GameTime& us)
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

void SceneLevel2::checkEnemies(const ASGE::GameTime& us, Enemy* enemy)
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

void SceneLevel2::fixedUpdate(const ASGE::GameTime& us) {}

void SceneLevel2::render(const ASGE::GameTime& us)
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
  renderScene(us);
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

void SceneLevel2::renderScene(const ASGE::GameTime& us)
{
  if (state == TimeTravelState::PAST)
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
  if (state == TimeTravelState::PRESENT)
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

bool SceneLevel2::loadPastMap()
{
  ASGE::FILEIO::File tile_map;
  if (!tile_map.open("/data/map/Level2PastMap.tmx"))
  {
    Logging::ERRORS("init::Failed to load past map");
    return false;
  }
  ASGE::FILEIO::IOBuffer buffer = tile_map.read();
  std::string file_string(buffer.as_char(), buffer.length);
  level2map.loadFromString(file_string, ".");

  /// All collidable objects are checked within the init function as their location is will remain
  /// the same during gameplay, i.e: they remain static.
  for (const auto& layer : level2map.getLayers())
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
          auto tile      = level2map.getTilesets()[0].getTile(tile_info.ID);
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

bool SceneLevel2::loadPresentMap()
{
  ASGE::FILEIO::File tile_map;

  if (!tile_map.open("/data/map/Level2PresentMap.tmx"))
  {
    Logging::ERRORS("init::Failed to load present map");
    return false;
  }
  ASGE::FILEIO::IOBuffer buffer = tile_map.read();
  std::string file_string(buffer.as_char(), buffer.length);
  level2map.loadFromString(file_string, ".");

  /// All collidable objects are checked within the init function as their location is will remain
  /// the same during gameplay, i.e: they remain static.
  for (const auto& layer : level2map.getLayers())
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
          auto tile      = level2map.getTilesets()[0].getTile(tile_info.ID);
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

void SceneLevel2::DebugInfo() {}

void SceneLevel2::initAudio() {}
