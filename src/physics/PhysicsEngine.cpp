#include "physics/PhysicsEngine.h"
#include "core/CelestialBody.h"

void PhysicsEngine::moveBodies(float timeElapsed) {
  for (auto &body : bodies) {
    sf::Vector2f oldPos = body.getPosition();
    sf::Vector2f velocity = body.getVelocity();
    sf::Vector2f acc = body.getAcceleration();

    body.setVelocity(velocity + acc * timeElapsed);
    body.setPosition(oldPos + body.getVelocity() * timeElapsed);
  }
}