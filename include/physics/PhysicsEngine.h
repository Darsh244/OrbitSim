#pragma once
#include "core/BodyInfo.h"
#include "core/CelestialBody.h"
#include "core/SimConfig.h"
#include <optional>
#include <vector>

class PhysicsEngine {
  std::vector<CelestialBody> bodies;
  int countBodies = 1;

  // engine variables
  SimConfig config;

public:
  PhysicsEngine() = default;

  // UTILITY
  void addCelestialBody(float m, float r, sf::Vector2f p,
                        sf::Vector2f v = {0, 0}, sf::Vector2f a = {0, 0},
                        sf::Color c = COLOR::RED);
  void resetAcceleration();
  void moveBodies(float timeElapsed); // given the time elapsed (in seconds),
                                      // it moves each body accordingly
  void resetEngine();
  const std::vector<CelestialBody> &getBodies() const { return bodies; }
  std::vector<CelestialBody> &getBodies() { return bodies; }
  SimConfig &getConfig() { return config; }
  const SimConfig &getConfig() const { return config; }

  // mouse click detection
  std::optional<int> findBodyAt(const sf::Vector2f &mouseWorldPos) const;
  std::optional<BodyInfo> getBodyInfo(const int id) const;

  // GRAVITY
  void calculateGravity();

  // COLLISIONS
  void calculateCollisions();

private:
  void removeBodyAtIndex(const int idx);
  void incrementCount() { countBodies++; }

  // GRAVITY HELPERS
  void calculateGravityBetweenBodies(CelestialBody &body1,
                                     CelestialBody &body2);
  float calculateGravitationalForce(
      float m1, float m2, sf::Vector2f &pos1,
      sf::Vector2f &pos2); // only the magnitude of the force

  sf::Vector2f findDirectionOfForce(
      sf::Vector2f &pos1,
      sf::Vector2f &pos2); // returns direction of force wrt to pos1

  // COLLISION HELPERS
  bool isColliding(const CelestialBody &body1, const CelestialBody &body2);

  sf::Vector2f velocityOfMergedBodyAfterCollision(const CelestialBody &body1,
                                                  const CelestialBody &body2);

  sf::Vector2f posOfMergedBodyAfterCollision(const CelestialBody &body1,
                                             const CelestialBody &body2);
};