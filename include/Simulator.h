#pragma once
#include "physics/PhysicsEngine.h"

class Simulator {
  sf::RenderWindow window;
  PhysicsEngine engine;

public:
  Simulator(unsigned windowWidth, unsigned windowHeight);
  void run();

private:
  void handleEvent(const sf::Event &event);
};