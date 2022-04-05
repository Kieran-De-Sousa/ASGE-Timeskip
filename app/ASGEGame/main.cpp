#include "Scenes/ASGEGame.hpp"
#include <Engine/Logger.hpp>

int main(int /*argc*/, char* /*argv*/[])
{
  ASGE::GameSettings game_settings;
  game_settings.game_title    = "ASGENetGame";
  game_settings.window_width  = 1920;
  game_settings.window_height = 1080;
  game_settings.mode          = ASGE::GameSettings::WindowMode::WINDOWED;
  game_settings.fixed_ts      = 50;
  game_settings.fps_limit     = 60;
  game_settings.msaa_level    = 16;
  game_settings.vsync         = ASGE::GameSettings::Vsync::ENABLED;

  Logging::INFO("Launching Game!");
  ASGENetGame game(game_settings);
  game.run();
  return 0;
}
