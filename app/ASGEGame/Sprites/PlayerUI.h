#ifndef ASGEGAME_PLAYERUI_H
#define ASGEGAME_PLAYERUI_H

#include "Components/GameComponent.h"
#include "Sprite.h"
#include <Engine/Sprite.hpp>

class PlayerUI : public GameComponent
{
 public:
  // initialisation stuff
  explicit PlayerUI(ASGE::Renderer& rendererRef);
  virtual ~PlayerUI() override = default;

  void init();
  void setLocations(const ASGE::Point2D& player1, const ASGE::Point2D& player2);

  // sprite rendering functions
  // health functions
  ASGE::Sprite* getP1HealthBar();
  ASGE::Sprite* getP2HealthBar();
  ASGE::Sprite* getP1HealthNum();
  ASGE::Sprite* getP2HealthNum();

  // portrait functions
  ASGE::Sprite* getP1Portrait();
  ASGE::Sprite* getP2Portrait();

  // weapon functions
  ASGE::Sprite* getP1WepIndicator();
  ASGE::Sprite* getP2WepIndicator();
  ASGE::Sprite* getP1ActiveWep();
  ASGE::Sprite* getP2ActiveWep();

  // kill count functions
  ASGE::Sprite* getP1KillsIndicator();
  ASGE::Sprite* getP2KillsIndicator();
  ASGE::Sprite* getP1KillCount();
  ASGE::Sprite* getP1KillCountExtra();
  ASGE::Sprite* getP2KillCount();
  ASGE::Sprite* getP2KillCountExtra();

  // kill count numbers
  int getP1KillCountVal();
  int getP2KillCountVal();

  // health stuff
  void removeHealth(int playerID);
  void addHealth(int playerID);

  virtual void update(const ASGE::GameTime& us) override;
  void updateLives();

  // weapon stuff
  void updateWeapon();
  void changeWeapon(int playerID, int wepID);

 private:
  // random vars
  int p1_health_val = 3;
  int p2_health_val = 3;
  int p1_kills_val  = 0;
  int p2_kills_val  = 0;

  // weapon stuff: 1 = Machine Gun, 2 = Shotgun
  int p1_wep_choice = 1;
  int p2_wep_choice = 1;

  // sprite block
  std::unique_ptr<Sprite> p1_health_bar;
  std::unique_ptr<Sprite> p2_health_bar;
  std::unique_ptr<Sprite> p1_health_num;
  std::unique_ptr<Sprite> p2_health_num;

  std::unique_ptr<Sprite> p1_portrait;
  std::unique_ptr<Sprite> p2_portrait;

  std::unique_ptr<Sprite> p1_wep_indicator;
  std::unique_ptr<Sprite> p2_wep_indicator;
  std::unique_ptr<Sprite> p1_active_wep;
  std::unique_ptr<Sprite> p2_active_wep;

  std::unique_ptr<Sprite> p1_kills_indicator;
  std::unique_ptr<Sprite> p2_kills_indicator;
  std::unique_ptr<Sprite> p1_kill_count;
  std::unique_ptr<Sprite> p2_kill_count;
  std::unique_ptr<Sprite> extra_p1_kill_count;
  std::unique_ptr<Sprite> extra_p2_kill_count;

  // renderer
  ASGE::Renderer* renderer;
};

#endif // ASGEGAME_PLAYERUI_H
