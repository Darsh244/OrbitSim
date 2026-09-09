#include "physics/PhysicsEngine.h"
#include "core/CelestialBody.h"

void PhysicsEngine::add(float m, float r, sf::Vector2f p, sf::Vector2f v,
                        sf::Vector2f a, sf::Color c) {
  CelestialBody body(m, r, p, v, a, c);
  bodies.push_back(body);
}

void PhysicsEngine::moveBodies(float timeElapsed) {
  for (auto &body : bodies) {
    sf::Vector2f oldPos = body.getPosition();
    sf::Vector2f velocity = body.getVelocity();
    sf::Vector2f acc = body.getAcceleration();

    body.setVelocity(velocity + acc * timeElapsed);
    body.setPosition(oldPos + body.getVelocity() * timeElapsed);
  }
}