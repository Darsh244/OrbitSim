#pragma once
#include "core/CelestialBody.h"
#include <vector>

class PhysicsEngine {
  std::vector<CelestialBody> bodies;

  // universal constants
  static constexpr float G = 500.0f;
  static constexpr float KG_PER_MASS_UNIT = 1.0f;
  static constexpr float METERS_PER_PIXEL = 1.0f;

public:
  PhysicsEngine() : bodies{} {}
  void add(CelestialBody body) { bodies.push_back(body); };
  void moveBodies(float timeElapsed); // given the time elapsed (in seconds),
                                      // it moves each body accordingly

  void calculateGravity(CelestialBody &body1, CelestialBody &body2);
  void calculateCollisions();
  const std::vector<CelestialBody> &getBodies() const { return bodies; }
  std::vector<CelestialBody> &getBodies() { return bodies; }

private:
  void removeBodyAtIndex(const int idx);
  float calculateGravitationalForce(
      float m1, float m2, sf::Vector2f &pos1,
      sf::Vector2f &pos2); // only the magnitude of the force

  sf::Vector2f findDirectionOfForce(
      sf::Vector2f &pos1,
      sf::Vector2f &pos2); // returns direction of force wrt to pos1

  bool isColliding(const CelestialBody &body1, const CelestialBody &body2);
  sf::Vector2f velocityOfMergedBodyAfterCollision(const CelestialBody &body1,
                                                  const CelestialBody &body2);
  sf::Vector2f posOfMergedBodyAfterCollision(const CelestialBody &body1,
                                             const CelestialBody &body2);
};