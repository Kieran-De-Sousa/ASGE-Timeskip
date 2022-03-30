#ifndef ASGEGAME_SCENEMAINMENU_H
#define ASGEGAME_SCENEMAINMENU_H

#include "Scene.h"

class SceneMainMenu : public Scene
{
  SceneMainMenu();
  ~SceneMainMenu() override = default;

  virtual bool init() override;

  virtual void update() override;
  virtual void fixedupdate() override;
  virtual void render() override;
};

#endif // ASGEGAME_SCENEMAINMENU_H
