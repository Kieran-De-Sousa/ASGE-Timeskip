#include "ASGEGame.hpp"
#include <Engine/FileIO.hpp>
#include <Engine/Logger.hpp>

/**
 * @brief Initialises the game.
 * Setup your game and initialise the core components.
 * @param settings
 */
ASGENetGame::ASGENetGame(const ASGE::GameSettings& settings) : OGLGame(settings)
{
  renderer->setBaseResolution(1920, 1080, ASGE::Resolution::Policy::MAINTAIN);
  key_callback_id     = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  inputs->use_threads = false;

  scene_manager = std::make_unique<SceneManager>(*renderer, *inputs);
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
  /// !!!!!!!!!!!PAUSE THE GAME WITH P!!!!!!!!!!!!!
  scene_manager->keyHandler(data);
  scene_manager->input();
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
  scene_manager->fixedUpdate(us);
}

/**
 * @brief Updates your game and all it's components.
 * @param us
 */
void ASGENetGame::update(const ASGE::GameTime& us)
{
  /// Assess input, update game and check the current screens state
  scene_manager->update(us);
  scene_manager->checkCurrentSceneState();

  /// Checks if current loaded scene wished for game to exit
  if (scene_manager->onExit())
  {
    signalExit();
  }
}

/**
 * @brief Render your game and its scenes here.
 * @param us
 */
void ASGENetGame::render(const ASGE::GameTime& us)
{
  scene_manager->render(us);
}