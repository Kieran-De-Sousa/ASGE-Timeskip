#ifndef ASGEGAME_PLAYERUI_H
#define ASGEGAME_PLAYERUI_H

#include "Sprite.h"
#include <Engine/Sprite.hpp>

class PlayerUI
{
 public:
  // initialisation stuff
  explicit PlayerUI(ASGE::Renderer& rendererRef);
  virtual ~PlayerUI() = default;

  void init();

  // sprite stuff
  ASGE::Sprite* getP1HealthBar();
  ASGE::Sprite* getP2HealthBar();
  ASGE::Sprite* getP1Portrait();
  ASGE::Sprite* getP2Portrait();
  ASGE::Sprite* getP1WepIndicator();
  ASGE::Sprite* getP2WepIndicator();
  ASGE::Sprite* getP1ActiveWep();
  ASGE::Sprite* getP2ActiveWep();

  // health stuff
  void removeHealth(int playerID);
  void addHealth(int playerID);

  void updateLives();

  // weapon stuff
  void updateWeapon();
  void changeWeapon(int playerID, int wepID);

 private:
  // random vars
  int p1_health_val = 3;
  int p2_health_val = 3;

  // weapon stuff: 1 = Machine Gun, 2 = Shotgun
  int p1_wep_choice = 1;
  int p2_wep_choice = 1;

  // sprite block
  std::unique_ptr<Sprite> p1_health_bar;
  std::unique_ptr<Sprite> p2_health_bar;
  std::unique_ptr<Sprite> p1_portrait;
  std::unique_ptr<Sprite> p2_portrait;
  std::unique_ptr<Sprite> p1_wep_indicator;
  std::unique_ptr<Sprite> p2_wep_indicator;
  std::unique_ptr<Sprite> p1_active_wep;
  std::unique_ptr<Sprite> p2_active_wep;

  // renderer
  std::unique_ptr<ASGE::Renderer> renderer;
};

#endif // ASGEGAME_PLAYERUI_H
