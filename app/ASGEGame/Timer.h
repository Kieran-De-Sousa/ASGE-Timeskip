#ifndef ASGEGAME_TIMER_H
#define ASGEGAME_TIMER_H

/// Game Engine
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>

/**
 * @brief Timer based class for classes requiring timers systems such as transitions, power-ups,
 * game world, etc.
 * @author Kieran
 */
class Timer
{
 public:
  /**
   * @brief Constructor w/Param
   * @details Timer objects instantiate with their duration already set
   * @param timerDuration
   */
  explicit Timer(float& timerDuration) : timerLength(timerDuration){};
  /**
   * @brief Default constructor
   * @details Use when duration length of timer is unknown during instantiation
   */
  explicit Timer() = default;
  ~Timer()         = default;

  /**
   * @brief Activate timer by changing 'active' private variable to true
   */
  void startTimer();
  /**
   * @brief Called when elapsed time exceeds the timer length set
   * @see updateTimer
   */
  void endTimer();
  /**
   * @brief Update the current elapsed time of the timer along with the timer state
   * @details Add the current elapsed timer time to the calculated delta time
   * within the fixed update loop. Timer will compare set duration against elapsed time and update
   * its active state depending on the result.
   * @param addTime
   */
  void updateTimer(float& addTime);

  /// SETTER & GETTER FUNCTIONS
  // Timer Duration
  void setTimerDuration(float& timerDuration);
  [[nodiscard]] float getTimerDuration() const;
  // Elapsed Time
  void setElapsedTime(float& elapsedTime);
  [[nodiscard]] float getElapsedTime() const;
  // Timer Status
  void setTimerStatus(bool& timerStatus);
  [[nodiscard]] bool getTimerStatus() const;

 private:
  bool active       = false;
  float timerLength = 0;
  float currentTime = 0;
};

#endif // ASGEGAME_TIMER_H
