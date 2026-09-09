#include "renderer/Renderer.h"
#include "core/CelestialBody.h"
#include <SFML/Graphics.hpp>

void Renderer::draw(sf::RenderWindow &win, const CelestialBody &body) {
  float radius = body.getRadius();
  const sf::Vector2f position = body.getPosition();

  sf::CircleShape bodyShape(radius);
  bodyShape.setOrigin({radius, radius});
  bodyShape.setPosition(position);
  bodyShape.setFillColor(body.getColor());
  win.draw(bodyShape);
}