#pragma once
#include "SFML/Graphics.hpp"
class CelestialBody;

class Renderer {
public:
  Renderer() = delete;
  static void draw(sf::RenderWindow &win, const CelestialBody &body);
};