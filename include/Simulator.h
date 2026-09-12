#pragma once
#include "core/Timer.h"
#include "physics/PhysicsEngine.h"

class Simulator {
  sf::RenderWindow window;
  PhysicsEngine engine;
  Timer timer;

  // body spawning attributes
  sf::Vector2f currentSpawiningBodyPosition;
  sf::Vector2f velocityLineEndPos;
  bool canSpawnBody = true;
  bool isSpawningBody = false;

public:
  Simulator(unsigned windowWidth, unsigned windowHeight);
  void run();

private:
  void handleEvent(const sf::Event &event);
  void handleRendering();
  void handlePhysics();
  sf::Vector2f calculateVelocityLineEndPos(
      sf::Vector2f &mousePos); // calculates and returns the end position of the
                               // velocity line for the currently spawning body

  // Testing
  void spawnTestBodyWithVelocity(sf::Vector2f &v);
};