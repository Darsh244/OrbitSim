#include "renderer/Renderer.h"
#include "core/Camera.h"
#include "core/CelestialBody.h"
#include <SFML/Graphics.hpp>

void Renderer::draw(sf::RenderWindow &win, const CelestialBody &body,
                    const Camera &camera) {
  float radiusOnScreen = camera.giveRadiusAfterZoom(body.getRadius());
  const sf::Vector2f positionOnWindow =
      camera.giveScreenPos(body.getPosition());

  sf::CircleShape bodyShape(radiusOnScreen < 0 ? 0 : radiusOnScreen);
  bodyShape.setOrigin({radiusOnScreen, radiusOnScreen});
  bodyShape.setPosition(positionOnWindow);
  bodyShape.setFillColor(body.getColor());
  win.draw(bodyShape);
}

void Renderer::drawLine(sf::RenderWindow &win, sf::Vector2f &startPosition,
                        sf::Vector2f &endPosition, const Camera &camera) {
  // argument positions are world positions
  sf::Vector2f startScreenPosition = camera.giveScreenPos(startPosition);
  sf::Vector2f endScreenPosition = camera.giveScreenPos(endPosition);
  sf::Vertex line[] = {sf::Vertex{startScreenPosition, COLOR::RED},
                       sf::Vertex{endScreenPosition, COLOR::RED}};
  win.draw(line, 2, sf::PrimitiveType::Lines);
}