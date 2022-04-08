#ifndef ASGEGAME_GAMESCENES_H
#define ASGEGAME_GAMESCENES_H

/**
 *
 * @author Kieran
 */

/**
 * @brief Enum data class for storing game scene IDs
 */
enum class GameScene : int
{
  UNDEFINED    = 0,
  MAIN_MENU    = 1,
  LEVEL_SELECT = 2,
  LEVEL_1      = 3,
  LEVEL_2      = 4
  /// Insert more scenes here...
};

/**
 * @brief Data struct holding relevant information for every game scene
 */
struct SceneStatus
{
  explicit SceneStatus(GameScene scene) : current_scene(scene) {}
  SceneStatus()          = default;
  virtual ~SceneStatus() = default;

  GameScene current_scene = GameScene::UNDEFINED;
  GameScene new_scene     = GameScene::UNDEFINED;
  bool change_scene       = false;
};

#endif // ASGEGAME_GAMESCENES_H