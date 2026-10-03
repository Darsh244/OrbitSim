#include "core/Timer.h"

float Timer::getDeltaTime() { return dt; }

sf::Time Timer::getdeltaTimeSFML() { return sf::seconds(getDeltaTime()); }

float Timer::getElapsedTime() { return clock.getElapsedTime().asSeconds(); }

void Timer::reset() {
  clock.restart();
  previousTime = 0;
  dt = 0;
}

void Timer::update() {
  float currentTime = getElapsedTime();
  dt = currentTime - previousTime;
  previousTime = currentTime;
}