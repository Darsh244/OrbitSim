#pragma once
#include <SFML/System.hpp>

class Timer {
  sf::Clock clock;
  float previousTime;

public:
  Timer() : previousTime(0.0f){};
  float getDeltaTime();
  float getElapsedTime();
  void reset();
};