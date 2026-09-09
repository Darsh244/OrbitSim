#include "core/Timer.h"

float Timer::getDeltaTime() {
  float currentTime = getElapsedTime();
  float dt = currentTime - previousTime;
  previousTime = currentTime;
  return dt;
}

float Timer::getElapsedTime() { return clock.getElapsedTime().asSeconds(); }

void Timer::reset() {
  clock.restart();
  previousTime = 0;
}