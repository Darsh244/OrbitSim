#include "core/Camera.h"

void Camera::handleClick(const sf::Vector2f &newMousePos) {
  isClicking = true;
  mousePos = newMousePos;
}

void Camera::handleDrag(const sf::Vector2f &newMousePos) {
  mouseDragVector = newMousePos - mousePos;
  cameraOffset += cameraPanningSpeed * mouseDragVector / zoomValue;
  mousePos = newMousePos; // to avoid camera acceleration if you keep dragging
}

void Camera::handleScroll(const sf::Vector2f &newMousePos,
                          const float scrollDelta) {
  sf::Vector2f mouseWorldPosBeforeZoom = giveWorldPos(newMousePos);
  zoomValue += cameraZoomSpeed * scrollDelta;
  cameraOffset = mouseWorldPosBeforeZoom -
                 newMousePos / zoomValue; // mouse world position should stay
                                          // the same before and after zoom
  mousePos = newMousePos;
}

void Camera::handleMouseRelease(const sf::Vector2f &newMousePos) {
  mousePos = newMousePos;
  isClicking = false;
}

sf::Vector2f Camera::giveScreenPos(const sf::Vector2f &worldPos) const {
  return (worldPos - cameraOffset) * zoomValue;
}

sf::Vector2f Camera::giveWorldPos(const sf::Vector2f &screenPos) const {
  return (cameraOffset + screenPos / zoomValue);
}

float Camera::giveRadiusAfterZoom(const float radius) const {
  return radius * zoomValue;
}