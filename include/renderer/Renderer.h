#pragma once
#include "SFML/Graphics.hpp"
class CelestialBody;
class Camera;

class Renderer {
public:
  Renderer() = delete;
  static void draw(sf::RenderWindow &win, const CelestialBody &body,
                   const Camera &camera);
  static void drawLine(sf::RenderWindow &win, sf::Vector2f &startPosition,
                       sf::Vector2f &endPosition, const Camera &camera);
};