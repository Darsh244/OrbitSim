#pragma once
#include "core/Color.h"
#include <SFML/System.hpp>

class CelestialBody {
  float mass;
  float radius;
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f acc; // acceleration
  sf::Color color;

public:
  CelestialBody(float m, float r, sf::Vector2f p, sf::Vector2f v = {0, 0},
                sf::Vector2f a = {0, 0}, sf::Color c = COLOR::RED)
      : mass(m), radius(r), position(p), velocity(v), acc(a), color(c) {}

  // getters
  float getMass() const { return mass; }
  float getRadius() const { return radius; }
  sf::Color getColor() const { return color; }
  sf::Vector2f getPosition() const { return position; }
  sf::Vector2f getVelocity() const { return velocity; }
  sf::Vector2f getAcceleration() const { return acc; }

  // setters
  void setPosition(sf::Vector2f newPos) { position = newPos; }
  void setVelocity(sf::Vector2f newVel) { velocity = newVel; }
  void setAcceleration(sf::Vector2f newAcc) { acc = newAcc; }
};