#pragma once
#include "core/Timer.h"
#include "physics/PhysicsEngine.h"

class Simulator {
  sf::RenderWindow window;
  PhysicsEngine engine;
  Timer timer;

public:
  Simulator(unsigned windowWidth, unsigned windowHeight);
  void run();

private:
  void handleEvent(const sf::Event &event);
};