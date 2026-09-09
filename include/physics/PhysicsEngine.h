#pragma once
#include "core/CelestialBody.h"
#include <vector>

class PhysicsEngine {
  std::vector<CelestialBody> bodies;

public:
  PhysicsEngine() : bodies{} {}
  void add(float m, float r, sf::Vector2f p, sf::Vector2f v, sf::Vector2f a,
           sf::Color c);

  const std::vector<CelestialBody> &getBodies() { return bodies; }
};