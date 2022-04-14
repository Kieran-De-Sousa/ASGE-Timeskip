#include "Components/Timer.h"

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
  return timerLength;
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