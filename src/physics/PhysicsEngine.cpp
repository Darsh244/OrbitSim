#include "physics/PhysicsEngine.h"
#include <cmath>

PhysicsEngine::PhysicsEngine() : bodies{} {
  G = DEFAULT_G;
  KG_PER_MASS_UNIT = DEFAULT_KG_PER_MASS_UNIT;
  METERS_PER_PIXEL = DEFAULT_METERS_PER_PIXEL;
}

// UTILITY
void PhysicsEngine::addCelestialBody(float m, float r, sf::Vector2f p,
                                     sf::Vector2f v, sf::Vector2f a,
                                     sf::Color c) {
  bodies.push_back({countBodies, m, r, p, v, a, c});
  incrementCount();
}

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

void PhysicsEngine::resetEngine() {
  G = DEFAULT_G;
  KG_PER_MASS_UNIT = DEFAULT_KG_PER_MASS_UNIT;
  METERS_PER_PIXEL = DEFAULT_METERS_PER_PIXEL;
  bodies.clear();
  countBodies = 1;
}

// mouse click detection
std::optional<int>
PhysicsEngine::findBodyAt(const sf::Vector2f &mouseWorldPos) const {
  for (int i = bodies.size() - 1; i >= 0; i--) {
    sf::Vector2f d = mouseWorldPos - bodies[i].getPosition();
    float r = bodies[i].getRadius();
    bool inside = d.x * d.x + d.y * d.y <= r * r;
    if (inside) {
      return bodies[i].getId();
    }
  }
  return std::nullopt;
}

std::optional<BodyInfo> PhysicsEngine::getBodyInfo(const int bodyId) const {
  int left = 0;
  int right = bodies.size() - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    int id = bodies[mid].getId();
    if (id == bodyId) {
      float mass = bodies[mid].getMass();
      sf::Vector2f velocity = bodies[mid].getVelocity();
      float speed = velocity.length();
      return BodyInfo{bodyId,
                      mass,
                      bodies[mid].getRadius(),
                      bodies[mid].getPosition(),
                      velocity,
                      speed,
                      mass * velocity,
                      0.5f * mass * speed * speed};
    } else if (id < bodyId) {
      left = mid + 1;
    } else
      right = mid - 1;
  }
  return std::nullopt;
}

// COLLISIONS
void PhysicsEngine::calculateCollisions() {
  std::vector<bool> merged(bodies.size(), false);
  std::vector<std::tuple<float, float, sf::Vector2f, sf::Vector2f>>
      mergedBodies;

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

  for (int i = 0; i < mergedBodies.size(); i++) {
    addCelestialBody(std::get<0>(mergedBodies[i]), std::get<1>(mergedBodies[i]),
                     std::get<2>(mergedBodies[i]),
                     std::get<3>(mergedBodies[i]));
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