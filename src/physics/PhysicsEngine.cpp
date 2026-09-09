#include "physics/PhysicsEngine.h"
#include "core/CelestialBody.h"

void PhysicsEngine::add(float m, float r, sf::Vector2f p, sf::Vector2f v,
                        sf::Vector2f a, sf::Color c) {
  CelestialBody body(m, r, p, v, a, c);
  bodies.push_back(body);
}