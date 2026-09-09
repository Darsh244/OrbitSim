#pragma once
#include "core/CelestialBody.h"
#include <vector>

class PhysicsEngine {
  std::vector<CelestialBody> bodies;

public:
  PhysicsEngine() : bodies{} {}
  void add(float m, float r, sf::Vector2f p, sf::Vector2f v, sf::Vector2f a,
           sf::Color c);
  void moveBodies(float timeElapsed); // given the time elapsed (in seconds),
                                      // it moves each body accordingly

  const std::vector<CelestialBody> &getBodies() { return bodies; }
};