#include "SceneLevel2.h"

SceneLevel2::SceneLevel2(ASGE::Renderer& rendererRef, ASGE::Input& inputRef, GameScene scene) :
  Scene(rendererRef, inputRef, scene)
{
}

bool SceneLevel2::init()
{
  setDefaultSceneStatus();

  player1 = std::make_shared<Player>(*renderer, 1);
  player1->initialiseSprite("/data/sprites/Player1Animation.png");
  player1->setSpriteVariables(24, 24, 3);
  player1->setPosition(64, 240);
  // gameComponents.emplace_back(std::move(player1));

  player2 = std::make_shared<Player>(*renderer, 2);
  player2->initialiseSprite("/data/sprites/Player2Animation.png");
  player2->setSpriteVariables(24, 24, 3);
  player2->setPosition(88, 240);
  // gameComponents.emplace_back(std::move(player2));

  return true;
}
void SceneLevel2::input() {}

void SceneLevel2::update(const ASGE::GameTime& us) {}

void SceneLevel2::fixedUpdate(const ASGE::GameTime& us) {}

void SceneLevel2::render(const ASGE::GameTime& us)
{
  //  for (auto& component : gameComponents)
  //  {
  //    if (component->getComponentType() != GameComponent::ComponentType::UNKNOWN)
  //    {
  //      /// Cast to sprite
  //      std::shared_ptr<Sprite> sprite = std::dynamic_pointer_cast<Sprite>(component.get());
  //      /// Render the sprite
  //      renderer->render(*sprite->getSprite());
  //      if (sprite->getComponentType() == GameComponent::ComponentType::PLAYER)
  //      {
  //        for (const auto& bullet : player->getBullets())
  //        {
  //          renderer->render(*bullet->getSprite());
  //        }
  //        /// Put back into vector
  //        gameComponents.emplace_back(std::move(player));
  //      }
  //      else
  //      {
  //        /// Put back into vector
  //        gameComponents.emplace_back(std::move(sprite));
  //      }
  //    }
  //  }
}

void SceneLevel2::renderScene(const ASGE::GameTime& us) {}

bool SceneLevel2::loadPastMap()
{
  return false;
}
bool SceneLevel2::loadPastBackground()
{
  return false;
}
bool SceneLevel2::loadPresentMap()
{
  return false;
}
bool SceneLevel2::loadPresentBackground()
{
  return false;
}

void SceneLevel2::Camera() {}

void SceneLevel2::DebugInfo() {}

void SceneLevel2::initAudio() {}
