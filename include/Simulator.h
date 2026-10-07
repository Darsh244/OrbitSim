#pragma once
#include "core/Camera.h"
#include "core/Timer.h"
#include "core/UI.h"
#include "physics/PhysicsEngine.h"

class Simulator {
  sf::RenderWindow window;
  PhysicsEngine engine;
  Camera camera;
  Timer timer;
  UI ui;

  bool shouldWindowClose = false;

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

  void spawnBodyWithVelocity(const sf::Vector2f &v);
  // Testing
  void spawnTestBodyWithVelocity(const sf::Vector2f &v = {0, 0});
};