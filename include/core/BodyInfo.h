#pragma once
#include <SFML/System/Vector2.hpp>

struct BodyInfo {
  int id;
  float mass;
  float radius;
  sf::Vector2f position;
  sf::Vector2f velocity;
  float speed;
  sf::Vector2f momentum;
  float kineticEnergy;
};