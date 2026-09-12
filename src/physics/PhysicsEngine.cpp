#include "physics/PhysicsEngine.h"
#include "core/CelestialBody.h"
#include <cmath>

void PhysicsEngine::moveBodies(float timeElapsed) {
  for (auto &body : bodies) {
    sf::Vector2f oldPos = body.getPosition();
    sf::Vector2f velocity = body.getVelocity();
    sf::Vector2f acc = body.getAcceleration();

    body.setVelocity(velocity + acc * timeElapsed);
    body.setPosition(oldPos + body.getVelocity() * timeElapsed);
  }
}

void PhysicsEngine::calculateGravity(CelestialBody &body1,
                                     CelestialBody &body2) {
  float m1 = body1.getMass();
  float m2 = body2.getMass();
  sf::Vector2f pos1 = body1.getPosition();
  sf::Vector2f pos2 = body2.getPosition();
  float gravityMagnitude = calculateGravitationalForce(m1, m2, pos1, pos2);
  sf::Vector2f directionOfForceOnBody1 = findDirectionOfForce(pos1, pos2);

  sf::Vector2f a1 = (gravityMagnitude / m1) * directionOfForceOnBody1;
  sf::Vector2f a2 = (gravityMagnitude / m2) * (-directionOfForceOnBody1);
  body1.setAcceleration(
      body1.getAcceleration() +
      a1); // incrementing acceleration from force exerted by all other bodies
  body2.setAcceleration(body2.getAcceleration() + a2);
}

float PhysicsEngine::calculateGravitationalForce(float m1, float m2,
                                                 sf::Vector2f &pos1,
                                                 sf::Vector2f &pos2) {
  sf::Vector2f displacementVector = pos2 - pos1;
  float ProductofMasses = (m1 * m2) * powf(KG_PER_MASS_UNIT, 2);
  float SquareOfDistance = powf(displacementVector.x * METERS_PER_PIXEL, 2) +
                           powf(displacementVector.y * METERS_PER_PIXEL, 2);
  return G * (ProductofMasses / SquareOfDistance);
}

sf::Vector2f PhysicsEngine::findDirectionOfForce(sf::Vector2f &pos1,
                                                 sf::Vector2f &pos2) {
  sf::Vector2f displacementVector = pos2 - pos1;
  float magnitude = sqrtf(powf(displacementVector.x * METERS_PER_PIXEL, 2) +
                          powf(displacementVector.y * METERS_PER_PIXEL, 2));
  return displacementVector / magnitude;
}