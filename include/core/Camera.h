#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Camera {
  sf::Vector2f cameraOffset = {0, 0};
  sf::Vector2f mouseDragVector = {0, 0};
  sf::Vector2f mousePos = {0, 0};

  bool isClicking = false;
  float zoomValue = 1;
  inline static float cameraPanningSpeed = 0.50;
  inline static float cameraZoomSpeed = 0.05;

public:
  void handleClick(const sf::Vector2f &newMousePos);
  void handleDrag(const sf::Vector2f &newMousePos);
  void handleScroll(const sf::Vector2f &newMousePos, const float scrollDelta);
  void handleMouseRelease(const sf::Vector2f &newMousePos);

  sf::Vector2f giveScreenPos(const sf::Vector2f &worldPos) const;
  sf::Vector2f giveWorldPos(const sf::Vector2f &screenPos) const;
  float giveRadiusAfterZoom(const float radius) const;

  bool getIsClicking() const { return isClicking; }
  sf::Vector2f getCameraOffset() const { return cameraOffset; }
};