#include "physics/PhysicsEngine.h"
#include "core/CelestialBody.h"
#include <cmath>

// UTILITY
void PhysicsEngine::removeBodyAtIndex(const int idx) {
  bodies[idx] = bodies.back();
  bodies.pop_back();
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

void PhysicsEngine::resetAcceleration() {
  for (CelestialBody &body : bodies) {
    body.setAcceleration({0, 0});
  }
}

// COLLISIONS
void PhysicsEngine::calculateCollisions() {
  std::vector<bool> merged(bodies.size(), false);
  std::vector<CelestialBody> mergedBodies;

  for (int i = 0; i < bodies.size(); i++) {
    if (merged[i])
      continue;
    for (int j = i + 1; j < bodies.size(); j++) {
      if (merged[j])
        continue;
      if (isColliding(bodies[i], bodies[j])) {
        CelestialBody body1 = bodies[i];
        CelestialBody body2 = bodies[j];
        sf::Vector2f resultingVelocity =
            velocityOfMergedBodyAfterCollision(body1, body2);
        sf::Vector2f resultingPosition =
            posOfMergedBodyAfterCollision(body1, body2);
        float resultingMass = body1.getMass() + body2.getMass();
        float resultingRadius = sqrtf(body1.getRadius() * body1.getRadius() +
                                      body2.getRadius() * body2.getRadius());

        merged[i] = true;
        merged[j] = true;
        mergedBodies.push_back({resultingMass, resultingRadius,
                                resultingPosition, resultingVelocity});
        break; // body i is now merged, stop comparing it against others
      }
    }
  }

  for (int i = bodies.size() - 1; i >= 0;
       i--) { // going in reverse so indices of previous bodies dont change
    if (merged[i])
      removeBodyAtIndex(i);
  }

  for (auto &body : mergedBodies) {
    add(body);
  }
}
bool PhysicsEngine::isColliding(const CelestialBody &body1,
                                const CelestialBody &body2) {
  sf::Vector2f displacementVectorBetweenBodies =
      body2.getPosition() - body1.getPosition();
  float sqrDistance = powf(displacementVectorBetweenBodies.x, 2) +
                      powf(displacementVectorBetweenBodies.y, 2);
  float sqrSumOfRadius = powf(body1.getRadius() + body2.getRadius(), 2);
  return sqrDistance <= sqrSumOfRadius;
}

sf::Vector2f
PhysicsEngine::velocityOfMergedBodyAfterCollision(const CelestialBody &body1,
                                                  const CelestialBody &body2) {
  sf::Vector2f sumOfInitialMomentums = body1.getMass() * body1.getVelocity() +
                                       body2.getMass() * body2.getVelocity();
  return sumOfInitialMomentums / (body1.getMass() + body2.getMass());
}

sf::Vector2f
PhysicsEngine::posOfMergedBodyAfterCollision(const CelestialBody &body1,
                                             const CelestialBody &body2) {
  sf::Vector2f weightedPos = body1.getMass() * body1.getPosition() +
                             body2.getMass() * body2.getPosition();
  return weightedPos /
         (body1.getMass() + body2.getMass()); // this is the position of C.O.M
}

// GRAVITY
void PhysicsEngine::calculateGravity() {
  for (int i = 0; i < bodies.size(); i++) {
    for (int j = i + 1; j < bodies.size(); j++) {
      calculateGravityBetweenBodies(bodies[i], bodies[j]);
    }
  }
}

void PhysicsEngine::calculateGravityBetweenBodies(CelestialBody &body1,
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