#include "Simulator.h"
#include "core/CelestialBody.h"
#include "physics/PhysicsEngine.h"
#include "renderer/Renderer.h"
#include <iostream>

Simulator::Simulator(unsigned windowWidth, unsigned windowHeight) {
  window =
      sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "Window");
  window.setFramerateLimit(60);
  engine = PhysicsEngine();
  timer = Timer();
}

void Simulator::run() {
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      handleEvent(
          *event); // handleEvent expects a sf::Event, even is std::optional
    }

    engine.moveBodies(
        timer.getDeltaTime()); // moves bodies using time since last frame
    window.clear();
    for (auto &body : engine.getBodies()) {
      Renderer::draw(window, body);
    }
    if (isSpawningBody && !canSpawnBody) {
      Renderer::drawLine(window, currentSpawiningBodyPosition,
                         velocityLineEndPos);
    }
    window.display();
  }
}

void Simulator::handleEvent(const sf::Event &event) {
  if (event.is<sf::Event::Closed>()) {
    window.close();
  } else if (event.is<sf::Event::MouseButtonPressed>() && canSpawnBody &&
             !isSpawningBody) {
    const auto *mouseButtonPressed =
        event.getIf<sf::Event::MouseButtonPressed>();
    sf::Vector2f spawnPosition(mouseButtonPressed->position);
    currentSpawiningBodyPosition = spawnPosition;
    velocityLineEndPos =
        spawnPosition; // start with zero veloity untill mouse is dragged
    isSpawningBody = true;
    canSpawnBody = false;
  } else if (event.is<sf::Event::MouseMoved>() && isSpawningBody &&
             !canSpawnBody) {
    const auto *mouseMoved = event.getIf<sf::Event::MouseMoved>();
    sf::Vector2f newMousePosition(mouseMoved->position);
    velocityLineEndPos = calculateVelocityLineEndPos(newMousePosition);

  } else if (event.is<sf::Event::MouseButtonReleased>() && isSpawningBody &&
             !canSpawnBody) {
    sf::Vector2f velocity = velocityLineEndPos - currentSpawiningBodyPosition;
    spawnTestBodyWithVelocity(velocity);
    isSpawningBody = false;
    canSpawnBody = true;
  }
}

sf::Vector2f Simulator::calculateVelocityLineEndPos(sf::Vector2f &mousePos) {
  sf::Vector2f vectorToVelocityLineEndPos =
      currentSpawiningBodyPosition - mousePos;
  return (currentSpawiningBodyPosition + vectorToVelocityLineEndPos);
}

void Simulator::spawnTestBodyWithVelocity(sf::Vector2f &v) {
  engine.add(CelestialBody(0, 20, currentSpawiningBodyPosition, v));
}