#pragma once
#include <SFML/System.hpp>

class Timer {
  sf::Clock clock;
  float previousTime;
  float dt;

public:
  Timer() : previousTime(0.0f), dt(0.0f){};
  float getDeltaTime();
  float getElapsedTime();
  sf::Time getdeltaTimeSFML();
  void reset();
  void update();
};