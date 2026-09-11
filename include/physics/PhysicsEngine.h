#pragma once
#include "core/CelestialBody.h"
#include <vector>

class PhysicsEngine {
  std::vector<CelestialBody> bodies;

public:
  PhysicsEngine() : bodies{} {}
  void add(CelestialBody body) { bodies.push_back(body); };
  void moveBodies(float timeElapsed); // given the time elapsed (in seconds),
                                      // it moves each body accordingly

  const std::vector<CelestialBody> &getBodies() { return bodies; }
};