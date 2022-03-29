#include "Timer.h"

/// Constructor w/Param
Timer::Timer(float& timerDuration) : timerLength(timerDuration) {}

void Timer::startTimer()
{
  active = true;
}
void Timer::endTimer()
{
  active      = false;
  currentTime = 0;
}

void Timer::updateTimer(float& addTime)
{
  if (currentTime < timerLength)
  {
    currentTime += addTime;
  }
  else
  {
    endTimer();
  }
}
/// SETTER & GETTER FUNCTIONS
// Timer Duration
void Timer::setTimerDuration(float& timerDuration)
{
  timerLength = timerDuration;
}
float Timer::getTimerDuration() const
{
  return 0;
}
// Elapsed Time
void Timer::setElapsedTime(float& elapsedTime)
{
  currentTime = elapsedTime;
}
float Timer::getElapsedTime() const
{
  return currentTime;
}
// Timer Status
void Timer::setTimerStatus(bool& timerStatus)
{
  active = timerStatus;
}
bool Timer::getTimerStatus() const
{
  return active;
}