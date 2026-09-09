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
  CelestialBody(float m, float r, sf::Vector2f p, sf::Vector2f v,
                sf::Vector2f a, sf::Color c)
      : mass(m), radius(r), position(p), velocity(v), acc(a), color(c) {}

  float getMass() const { return mass; }
  float getRadius() const { return radius; }
  sf::Color getColor() const { return color; }
  sf::Vector2f getPosition() const { return position; }
};